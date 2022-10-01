#include <map>

#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    std::map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,  2},
            {Lexer::TokenType::SymbolSlash, 2},
            {Lexer::TokenType::SymbolPlus,  1},
            {Lexer::TokenType::SymbolMinus, 1}
    };

    GS_Parser::GS_Parser(Driver::GSContextPtr context)
            : _context(std::move(context)),
              _messages(IO::GSMessagePtrArray()),
              _tokens(Lexer::GSTokenArray()),
              _tokensIterator(Lexer::GSTokenArrayIterator()),
              _builder(AST::GS_ASTBuilder::Create(_context->GetASTContext())) {}

    GS_Parser GS_Parser::Create(Driver::GSContextPtr context) {
        return GS_Parser(std::move(context));
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::ParseProgram(LRef<Driver::GS_CompilationUnit> compilationUnit) {
        _messages = IO::GSMessagePtrArray();

        _tokens = compilationUnit.GetTokens();

        _tokensIterator = _tokens.begin();

        auto translationUnitDeclaration = ParseTranslationUnitDeclaration(compilationUnit.GetSource()->GetName().GetName());

        for (auto &message : _messages) {
            message->Write(_context);
        }

        _messages = IO::GSMessagePtrArray();

        _tokens = Lexer::GSTokenArray();

        _tokensIterator = Lexer::GSTokenArrayIterator();

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
        if (IsTokenType(Lexer::TokenType::KeywordFunc)) {
            return ParseFunctionDeclaration();
        }

        UStringStream stringStream;

        stringStream << "Unknown declaration!"_us;

        LocatedMessage(stringStream.String(),
                       IO::MessageLevel::Error,
                       TokenLocation());

        return nullptr;
    }

    std::shared_ptr<AST::GS_FunctionDeclaration> GS_Parser::ParseFunctionDeclaration() {
        if (!IsTokenType(Lexer::TokenType::KeywordFunc)) {
            UStringStream stringStream;

            stringStream << "Missed keyword 'func' in function declaration!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip 'func'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            UStringStream stringStream;

            stringStream << "Invalid identifier in function declaration!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        auto functionName = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            UStringStream stringStream;

            stringStream << "Missed symbol '(' in function declaration!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip '('

        if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            UStringStream stringStream;

            stringStream << "Missed symbol ')' in function declaration!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip ')'

        if (!IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
            UStringStream stringStream;

            stringStream << "Missed symbol '{' in function declaration!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip '{'

        auto function = _builder->CreateFunctionDeclaration(functionName);

        while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = ParseStatement();

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

        return ParseExpressionStatement();
    }

    std::shared_ptr<AST::GS_AssignmentStatement> GS_Parser::ParseAssignmentStatement() {
        auto lvalueExpression = ParseLValueExpression();

        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            UStringStream stringStream;

            stringStream << "Missed symbol '=' in assignment statement!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip '='

        auto rvalueExpression = ParseRValueExpression();

        auto assignmentStatement = _builder->CreateAssignmentStatement(lvalueExpression, rvalueExpression);

        return assignmentStatement;
    }

    std::shared_ptr<AST::GS_VariableDeclarationStatement> GS_Parser::ParseVariableDeclarationStatement() {
        UString variableName;
        Semantic::GSTypePtr variableType;
        AST::GSExpressionPtr variableExpression;

        if (!IsTokenType(Lexer::TokenType::KeywordVar)) {
            UStringStream stringStream;

            stringStream << "Missed keyword 'var' in variable declaration statement!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip 'var'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            UStringStream stringStream;

            stringStream << "Invalid identifier in variable declaration statement!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        variableName = TokenValue();

        NextToken(); // skip variable name

        if (IsTokenType(Lexer::TokenType::SymbolColon)) {
            NextToken(); // skip ':'

            variableType = ParseType();
        }

        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            UStringStream stringStream;

            stringStream << "Missed symbol '=' in variable declaration statement!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        NextToken(); // skip '='

        variableExpression = ParseExpression();

        auto variable = _builder->CreateVariableDeclarationStatement(variableName, variableType, variableExpression);

        return variable;
    }

    std::shared_ptr<AST::GS_ExpressionStatement> GS_Parser::ParseExpressionStatement() {
        auto expression = ParseExpression();

        auto expressionStatement = _builder->CreateExpressionStatement(expression);

        return expressionStatement;
    }

    AST::GSExpressionPtr GS_Parser::ParseExpression() {
        auto expression = ParseUnaryExpression();

        return ParseBinaryExpression(0, expression);
    }

    AST::GSExpressionPtr GS_Parser::ParseLValueExpression() {
        if (IsTokenType(Lexer::TokenType::Identifier)) {
            return ParseVariableUsingExpression();
        }

        UStringStream stringStream;

        stringStream << "Unknown left value expression!"_us;

        LocatedMessage(stringStream.String(),
                       IO::MessageLevel::Error,
                       TokenLocation());

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseRValueExpression() {
        auto expression = ParseUnaryExpression();

        return ParseBinaryExpression(0, expression);
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

            return _builder->CreateUnaryExpression(AST::UnaryOperation::Minus, expression);
        }

        return ParsePrimaryExpression();
    }

    AST::GSExpressionPtr GS_Parser::ParseBinaryExpression(I32 expressionPrecedence, LRef<AST::GSExpressionPtr> expression) {
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
                    UStringStream stringStream;

                    stringStream << "Unknown binary operation in binary expression!"_us;

                    LocatedMessage(stringStream.String(),
                                   IO::MessageLevel::Error,
                                   TokenLocation());

                    return nullptr;
            }

            NextToken(); // skip binary operator

            auto secondExpression = ParseUnaryExpression();

            auto nextTokenPrecedence = TokenPrecedence();

            if (currentTokenPrecedence < nextTokenPrecedence) {
                secondExpression = ParseBinaryExpression(currentTokenPrecedence + 1, secondExpression);
            }

            expression = _builder->CreateBinaryExpression(binaryOperator, expression, secondExpression);
        }
    }

    AST::GSExpressionPtr GS_Parser::ParseVariableUsingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            UStringStream stringStream;

            stringStream << "Missed identifier in variable using expression!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        auto variableName = TokenValue();

        NextToken(); // skip variable name

        return _builder->CreateVariableUsingExpression(variableName);
    }

    AST::GSExpressionPtr GS_Parser::ParseFunctionCallingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            UStringStream stringStream;

            stringStream << "Missed identifier in function calling expression!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        auto name = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            UStringStream stringStream;

            stringStream << "Missed symbol '(' in function calling expression!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

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

        if (IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            NextToken(); // skip '('

            expression = ParseExpression();

            if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
                UStringStream stringStream;

                stringStream << "Missed symbol ')'!"_us;

                LocatedMessage(stringStream.String(),
                               IO::MessageLevel::Error,
                               TokenLocation());

                return nullptr;
            }

            NextToken(); // skip ')'

            return expression;
        }

        UStringStream stringStream;

        stringStream << "Unknown expression!"_us;

        LocatedMessage(stringStream.String(),
                       IO::MessageLevel::Error,
                       TokenLocation());

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

        UStringStream stringStream;

        stringStream << "Invalid value!"_us;

        LocatedMessage(stringStream.String(),
                       IO::MessageLevel::Error,
                       TokenLocation());

        return nullptr;
    }

    Semantic::GSTypePtr GS_Parser::ParseType() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            UStringStream stringStream;

            stringStream << "Missed type name!"_us;

            LocatedMessage(stringStream.String(),
                           IO::MessageLevel::Error,
                           TokenLocation());

            return nullptr;
        }

        auto stringVariableType = TokenValue();

        NextToken(); // skip variable type

        Semantic::GSTypePtr variableType;

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
        return *_tokensIterator;
    }

    Lexer::TokenType GS_Parser::TokenType() {
        return CurrentToken().GetType();
    }

    UString GS_Parser::TokenValue() {
        return CurrentToken().GetValue();
    }

    IO::GS_SourceLocation GS_Parser::TokenLocation() {
        return CurrentToken().GetLocation();
    }

    Void GS_Parser::NextToken() {
        ++_tokensIterator;
    }

    Void GS_Parser::Message(UString message, IO::MessageLevel messageLevel) {
        auto textMessage = IO::GS_TextMessage::Create(std::move(message), messageLevel);

        _messages.emplace_back(textMessage);
    }

    Void GS_Parser::LocatedMessage(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation messageLocation) {
        auto locatedTextMessage = IO::GS_LocatedTextMessage::Create(std::move(message), messageLevel, messageLocation);

        _messages.emplace_back(locatedTextMessage);
    }

}