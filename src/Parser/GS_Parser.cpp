#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    GS_Parser::GS_Parser(Lexer::GSTokenArray tokens)
            : _tokens(std::move(tokens)), _tokenIterator(_tokens.begin()) {
        _operatorsPrecedence[Lexer::TokenType::SymbolStar]  = 2;
        _operatorsPrecedence[Lexer::TokenType::SymbolSlash] = 2;
        _operatorsPrecedence[Lexer::TokenType::SymbolPlus]  = 1;
        _operatorsPrecedence[Lexer::TokenType::SymbolMinus] = 1;
    }

    AST::GSDeclarationPtrArray GS_Parser::parse() {
        return _parseProgram();
    }

    AST::GSDeclarationPtrArray GS_Parser::_parseProgram() {
        AST::GSDeclarationPtrArray declarations;

        while (!_checkTokenType(Lexer::TokenType::EndOfFile)) {
            declarations.emplace_back(_parseDeclaration());
        }

        return declarations;
    }

    AST::GSDeclarationPtr GS_Parser::_parseDeclaration() {
        if (_checkTokenType(Lexer::TokenType::KeywordFunc)) {
            return _parseFunctionDeclaration();
        } else {
            throw std::runtime_error("Unknown declaration!");
        }
    }

    AST::GSDeclarationPtr GS_Parser::_parseFunctionDeclaration() {
        _nextToken(); // skip 'func'

        if (!_checkTokenType(Lexer::TokenType::Identifier)) {
            throw std::runtime_error("Invalid function name!");
        }

        auto functionName = _currentToken().getValue();

        _nextToken(); // skip function name

        if (!_checkTokenType(Lexer::TokenType::SymbolLeftParen)) {
            throw std::runtime_error("Missing \'(\'!");
        }

        _nextToken(); // skip '('

        if (!_checkTokenType(Lexer::TokenType::SymbolRightParen)) {
            throw std::runtime_error("Missing \')\'!");
        }

        _nextToken(); // skip ')'

        if (!_checkTokenType(Lexer::TokenType::SymbolLeftBrace)) {
            throw std::runtime_error("Missing \'{\'!");
        }

        _nextToken(); // skip '{'

        AST::GSStatementPtrArray functionBody;

        while (!_checkTokenType(Lexer::TokenType::SymbolRightBrace)) {
            auto statement = _parseStatement();

            functionBody.emplace_back(statement);
        }

        _nextToken(); // skip '}'

        return std::make_shared<AST::GS_FunctionDeclaration>(functionName, functionBody);
    }

    AST::GSStatementPtr GS_Parser::_parseStatement() {
        if (_checkTokenType(Lexer::TokenType::KeywordVar) || _checkTokenType(Lexer::TokenType::Identifier)) {
            auto statement = _parseAssignmentStatement();

            if (statement) {
                return statement;
            }
        }

        return std::make_shared<AST::GS_ExpressionStatement>(_parseExpression());
    }

    AST::GSStatementPtr GS_Parser::_parseVariableDeclarationStatement() {
        _nextToken(); // skip 'var'

        if (!_checkTokenType(Lexer::TokenType::Identifier)) {
            throw std::runtime_error("Invalid variable name!");
        }

        auto variableName = _currentToken().getValue();

        _nextToken(); // skip variable name

        if (!_checkTokenType(Lexer::TokenType::SymbolColon)) {
            throw std::runtime_error("Can`t declare variable without type!");
        }

        _nextToken(); // skip ':'

        if (!_checkTokenType(Lexer::TokenType::Identifier)) {
            throw std::runtime_error("Invalid type name!");
        }

        auto typeName = _currentToken().getValue();

        AST::GSTypePtr variableType;

        if (typeName == "I32") {
            variableType = std::make_shared<AST::GS_I32Type>();
        } else if (typeName == "String") {
            variableType = std::make_shared<AST::GS_StringType>();
        } else {
            throw std::runtime_error("Unknown type name!");
        }

        _nextToken(); // skip variable type

        return std::make_shared<AST::GS_VariableDeclarationStatement>(variableName, variableType);
    }

    AST::GSStatementPtr GS_Parser::_parseAssignmentStatement() {
        auto statement = _parseVariableDeclarationStatement();

        if (statement) {
            goto assignment;
        }


        statement =

        if (statement) {

        }

        assignment:
        if (_checkTokenType(Lexer::TokenType::SymbolEq)) {
            _nextToken(); // skip '='

            auto expression = _parseExpression();

            return std::make_shared<AST::GS_AssignmentStatement>(declarationOrUsing, expression);
        }

        return declarationOrUsing;
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

            switch (_currentToken().getType()) {
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

            _nextToken(); // skip binary operator

            auto secondExpression = _parseUnaryExpression();

            auto nextTokenPrecedence = _currentTokenPrecedence();

            if (currentTokenPrecedence < nextTokenPrecedence) {
                secondExpression = _parseBinaryExpression(currentTokenPrecedence + 1, secondExpression);
            }

            expression = std::make_shared<AST::GS_BinaryExpression>(binaryOperator, expression, secondExpression);
        }
    }

    AST::GSExpressionPtr GS_Parser::_parseUnaryExpression() {
        if (_checkTokenType(Lexer::TokenType::SymbolMinus)) {
            _nextToken();

            return std::make_shared<AST::GS_UnaryExpression>(AST::UnaryOperation::Minus, _parsePrimaryExpression());
        }

        return _parsePrimaryExpression();
    }

    AST::GSExpressionPtr GS_Parser::_parsePrimaryExpression() {
        if (_checkTokenType(Lexer::TokenType::LiteralNumber)) {
            auto value = _currentToken().getValue();

            _nextToken();

            return std::make_shared<AST::GS_ConstantExpression>(std::make_shared<AST::GS_I32Value>(std::stoi(value)));
        } else if (_checkTokenType(Lexer::TokenType::Identifier)) {
            auto value = _currentToken().getValue();

            _nextToken();

            return std::make_shared<AST::GS_VariableUsingExpression>(value);
        } else if (_checkTokenType(Lexer::TokenType::SymbolLeftParen)) {
            _nextToken();

            auto expression = _parseExpression();

            if (!_checkTokenType(Lexer::TokenType::SymbolRightParen)) {
                throw std::runtime_error("Missed \')\'!");
            }

            _nextToken();

            return expression;
        } else {
            throw std::runtime_error("Unknown expression!");
        }
    }

    I32 GS_Parser::_currentTokenPrecedence() {
        auto precedence = _operatorsPrecedence[_currentToken().getType()];

        if (!precedence) {
            return -1;
        }

        return precedence;
    }

    Bool GS_Parser::_checkTokenType(Lexer::TokenType typeForCheck, I32 numberOfToken) {
        return _tokenIterator[numberOfToken].getType() == typeForCheck;
    }

    Lexer::GS_Token GS_Parser::_currentToken() {
        return _tokenIterator[0];
    }

    Void GS_Parser::_nextToken() {
        ++_tokenIterator;
    }

}