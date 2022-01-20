#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    Map<Lexer::TokenType, I32> OperatorsPrecedence = {
            {Lexer::TokenType::SymbolStar,  2},
            {Lexer::TokenType::SymbolSlash, 2},
            {Lexer::TokenType::SymbolPlus,  1},
            {Lexer::TokenType::SymbolMinus, 1}
    };

    GS_Parser::GS_Parser(Ptr<Lexer::GS_TokenStream> stream)
            : _tokenStream(stream) {}

    AST::GSDeclarationPtrArray GS_Parser::parse() {
        return _parseProgram();
    }

    AST::GSDeclarationPtrArray GS_Parser::_parseProgram() {
        AST::GSDeclarationPtrArray declarations;

        while (!_isEqualTokenTypes(Lexer::TokenType::EndOfFile)) {
            declarations.emplace_back(_parseDeclaration());
        }

        return declarations;
    }

    AST::GSDeclarationPtr GS_Parser::_parseDeclaration() {
        if (_isEqualTokenTypes(Lexer::TokenType::KeywordFunc)) {
            return _parseFunctionDeclaration();
        } else if (_isEqualTokenTypes(Lexer::TokenType::KeywordVar)) {
            return _parseVariableDeclaration();
        } else {
            throw std::runtime_error("Unknown declaration!");
        }
    }

    AST::GSDeclarationPtr GS_Parser::_parseFunctionDeclaration() {
        if (!_isEqualTokenTypes(Lexer::TokenType::KeywordFunc)) {
            throw std::runtime_error("Invalid function declaration! Missing 'func' keyword!");
        }

        _nextToken(); // skip 'func'

        if (!_isEqualTokenTypes(Lexer::TokenType::Identifier)) {
            throw std::runtime_error("Invalid function name!");
        }

        auto functionName = ReinterpretCast<Ptr<Lexer::GS_ValueToken>>(_token.get())->getValue();

        _nextToken(); // skip function name

        if (!_isEqualTokenTypes(Lexer::TokenType::SymbolLeftParen)) {
            throw std::runtime_error("Missing \'(\'!");
        }

        _nextToken(); // skip '('

        if (!_isEqualTokenTypes(Lexer::TokenType::SymbolRightParen)) {
            throw std::runtime_error("Missing \')\'!");
        }

        _nextToken(); // skip ')'

        if (!_isEqualTokenTypes(Lexer::TokenType::SymbolLeftBrace)) {
            throw std::runtime_error("Missing \'{\'!");
        }

        _nextToken(); // skip '{'

        AST::GSStatementPtrArray functionBody;

        while (!_isEqualTokenTypes(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = _parseStatement();

            functionBody.emplace_back(statement);
        }

        _nextToken(); // skip '}'

        return std::make_shared<AST::GS_FunctionDeclaration>(functionName, functionBody);
    }

    AST::GSStatementPtr GS_Parser::_parseVariableDeclaration() {
        _tokenStream.next(); // skip 'var'

        if (!_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
            throw std::runtime_error("Invalid variable name!");
        }

        auto variableName = _tokenStream.tokenValue();

        _tokenStream.next(); // skip variable name

        if (!_tokenStream.isEqualTypes(Lexer::TokenType::SymbolColon)) {
            throw std::runtime_error("Can`t declare variable without type!");
        }

        _tokenStream.next(); // skip ':'

        if (!_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
            throw std::runtime_error("Invalid type name!");
        }

        auto typeName = _tokenStream.tokenValue();

        AST::GSTypePtr variableType;

        if (typeName == "I32") {
            variableType = std::make_shared<AST::GS_I32Type>();
        } else if (typeName == "String") {
            variableType = std::make_shared<AST::GS_StringType>();
        } else {
            throw std::runtime_error("Unknown type name!");
        }

        _tokenStream.next(); // skip variable type

        return std::make_shared<AST::GS_VariableDeclaration>(variableName, variableType);
    }

    AST::GSStatementPtr GS_Parser::_parseStatement() {
        if (_tokenStream.isEqualTypes(Lexer::TokenType::KeywordVar)
         || _tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
            return _parseAssignmentStatement();
        } else {
            return std::make_shared<AST::GS_ExpressionStatement>(_parseExpression());
        }
    }

    AST::GSStatementPtr GS_Parser::_parseAssignmentStatement() {
        AST::GSStatementPtr statement;

        if (_tokenStream.isEqualTypes(Lexer::TokenType::KeywordVar)) {
            statement = _parseVariableDeclarationStatement();
        } else if (_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
            statement = std::make_shared<AST::GS_ExpressionStatement>(_parsePrimaryExpression());
        }

        if (_tokenStream.isEqualTypes(Lexer::TokenType::SymbolEq)) {
            _tokenStream.next(); // skip '='

            auto expression = _parseExpression();

            return std::make_shared<AST::GS_AssignmentStatement>(statement, expression);
        }

        return statement;
    }

    AST::GSExpressionPtr GS_Parser::_parseExpression() {
        auto expression = _parseUnaryExpression();

        return _parseBinaryExpression(0, expression);
    }

    AST::GSExpressionPtr GS_Parser::_parseBinaryExpression(I32 expressionPrecedence, AST::GSExpressionPtr expression) {
        while (true) {
            auto currentTokenPrecedence = _currentTokenPrecedence();

            if (currentTokenPrecedence < expressionPrecedence) {
                return expression;
            }

            AST::BinaryOperation binaryOperator;

            switch (_tokenStream.tokenType()) {
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
                    throw std::runtime_error("Unknown binary operator!");
            }

            _tokenStream.next(); // skip binary operator

            auto secondExpression = _parseUnaryExpression();

            auto nextTokenPrecedence = _currentTokenPrecedence();

            if (currentTokenPrecedence < nextTokenPrecedence) {
                secondExpression = _parseBinaryExpression(currentTokenPrecedence + 1, secondExpression);
            }

            expression = std::make_shared<AST::GS_BinaryExpression>(binaryOperator, expression, secondExpression);
        }
    }

    AST::GSExpressionPtr GS_Parser::_parseUnaryExpression() {
        if (_tokenStream.isEqualTypes(Lexer::TokenType::SymbolMinus)) {
            _tokenStream.next();

            return std::make_shared<AST::GS_UnaryExpression>(AST::UnaryOperation::Minus, _parsePrimaryExpression());
        }

        return _parsePrimaryExpression();
    }

    AST::GSExpressionPtr GS_Parser::_parsePrimaryExpression() {
        if (_tokenStream.isEqualTypes(Lexer::TokenType::LiteralNumber)) {
            auto value = _tokenStream.tokenValue();

            _tokenStream.next();

            return std::make_shared<AST::GS_ConstantExpression>(std::make_shared<AST::GS_I32Value>(std::stoi(value)));
        } else if (_tokenStream.isEqualTypes(Lexer::TokenType::Identifier)) {
            auto value = _tokenStream.tokenValue();

            _tokenStream.next();

            return std::make_shared<AST::GS_VariableUsingExpression>(value);
        } else if (_tokenStream.isEqualTypes(Lexer::TokenType::SymbolLeftParen)) {
            _tokenStream.next();

            auto expression = _parseExpression();

            if (!_tokenStream.isEqualTypes(Lexer::TokenType::SymbolRightParen)) {
                throw std::runtime_error("Missed \')\'!");
            }

            _tokenStream.next();

            return expression;
        } else {
            throw std::runtime_error("Unknown expression!");
        }
    }

    Void GS_Parser::_nextToken() {
        _token = _tokenStream->getToken();
    }

    I32 GS_Parser::_currentTokenPrecedence() {
        auto precedence = OperatorsPrecedence[_token->getTokenType()];

        if (!precedence) {
            return -1;
        }

        return precedence;
    }

    Bool GS_Parser::_isEqualTokenTypes(Lexer::TokenType type) {
        return _token->getTokenType() == type;
    }

}