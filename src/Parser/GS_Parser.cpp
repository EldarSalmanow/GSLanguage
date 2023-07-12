#include <map>

#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    std::map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,    10},
            {Lexer::TokenType::SymbolSlash,   10},
            {Lexer::TokenType::SymbolPercent, 10},

            {Lexer::TokenType::SymbolPlus,    9},
            {Lexer::TokenType::SymbolMinus,   9},

            {Lexer::TokenType::SymbolLtLt,    8},
            {Lexer::TokenType::SymbolGtGt,    8},

            {Lexer::TokenType::SymbolAnd,     7},

            {Lexer::TokenType::SymbolCaret,   6},

            {Lexer::TokenType::SymbolOr,      5},

            {Lexer::TokenType::SymbolGtGt,    4},
            {Lexer::TokenType::SymbolGtGt,    4},

            {Lexer::TokenType::SymbolEqEq,    3},
            {Lexer::TokenType::SymbolNotEq,   3},
            {Lexer::TokenType::SymbolGt,      3},
            {Lexer::TokenType::SymbolGtEq,    3},
            {Lexer::TokenType::SymbolLt,      3},
            {Lexer::TokenType::SymbolLtEq,    3},

            {Lexer::TokenType::SymbolAndAnd,  2},

            {Lexer::TokenType::SymbolOrOr,    1}
    };

    GS_Parser::GS_Parser(LRef<Driver::GS_Session> session,
                         ConstLRef<Lexer::GS_TokenBuffer> tokenBuffer)
            : _session(session),
              _messageQueue(IO::GS_MessageQueue::Create()),
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

        _messageQueue.Flush(_session.Out());

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
        UString functionName;
        AST::GSFunctionParamArray params;
        Semantic::GSTypePtr returnType;
        AST::ExternType externType;

        if (IsTokenType(Lexer::TokenType::KeywordExtern)) {
            externType = AST::ExternType::Yes;

            NextToken(); // skip 'extern'
        } else {
            externType = AST::ExternType::No;
        }

        if (!IsTokenType(Lexer::TokenType::KeywordFunc)) {
            ErrorMessage("Missed keyword 'func' in function declaration!"_us);

            return nullptr;
        }

        NextToken(); // skip 'func'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            ErrorMessage("Invalid identifier in function declaration!"_us);

            return nullptr;
        }

        functionName = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            ErrorMessage("Missed symbol '(' in function declaration!"_us);

            return nullptr;
        }

        NextToken(); // skip '('

        while (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            if (!IsTokenType(Lexer::TokenType::Identifier)) {
                ErrorMessage("Invalid function param declaring in function declaration!");

                return nullptr;
            }

            auto name = TokenValue();

            NextToken(); // skip param name

            if (!IsTokenType(Lexer::TokenType::SymbolColon)) {
                ErrorMessage("Missed ':' in function param type declaring in function declaration!");

                return nullptr;
            }

            NextToken(); // skip ':'

            auto type = ParseType();

            auto param = _builder->CreateFunctionParam(name,
                                                       type);

            params.emplace_back(param);

            if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
                if (!IsTokenType(Lexer::TokenType::SymbolComma)) {
                    ErrorMessage("Missed ',' after function param or ')' in function declaration!");

                    return nullptr;
                }

                NextToken(); // skip ','
            }
        }

        NextToken(); // skip ')'

        if (IsTokenType(Lexer::TokenType::SymbolColon)) {
            NextToken(); // skip ':'

            returnType = ParseType();
        } else {
            returnType = nullptr;
        }

        auto functionQualifiers = _builder->CreateFunctionQualifiers(externType);
        auto functionSignature = _builder->CreateFunctionSignature(params,
                                                                   returnType,
                                                                   functionQualifiers);
        auto function = _builder->CreateFunctionDeclaration(functionName,
                                                            functionSignature);

        if (IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
            NextToken(); // skip '{'

            while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
                auto statement = ParseStatement();

                if (!statement) {
                    return nullptr;
                }

                function->AddStatement(statement);
            }

            NextToken(); // skip '}'
        }

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

    AST::NodePtr<AST::GS_IfStatement> GS_Parser::ParseIfStatement() {
        if (!IsTokenType(Lexer::TokenType::KeywordIf)) {
            ErrorMessage("");

            return nullptr;
        }

        NextToken(); // skip 'if'

        auto condition = ParseExpression();

        auto ifStatement = _builder->CreateIfStatement(condition);

        if (!IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
            ErrorMessage("");

            return nullptr;
        }

        NextToken(); // skip '{'

        while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = ParseStatement();

            if (!statement) {
                return nullptr;
            }

            ifStatement->AddIfStatement(statement);
        }

        NextToken(); // skip '}'

        return ifStatement;
    }

    AST::NodePtr<AST::GS_ForStatement> GS_Parser::ParseForStatement() {
        if (!IsTokenType(Lexer::TokenType::KeywordFor)) {
            ErrorMessage("");

            return nullptr;
        }

        return nullptr;
    }

    AST::NodePtr<AST::GS_WhileStatement> GS_Parser::ParseWhileStatement() {
        if (!IsTokenType(Lexer::TokenType::KeywordWhile)) {
            ErrorMessage("");

            return nullptr;
        }

        NextToken(); // skip 'while'

        auto condition = ParseExpression();

        auto whileStatement = _builder->CreateWhileStatement(condition);

        if (!IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
            ErrorMessage("");

            return nullptr;
        }

        NextToken(); // skip '{'

        while (!IsTokenType(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = ParseStatement();

            if (!statement) {
                return nullptr;
            }

            whileStatement->AddStatement(statement);
        }

        NextToken(); // skip '}'

        return whileStatement;
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

            return _builder->CreateUnaryExpression(AST::UnaryOperation::Neg,
                                                   expression);
        } else if (IsTokenType(Lexer::TokenType::SymbolNot)) {
            NextToken(); // skip '!'

            auto expression = ParsePrimaryExpression();

            return _builder->CreateUnaryExpression(AST::UnaryOperation::Not,
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

            auto tokenType = TokenType();

            switch (tokenType) {
                case Lexer::TokenType::SymbolPlus:
                    binaryOperator = AST::BinaryOperation::Add;

                    break;
                case Lexer::TokenType::SymbolMinus:
                    binaryOperator = AST::BinaryOperation::Sub;

                    break;
                case Lexer::TokenType::SymbolStar:
                    binaryOperator = AST::BinaryOperation::Mul;

                    break;
                case Lexer::TokenType::SymbolSlash:
                    binaryOperator = AST::BinaryOperation::Div;

                    break;
                case Lexer::TokenType::SymbolPercent:
                    binaryOperator = AST::BinaryOperation::Rem;

                    break;
                case Lexer::TokenType::SymbolAndAnd:
                    binaryOperator = AST::BinaryOperation::And;

                    break;
                case Lexer::TokenType::SymbolOrOr:
                    binaryOperator = AST::BinaryOperation::Or;

                    break;
                case Lexer::TokenType::SymbolCaret:
                    binaryOperator = AST::BinaryOperation::BitXor;

                    break;
                case Lexer::TokenType::SymbolAnd:
                    binaryOperator = AST::BinaryOperation::BitAnd;

                    break;
                case Lexer::TokenType::SymbolOr:
                    binaryOperator = AST::BinaryOperation::BitOr;

                    break;
                case Lexer::TokenType::SymbolLtLt:
                    binaryOperator = AST::BinaryOperation::Shl;

                    break;
                case Lexer::TokenType::SymbolGtGt:
                    binaryOperator = AST::BinaryOperation::Shr;

                    break;
                case Lexer::TokenType::SymbolEqEq:
                    binaryOperator = AST::BinaryOperation::Eq;

                    break;
                case Lexer::TokenType::SymbolNotEq:
                    binaryOperator = AST::BinaryOperation::Ne;

                    break;
                case Lexer::TokenType::SymbolGt:
                    binaryOperator = AST::BinaryOperation::Gt;

                    break;
                case Lexer::TokenType::SymbolGtEq:
                    binaryOperator = AST::BinaryOperation::Ge;

                    break;
                case Lexer::TokenType::SymbolLt:
                    binaryOperator = AST::BinaryOperation::Lt;

                    break;
                case Lexer::TokenType::SymbolLtEq:
                    binaryOperator = AST::BinaryOperation::Le;

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

            if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
                if (!IsTokenType(Lexer::TokenType::SymbolComma)) {
                    ErrorMessage("Missed ',' after function argument or ')' in function calling expression!");

                    return nullptr;
                }

                NextToken(); // skip ','
            }
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
        if (IsTokenType(Lexer::TokenType::LiteralSymbol)) {
            auto symbol = TokenValue()[0];

            NextToken();

            return _builder->CreateCharValue(symbol);
        } else if (IsTokenType(Lexer::TokenType::LiteralNumber)) {
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
            } else if (stringVariableType == "Char"_us) {
                variableType = _builder->CreateCharType();
            } else if (stringVariableType == "I8"_us) {
                variableType = _builder->CreateI8Type();
            } else if (stringVariableType == "I16"_us) {
                variableType = _builder->CreateI16Type();
            } else if (stringVariableType == "I32"_us) {
                variableType = _builder->CreateI32Type();
            } else if (stringVariableType == "I64"_us) {
                variableType = _builder->CreateI64Type();
            } else if (stringVariableType == "U8"_us) {
                variableType = _builder->CreateU8Type();
            } else if (stringVariableType == "U16"_us) {
                variableType = _builder->CreateU16Type();
            } else if (stringVariableType == "U32"_us) {
                variableType = _builder->CreateU32Type();
            } else if (stringVariableType == "U64"_us) {
                variableType = _builder->CreateU64Type();
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

    IO::GS_SourceRange GS_Parser::TokenLocation() {
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

        _messageQueue.AddMessage(message);
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