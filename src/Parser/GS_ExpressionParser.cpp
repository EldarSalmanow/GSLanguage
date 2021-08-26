#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    GSNodePtr GS_Parser::_expression() {
        return _additive();
    }

    GSNodePtr GS_Parser::_additive() {
        GSNodePtr expression = _multiplicative();

        while (true) {
            if (_checkTokenType(Lexer::TokenType::SYMBOL_PLUS)) {
                _nextToken();

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::PLUS, expression, _multiplicative());

                continue;
            } else if (_checkTokenType(Lexer::TokenType::SYMBOL_MINUS)) {
                _nextToken();

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::MINUS, expression, _multiplicative());

                continue;
            }

            break;
        }

        return expression;
    }

    GSNodePtr GS_Parser::_multiplicative() {
        GSNodePtr expression = _unary();

//        if (!expression) {
//            _throwException("Error with parsing multiplicative expression!");
//        }

        while (true) {
            if (_checkTokenType(Lexer::TokenType::SYMBOL_STAR)) {
                _nextToken();

                auto node = _unary();

//                if (!node) {
//                    _throwException("Error with parsing multiplicative expression!");
//                }

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::STAR, expression, node);

                continue;
            } else if (_checkTokenType(Lexer::TokenType::SYMBOL_SLASH)) {
                _nextToken();

                auto node = _unary();

//                if (!node) {
//                    _throwException("Error with parsing multiplicative expression!");
//                }

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::SLASH, expression, node);

                continue;
            }

            break;
        }

        return expression;
    }

    GSNodePtr GS_Parser::_unary() {
        if (_checkTokenType(Lexer::TokenType::SYMBOL_MINUS)) {
            _nextToken();

            auto node = _primary();

//            if (!node) {
//                _throwException("Error with parsing unary expression!");
//            }

            return std::make_shared<GS_UnaryNode>(UnaryOperation::MINUS, node);
        }

        return _primary();
    }

    GSNodePtr GS_Parser::_primary() {
        GSNodePtr expression = nullptr;

        if (_checkTokenType(Lexer::TokenType::NEW_LINE)) {
            _nextToken();

            return _primary();
        }

        if (_checkTokenType(Lexer::TokenType::LITERAL_NUMBER)) {
            expression = std::make_shared<GS_ValueNode>(std::make_shared<GS_IntegerValue>(std::stoi(_currentToken().getValue())));

            _nextToken();
        } else if (_checkTokenType(Lexer::TokenType::LITERAL_STRING)) {
            expression = std::make_shared<GS_ValueNode>(std::make_shared<GS_StringValue>(_currentToken().getValue()));

            _nextToken();
        } else if (_checkTokenType(Lexer::TokenType::SYMBOL_LEFT_PARENTHESES)) {
            _nextToken();

            expression = _expression();

            if (!_checkTokenType(Lexer::TokenType::SYMBOL_RIGHT_PARENTHESES)) {
                _throwException("Lost right parentheses!");
            }

            _nextToken();
        } else if (_checkTokenType(Lexer::TokenType::SYMBOL_RIGHT_PARENTHESES)) {
            _throwException("Lost left parentheses!");
        } else {
            _throwException("Unknown expression!");
        }

        return expression;
    }

}