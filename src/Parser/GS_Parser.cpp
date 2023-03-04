#include <map>

#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    std::map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,  2},
            {Lexer::TokenType::SymbolSlash, 2},
            {Lexer::TokenType::SymbolPlus,  1},
            {Lexer::TokenType::SymbolMinus, 1}
    };

    GS_Parser::GS_Parser(LRef<Driver::GS_Session> session,
                         ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer)
            : _session(session),
              _messages(IO::GSMessageArray()),
              _tokenBuffer(tokenBuffer),
              _tokenIterator(_tokenBuffer.cbegin()),
              _builder(AST::GS_ASTBuilder::Create(_session.GetASTContext())) {}

    GS_Parser GS_Parser::Create(LRef<Driver::GS_Session> session,
                                ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer) {
        return GS_Parser(session,
                         tokenBuffer);
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::Run(LRef<Driver::GS_Session> session,
                                                        ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer,
                                                        UString translationUnitName) {
        auto parser = GS_Parser::Create(session,
                                        tokenBuffer);

        auto translationUnitDeclaration = parser.ParseProgram(std::move(translationUnitName));

        return translationUnitDeclaration;
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::ParseProgram(UString programName) {
        auto translationUnitDeclaration = ParseTranslationUnitDeclaration(std::move(programName));

        for (auto &message : _messages) {
            _session.Out() << message;
        }

        return translationUnitDeclaration;
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::ParseTranslationUnitDeclaration(UString translationUnitName) {
        auto unit = _builder->CreateTranslationUnitDeclaration(std::move(translationUnitName));

        while (!IsTokenType(Lexer::TokenType::EndOfFile)) {
            auto declaration = ParseDeclaration();

            if (!declaration) {
                return nullptr;
            }

            unit->AddNode(declaration);
        }

        return unit;
    }

    AST::GSDeclarationPtr GS_Parser::ParseDeclaration() {
        AST::GSDeclarationPtr declaration;

        declaration = TryParse(&GS_Parser::ParseFunctionDeclaration);

        if (declaration) {
            return declaration;
        }

        ErrorMessage("Unknown declaration!"_us);

        return nullptr;
    }

    AST::NodePtr<AST::GS_FunctionDeclaration> GS_Parser::ParseFunctionDeclaration() {
        if (!IsTokenType(Lexer::TokenType::KeywordFunc)) {
            ErrorMessage("Missed keyword 'func' in function declaration!"_us);

            return nullptr;
        }

        NextToken(); // skip 'func'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            ErrorMessage("Invalid identifier in function declaration!"_us);

            return nullptr;
        }

        auto functionName = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            ErrorMessage("Missed symbol '(' in function declaration!"_us);

            return nullptr;
        }

        NextToken(); // skip '('

        if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            ErrorMessage("Missed symbol ')' in function declaration!"_us);

            return nullptr;
        }

        NextToken(); // skip ')'

        if (!IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
            ErrorMessage("Missed symbol '{' in function declaration!"_us);

            return nullptr;
        }

        NextToken(); // skip '{'

        auto function = _builder->CreateFunctionDeclaration(functionName);

        while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = ParseStatement();

            if (!statement) {
                return nullptr;
            }

            function->AddStatement(statement);
        }

        NextToken(); // skip '}'

        return function;
    }

    AST::GSStatementPtr GS_Parser::ParseStatement() {
        AST::GSStatementPtr statement;

        statement = TryParse(&GS_Parser::ParseVariableDeclarationStatement);

        if (statement) {
            return statement;
        }

        statement = TryParse(&GS_Parser::ParseAssignmentStatement);

        if (statement) {
            return statement;
        }

        statement = TryParse(&GS_Parser::ParseExpressionStatement);

        if (statement) {
            return statement;
        }

        ErrorMessage("Unknown statement!");

        return nullptr;
    }

    AST::NodePtr<AST::GS_VariableDeclarationStatement> GS_Parser::ParseVariableDeclarationStatement() {
        UString variableName;
        Semantic::GSTypePtr variableType;
        AST::GSExpressionPtr variableExpression;

        if (!IsTokenType(Lexer::TokenType::KeywordVar)) {
            ErrorMessage("Missed keyword 'var' in variable declaration statement!"_us);

            return nullptr;
        }

        NextToken(); // skip 'var'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            ErrorMessage("Invalid identifier in variable declaration statement!"_us);

            return nullptr;
        }

        variableName = TokenValue();

        NextToken(); // skip variable name

        if (!IsTokenType(Lexer::TokenType::SymbolColon) &&
            !IsTokenType(Lexer::TokenType::SymbolEq)) {
            ErrorMessage("Missed '=' for expression or ':' for type in variable declaration statement!"_us);

            return nullptr;
        }

        if (IsTokenType(Lexer::TokenType::SymbolColon)) {
            NextToken(); // skip ':'

            variableType = ParseType();
        }

        if (IsTokenType(Lexer::TokenType::SymbolEq)) {
            NextToken(); // skip '='

            variableExpression = ParseExpression();
        }

        auto variable = _builder->CreateVariableDeclarationStatement(variableName,
                                                                     variableType,
                                                                     variableExpression);

        return variable;
    }

    AST::NodePtr<AST::GS_AssignmentStatement> GS_Parser::ParseAssignmentStatement() {
        auto lvalueExpression = ParseLValueExpression();

        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            ErrorMessage("Missed symbol '=' in assignment statement!"_us);

            return nullptr;
        }

        NextToken(); // skip '='

        auto rvalueExpression = ParseRValueExpression();

        auto assignmentStatement = _builder->CreateAssignmentStatement(lvalueExpression,
                                                                       rvalueExpression);

        return assignmentStatement;
    }

    AST::NodePtr<AST::GS_ExpressionStatement> GS_Parser::ParseExpressionStatement() {
        auto expression = ParseExpression();

        auto expressionStatement = _builder->CreateExpressionStatement(expression);

        return expressionStatement;
    }

    AST::GSExpressionPtr GS_Parser::ParseExpression() {
        AST::GSExpressionPtr expression;

        expression = TryParse(&GS_Parser::ParseArrayExpression);

        if (expression) {
            return expression;
        }

        expression = TryParse(&GS_Parser::ParseUnaryExpression);

        if (expression) {
            return ParseBinaryExpression(0,
                                         expression);
        }

        ErrorMessage("Unknown expression!"_us);

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseLValueExpression() {
        AST::GSExpressionPtr expression;

        expression = TryParse(&GS_Parser::ParseVariableUsingExpression);

        if (expression) {
            return expression;
        }

        ErrorMessage("Unknown left value expression!"_us);

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseRValueExpression() {
        AST::GSExpressionPtr expression;

        expression = TryParse(&GS_Parser::ParseArrayExpression);

        if (expression) {
            return expression;
        }

        expression = TryParse(&GS_Parser::ParseUnaryExpression);

        if (expression) {
            return ParseBinaryExpression(0,
                                         expression);
        }

        ErrorMessage("Unknown right value expression!"_us);

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseConstantExpression() {
        auto value = ParseValue();

        if (!value) {
            return nullptr;
        }

        return _builder->CreateConstantExpression(value);
    }

    AST::GSExpressionPtr GS_Parser::ParseUnaryExpression() {
        if (IsTokenType(Lexer::TokenType::SymbolMinus)) {
            NextToken(); // skip '-'

            auto expression = ParsePrimaryExpression();

            return _builder->CreateUnaryExpression(AST::UnaryOperation::Minus,
                                                   expression);
        }

        return ParsePrimaryExpression();
    }

    AST::GSExpressionPtr GS_Parser::ParseBinaryExpression(I32 expressionPrecedence,
                                                          LRef<AST::GSExpressionPtr> expression) {
        while (true) {
            auto currentTokenPrecedence = TokenPrecedence();

            if (currentTokenPrecedence < expressionPrecedence) {
                return expression;
            }

            AST::BinaryOperation binaryOperator;

            switch (TokenType()) {
                case Lexer::TokenType::SymbolPlus:
                    binaryOperator = AST::BinaryOperation::Plus;

                    break;
                case Lexer::TokenType::SymbolMinus:
                    binaryOperator = AST::BinaryOperation::Minus;

                    break;
                case Lexer::TokenType::SymbolStar:
                    binaryOperator = AST::BinaryOperation::Star;

                    break;
                case Lexer::TokenType::SymbolSlash:
                    binaryOperator = AST::BinaryOperation::Slash;

                    break;
                default:
                    ErrorMessage("Unknown binary operation in binary expression!"_us);

                    return nullptr;
            }

            NextToken(); // skip binary operator

            auto secondExpression = ParseUnaryExpression();

            auto nextTokenPrecedence = TokenPrecedence();

            if (currentTokenPrecedence < nextTokenPrecedence) {
                secondExpression = ParseBinaryExpression(currentTokenPrecedence + 1,
                                                         secondExpression);
            }

            expression = _builder->CreateBinaryExpression(binaryOperator,
                                                          expression,
                                                          secondExpression);
        }
    }

    AST::NodePtr<AST::GS_ArrayExpression> GS_Parser::ParseArrayExpression() {
        if (!IsTokenType(Lexer::TokenType::SymbolLeftBracket)) {
            ErrorMessage("Missed symbol ']' in array expression!"_us);

            return nullptr;
        }

        NextToken(); // skip '['

        AST::GSExpressionPtrArray expressions;

        while (!IsTokenType(Lexer::TokenType::SymbolRightBracket)) {
            auto expression = ParseExpression();

            if (IsTokenType(Lexer::TokenType::SymbolComma)) {
                NextToken(); // skip ','

                if (IsTokenType(Lexer::TokenType::SymbolRightBracket)) {
                    ErrorMessage("Missed expression after ',' in array expression!"_us);

                    return nullptr;
                }
            }

            expressions.emplace_back(expression);
        }

        NextToken(); // skip ']'

        return _builder->CreateArrayExpression(expressions);
    }

    AST::NodePtr<AST::GS_VariableUsingExpression> GS_Parser::ParseVariableUsingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            ErrorMessage("Missed identifier in variable using expression!"_us);

            return nullptr;
        }

        auto variableName = TokenValue();

        NextToken(); // skip variable name

        return _builder->CreateVariableUsingExpression(variableName);
    }

    AST::NodePtr<AST::GS_FunctionCallingExpression> GS_Parser::ParseFunctionCallingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            ErrorMessage("Missed identifier in function calling expression!"_us);

            return nullptr;
        }

        auto name = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            ErrorMessage("Missed symbol '(' in function calling expression!"_us);

            return nullptr;
        }

        NextToken(); // skip '('

        AST::GSExpressionPtrArray params;

        while (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            auto param = ParseExpression();

            params.emplace_back(param);
        }

        NextToken(); // skip ')'

        return _builder->CreateFunctionCallingExpression(name, params);
    }

    AST::GSExpressionPtr GS_Parser::ParseParenExpression() {
        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            return nullptr;
        }

        NextToken(); // skip '('

        auto expression = ParseExpression();

        if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            ErrorMessage("Missed symbol ')' in paren expression!"_us);

            return nullptr;
        }

        NextToken(); // skip ')'

        return expression;
    }

    AST::GSExpressionPtr GS_Parser::ParsePrimaryExpression() {
        AST::GSExpressionPtr expression;

        expression = TryParse(&GS_Parser::ParseFunctionCallingExpression);

        if (expression) {
            return expression;
        }

        expression = TryParse(&GS_Parser::ParseVariableUsingExpression);

        if (expression) {
            return expression;
        }

        expression = TryParse(&GS_Parser::ParseConstantExpression);

        if (expression) {
            return expression;
        }

        expression = TryParse(&GS_Parser::ParseParenExpression);

        if (expression) {
            return expression;
        }

        ErrorMessage("Unknown expression!"_us);

        return nullptr;
    }

    AST::GSValuePtr GS_Parser::ParseValue() {
        if (IsTokenType(Lexer::TokenType::LiteralNumber)) {
            auto number = std::stoi(TokenValue().AsUTF8());

            NextToken(); // skip number

            return _builder->CreateI32Value(number);
        } else if (IsTokenType(Lexer::TokenType::LiteralString)) {
            auto string = TokenValue();

            NextToken(); // skip string

            return _builder->CreateStringValue(string);
        }

        ErrorMessage("Invalid value!"_us);

        return nullptr;
    }

    Semantic::GSTypePtr GS_Parser::ParseType() {
        if (IsTokenType(Lexer::TokenType::SymbolLeftBracket)) {
            NextToken(); // skip '['

            auto arrayElementsType = ParseType();

            if (!IsTokenType(Lexer::TokenType::SymbolComma)) {
                ErrorMessage("Missed symbol ',' in array type!"_us);

                return nullptr;
            }

            NextToken(); // skip ','

            if (!IsTokenType(Lexer::TokenType::LiteralNumber)) {
                ErrorMessage("Array size must be a number in array type!"_us);

                return nullptr;
            }

            auto arraySize = std::stoi(TokenValue().AsUTF8());

            NextToken(); // skip array size

            if (!IsTokenType(Lexer::TokenType::SymbolRightBracket)) {
                ErrorMessage("Missed symbol ']' in array type!"_us);

                return nullptr;
            }

            NextToken(); // skip ']'

            return _builder->CreateArrayType(arrayElementsType, arraySize);
        } else if (IsTokenType(Lexer::TokenType::Identifier)) {
            Semantic::GSTypePtr variableType;

            auto stringVariableType = TokenValue();

            NextToken(); // skip variable type

            if (stringVariableType == "Void"_us) {
                variableType = _builder->CreateVoidType();
            } else if (stringVariableType == "I32"_us) {
                variableType = _builder->CreateI32Type();
            } else if (stringVariableType == "String"_us) {
                variableType = _builder->CreateStringType();
            } else {
                variableType = _builder->CreateType(stringVariableType);
            }

            return variableType;
        }

        ErrorMessage("Invalid type!");

        return nullptr;
    }

    I32 GS_Parser::TokenPrecedence() {
        auto precedence = OperatorsPrecedence[TokenType()];

        if (!precedence) {
            return -1;
        }

        return precedence;
    }

    Bool GS_Parser::IsTokenType(Lexer::TokenType type) {
        return TokenType() == type;
    }

    Lexer::GS_Token GS_Parser::CurrentToken() {
        return *_tokenIterator;
    }

    Lexer::TokenType GS_Parser::TokenType() {
        return CurrentToken().GetType();
    }

    UString GS_Parser::TokenValue() {
        return CurrentToken().GetValue();
    }

    IO::GSByteSourceRange GS_Parser::TokenLocation() {
        return CurrentToken().GetLocationRange();
    }

    Void GS_Parser::NextToken() {
        ++_tokenIterator;
    }

    Void GS_Parser::ErrorMessage(UString messageText) {
        auto message = _session.ErrorMessage()
                               .Text(std::move(messageText))
                               .Location(TokenLocation())
                               .Message();

        _messages.emplace_back(message);
    }

    AST::GSTranslationUnitDeclarationPtr ParseProgram(LRef<Driver::GS_Session> session,
                                                      ConstLRef<IO::GS_Source> source) {
        auto tokenBuffer = Lexer::GS_Lexer::Run(session,
                                                source);

        auto program = Parser::GS_Parser::Run(session,
                                              tokenBuffer,
                                              source.GetName().GetName());

        return program;
    }

    AST::GSTranslationUnitDeclarationPtr ParseProgramFromFile(LRef<Driver::GS_Session> session,
                                                              UString fileName) {
        auto fileSource = IO::GS_Source::CreateFile(std::move(fileName));

        auto fileSourceRef = session.AddSource(std::move(fileSource));

        auto program = ParseProgram(session,
                                    fileSourceRef);

        return program;
    }

    AST::GSTranslationUnitDeclarationPtr ParseProgramFromString(LRef<Driver::GS_Session> session,
                                                                UString string) {
        auto stringSource = IO::GS_Source::CreateString(std::move(string));

        auto stringSourceRef = session.AddSource(std::move(stringSource));

        auto program = ParseProgram(session,
                                    stringSourceRef);

        return program;
    }

}