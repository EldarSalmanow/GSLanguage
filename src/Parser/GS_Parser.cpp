#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    // TODO add normal error handler

    Map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,  2},
            {Lexer::TokenType::SymbolSlash, 2},
            {Lexer::TokenType::SymbolPlus,  1},
            {Lexer::TokenType::SymbolMinus, 1}
    };

    GS_Parser::GS_Parser(LRef<Lexer::GS_TokenStream> tokenStream)
            : _stream(tokenStream), _builder(AST::GS_ASTBuilder::Create()) {}

    AST::GSTranslationUnitDeclarationPtr GS_Parser::Parse() {
        return ParseTranslationUnitDeclaration();
    }

    AST::GSTranslationUnitDeclarationPtr GS_Parser::ParseTranslationUnitDeclaration() {
        // TODO update getting TU name
        auto unit = _builder->CreateTranslationUnitDeclaration(""_us);

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

        return nullptr;
    }

    SharedPtr<AST::GS_FunctionDeclaration> GS_Parser::ParseFunctionDeclaration() {
        if (!IsTokenType(Lexer::TokenType::KeywordFunc)) {
            return nullptr;
        }

        NextToken(); // skip 'func'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        auto functionName = TokenValue();

        NextToken(); // skip function name

        if (!IsTokenType(Lexer::TokenType::SymbolLeftParen)) {
            return nullptr;
        }

        NextToken(); // skip '('

        if (!IsTokenType(Lexer::TokenType::SymbolRightParen)) {
            return nullptr;
        }

        NextToken(); // skip ')'

        if (!IsTokenType(Lexer::TokenType::SymbolLeftBrace)) {
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
        // TODO update statement parsing process (add TryParse method ?)

        if (IsTokenType(Lexer::TokenType::KeywordVar)) {
            return ParseVariableDeclarationStatement();
        }

        auto expression = ParseExpression();

        if (IsTokenType(Lexer::TokenType::SymbolEq)) {
            return ParseAssignmentStatement(expression);
        }

        return ParseExpressionStatement(expression);
    }

    SharedPtr<AST::GS_AssignmentStatement> GS_Parser::ParseAssignmentStatement() {
        auto lvalueExpression = ParseLValueExpression();

        return ParseAssignmentStatement(lvalueExpression); // TODO remove or modify
    }

    SharedPtr<AST::GS_AssignmentStatement> GS_Parser::ParseAssignmentStatement(ConstLRef<AST::GSExpressionPtr> lvalueExpression) {
        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            return nullptr;
        }

        NextToken(); // skip '='

        auto rvalueExpression = ParseRValueExpression();

        auto assignmentStatement = _builder->CreateAssignmentStatement(lvalueExpression, rvalueExpression);

        return assignmentStatement;
    }

    SharedPtr<AST::GS_VariableDeclarationStatement> GS_Parser::ParseVariableDeclarationStatement() {
        UString variableName;
        AST::GSTypePtr variableType;
        AST::GSExpressionPtr variableExpression;

        if (!IsTokenType(Lexer::TokenType::KeywordVar)) {
            return nullptr;
        }

        NextToken(); // skip 'var'

        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        variableName = TokenValue();

        NextToken(); // skip variable name

        if (IsTokenType(Lexer::TokenType::SymbolColon)) {
            NextToken(); // skip ':'

            variableType = ParseType();

//            if (variableType->GetName() == U"Void") {
//                return nullptr;
//            } TODO add semantic check and remove
        }

        if (!IsTokenType(Lexer::TokenType::SymbolEq)) {
            return nullptr;
        }

        NextToken(); // skip '='

        variableExpression = ParseRValueExpression();

        auto variable = _builder->CreateVariableDeclarationStatement(variableName, variableType, variableExpression);

        return variable;
    }

    SharedPtr<AST::GS_ExpressionStatement> GS_Parser::ParseExpressionStatement() {
        auto expression = ParseExpression();

        return ParseExpressionStatement(expression); // TODO remove of modify
    }

    SharedPtr<AST::GS_ExpressionStatement> GS_Parser::ParseExpressionStatement(ConstLRef<AST::GSExpressionPtr> expression) {
        auto expressionStatement = _builder->CreateExpressionStatement(expression);

        return expressionStatement;
    }

    AST::GSExpressionPtr GS_Parser::ParseExpression() {
        // TODO update parsing expression process

        auto expression = ParseLValueExpression();

        if (!expression) {
            expression = ParseRValueExpression();
        }

        return expression;
    }

    AST::GSExpressionPtr GS_Parser::ParseLValueExpression() {
        if (IsTokenType(Lexer::TokenType::Identifier)) {
            return ParseVariableUsingExpression();
        }

        return nullptr;
    }

    AST::GSExpressionPtr GS_Parser::ParseRValueExpression() {
        auto expression = ParseUnaryExpression();

        return ParseBinaryExpression(0, expression);
    }

    AST::GSExpressionPtr GS_Parser::ParseVariableUsingExpression() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        auto variableName = TokenValue();

        NextToken(); // skip variable name

        return _builder->CreateVariableUsingExpression(variableName);
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
                    throw UException("Unknown binary operator!"_us); // TODO remove
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

    AST::GSExpressionPtr GS_Parser::ParseUnaryExpression() {
        if (IsTokenType(Lexer::TokenType::SymbolMinus)) {
            NextToken(); // skip '-'

            auto constantExpression = ParseConstantExpression();

            return _builder->CreateUnaryExpression(AST::UnaryOperation::Minus, constantExpression);
        }

        return ParseConstantExpression();
    }

    // TODO move to UString (GSCrossPlatform)
    inline I32 AsI32(ConstLRef<UString> string) {
        return std::stoi(string.AsString());
    }

    AST::GSExpressionPtr GS_Parser::ParseConstantExpression() {
        if (IsTokenType(Lexer::TokenType::LiteralNumber)) {
            auto number = _builder->CreateI32Value(AsI32(TokenValue()));

            NextToken(); // skip number

            return _builder->CreateConstantExpression(number);
        } else if (IsTokenType(Lexer::TokenType::LiteralString)) {
            auto string = _builder->CreateStringValue(TokenValue());

            NextToken();

            return _builder->CreateConstantExpression(string);
        } else if (IsTokenType(Lexer::TokenType::Identifier)) {
            return ParseVariableUsingExpression();
        }

        return nullptr;
    }

    AST::GSValuePtr GS_Parser::ParseValue() {
        if (IsTokenType(Lexer::TokenType::LiteralNumber)) {
            auto number = AsI32(TokenValue());

            NextToken(); // skip number

            return _builder->CreateI32Value(number);
        } else if (IsTokenType(Lexer::TokenType::LiteralString)) {
            auto string = TokenValue();

            NextToken();

            return _builder->CreateStringValue(string);
        }

        return nullptr;
    }

    AST::GSTypePtr GS_Parser::ParseType() {
        if (!IsTokenType(Lexer::TokenType::Identifier)) {
            return nullptr;
        }

        auto stringVariableType = TokenValue();

        NextToken(); // skip variable type

        AST::GSTypePtr variableType;

        if (stringVariableType == "Void"_us) {
            variableType = _builder->CreateVoidType();
        } else if (stringVariableType == "I32"_us) {
            variableType = _builder->CreateI32Type();
        } else if (stringVariableType == "String"_us) {
            variableType = _builder->CreateStringType();
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

    UString GS_Parser::TokenValue() {
        return CurrentToken().GetValue();
    }

    Lexer::TokenType GS_Parser::TokenType() {
        return CurrentToken().GetType();
    }

    Lexer::GS_Token GS_Parser::CurrentToken() {
        return _stream.CurrentToken();
    }

    Void GS_Parser::NextToken() {
        _stream.NextToken();
    }

//    Map<Lexer::TokenType, I32> OperatorsPrecedence = {
//            {Lexer::TokenType::SymbolStar,  2},
//            {Lexer::TokenType::SymbolSlash, 2},
//            {Lexer::TokenType::SymbolPlus,  1},
//            {Lexer::TokenType::SymbolMinus, 1}
//    };
//
//    GS_Parser::GS_Parser(Ptr<Lexer::GS_TokenStream> stream)
//            : _tokenStream(stream) {}
//
//    AST::GSDeclarationPtrArray GS_Parser::parse() {
//        return _parseProgram();
//    }
//
//    AST::GSDeclarationPtrArray GS_Parser::_parseProgram() {
//        AST::GSDeclarationPtrArray declarations;
//
//        while (!_isEqualTokenTypes(Lexer::TokenType::EndOfFile)) {
//            declarations.emplace_back(_parseDeclaration());
//        }
//
//        return declarations;
//    }
//
//    AST::GSDeclarationPtr GS_Parser::_parseDeclaration() {
//        if (_isEqualTokenTypes(Lexer::TokenType::KeywordFunc)) {
//            return _parseFunctionDeclaration();
//        } else if (_isEqualTokenTypes(Lexer::TokenType::KeywordVar)) {
//            return _parseVariableDeclaration();
//        } else {
//            throw std::runtime_error("Unknown declaration!");
//        }
//    }
//
//    AST::GSDeclarationPtr GS_Parser::_parseFunctionDeclaration() {
//        if (!_isEqualTokenTypes(Lexer::TokenType::KeywordFunc)) {
//            throw std::runtime_error("Invalid function declaration! Missing 'func' keyword!");
//        }
//
//        _nextToken(); // skip 'func'
//
//        if (!_isEqualTokenTypes(Lexer::TokenType::Identifier)) {
//            throw std::runtime_error("Invalid function name!");
//        }
//
//        auto functionName = ReinterpretCast<Ptr<Lexer::GS_ValueToken>>(_token.get())->getValue();
//
//        _nextToken(); // skip function name
//
//        if (!_isEqualTokenTypes(Lexer::TokenType::SymbolLeftParen)) {
//            throw std::runtime_error("Missing \'(\'!");
//        }
//
//        _nextToken(); // skip '('
//
//        if (!_isEqualTokenTypes(Lexer::TokenType::SymbolRightParen)) {
//            throw std::runtime_error("Missing \')\'!");
//        }
//
//        _nextToken(); // skip ')'
//
//        if (!_isEqualTokenTypes(Lexer::TokenType::SymbolLeftBrace)) {
//            throw std::runtime_error("Missing \'{\'!");
//        }
//
//        _nextToken(); // skip '{'
//
//        AST::GSStatementPtrArray functionBody;
//
//        while (!_isEqualTokenTypes(Lexer::TokenType::SymbolRightBrace)) {
//            auto statement = _parseStatement();
//
//            functionBody.emplace_back(statement);
//        }
//
//        _nextToken(); // skip '}'
//
//        return std::make_shared<AST::GS_FunctionDeclaration>(functionName, functionBody);
//    }
//
//    AST::GSStatementPtr GS_Parser::_parseVariableDeclaration() {
//        _tokenStream.next(); // skip 'var'
//
//        if (!_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
//            throw std::runtime_error("Invalid variable name!");
//        }
//
//        auto variableName = _tokenStream.tokenValue();
//
//        _tokenStream.next(); // skip variable name
//
//        if (!_tokenStream.isEqualTypes(Lexer::TokenType::SymbolColon)) {
//            throw std::runtime_error("Can`t declare variable without type!");
//        }
//
//        _tokenStream.next(); // skip ':'
//
//        if (!_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
//            throw std::runtime_error("Invalid type name!");
//        }
//
//        auto typeName = _tokenStream.tokenValue();
//
//        AST::GSTypePtr variableType;
//
//        if (typeName == "I32") {
//            variableType = std::make_shared<AST::GS_I32Type>();
//        } else if (typeName == "String") {
//            variableType = std::make_shared<AST::GS_StringType>();
//        } else {
//            throw std::runtime_error("Unknown type name!");
//        }
//
//        _tokenStream.next(); // skip variable type
//
//        return std::make_shared<AST::GS_VariableDeclaration>(variableName, variableType);
//    }
//
//    AST::GSStatementPtr GS_Parser::_parseStatement() {
//        if (_tokenStream.isEqualTypes(Lexer::TokenType::KeywordVar)
//         || _tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
//            return _parseAssignmentStatement();
//        } else {
//            return std::make_shared<AST::GS_ExpressionStatement>(_parseExpression());
//        }
//    }
//
//    AST::GSStatementPtr GS_Parser::_parseAssignmentStatement() {
//        AST::GSStatementPtr statement;
//
//        if (_tokenStream.isEqualTypes(Lexer::TokenType::KeywordVar)) {
//            statement = _parseVariableDeclarationStatement();
//        } else if (_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
//            statement = std::make_shared<AST::GS_ExpressionStatement>(_parsePrimaryExpression());
//        }
//
//        if (_tokenStream.isEqualTypes(Lexer::TokenType::SymbolEq)) {
//            _tokenStream.next(); // skip '='
//
//            auto expression = _parseExpression();
//
//            return std::make_shared<AST::GS_AssignmentStatement>(statement, expression);
//        }
//
//        return statement;
//    }
//
//    AST::GSExpressionPtr GS_Parser::_parseExpression() {
//        auto expression = _parseUnaryExpression();
//
//        return _parseBinaryExpression(0, expression);
//    }
//
//    AST::GSExpressionPtr GS_Parser::_parseBinaryExpression(I32 expressionPrecedence, AST::GSExpressionPtr expression) {
//        while (true) {
//            auto currentTokenPrecedence = _currentTokenPrecedence();
//
//            if (currentTokenPrecedence < expressionPrecedence) {
//                return expression;
//            }
//
//            AST::BinaryOperation binaryOperator;
//
//            switch (_tokenStream.tokenType()) {
//                case Lexer::TokenType::SymbolPlus:
//                    binaryOperator = AST::BinaryOperation::Plus;
//
//                    break;
//                case Lexer::TokenType::SymbolMinus:
//                    binaryOperator = AST::BinaryOperation::Minus;
//
//                    break;
//                case Lexer::TokenType::SymbolStar:
//                    binaryOperator = AST::BinaryOperation::Star;
//
//                    break;
//                case Lexer::TokenType::SymbolSlash:
//                    binaryOperator = AST::BinaryOperation::Slash;
//
//                    break;
//                default:
//                    throw std::runtime_error("Unknown binary operator!");
//            }
//
//            _tokenStream.next(); // skip binary operator
//
//            auto secondExpression = _parseUnaryExpression();
//
//            auto nextTokenPrecedence = _currentTokenPrecedence();
//
//            if (currentTokenPrecedence < nextTokenPrecedence) {
//                secondExpression = _parseBinaryExpression(currentTokenPrecedence + 1, secondExpression);
//            }
//
//            expression = std::make_shared<AST::GS_BinaryExpression>(binaryOperator, expression, secondExpression);
//        }
//    }
//
//    AST::GSExpressionPtr GS_Parser::_parseUnaryExpression() {
//        if (_tokenStream.isEqualTypes(Lexer::TokenType::SymbolMinus)) {
//            _tokenStream.next();
//
//            return std::make_shared<AST::GS_UnaryExpression>(AST::UnaryOperation::Minus, _parsePrimaryExpression());
//        }
//
//        return _parsePrimaryExpression();
//    }
//
//    AST::GSExpressionPtr GS_Parser::_parsePrimaryExpression() {
//        if (_tokenStream.isEqualTypes(Lexer::TokenType::LiteralNumber)) {
//            auto value = _tokenStream.tokenValue();
//
//            _tokenStream.next();
//
//            return std::make_shared<AST::GS_ConstantExpression>(std::make_shared<AST::GS_I32Value>(std::stoi(value)));
//        } else if (_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
//            auto value = _tokenStream.tokenValue();
//
//            _tokenStream.next();
//
//            return std::make_shared<AST::GS_VariableUsingExpression>(value);
//        } else if (_tokenStream.isEqualTypes(Lexer::TokenType::SymbolLeftParen)) {
//            _tokenStream.next();
//
//            auto expression = _parseExpression();
//
//            if (!_tokenStream.isEqualTypes(Lexer::TokenType::SymbolRightParen)) {
//                throw std::runtime_error("Missed \')\'!");
//            }
//
//            _tokenStream.next();
//
//            return expression;
//        } else {
//            throw std::runtime_error("Unknown expression!");
//        }
//    }
//
//    Void GS_Parser::_nextToken() {
//        _token = _tokenStream->getToken();
//    }
//
//    I32 GS_Parser::_currentTokenPrecedence() {
//        auto precedence = OperatorsPrecedence[_token->getTokenType()];
//
//        if (!precedence) {
//            return -1;
//        }
//
//        return precedence;
//    }
//
//    Bool GS_Parser::_isEqualTokenTypes(Lexer::TokenType type) {
//        return _token->getTokenType() == type;
//    }

}