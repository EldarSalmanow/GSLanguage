#include "../../../include/Compiler/Parser/GS_Parser.h"

namespace GSLanguageCompiler {

    GSExpressionPointer GS_Parser::_expression() {
        return _additive();
    }

    GSExpressionPointer GS_Parser::_additive() {
        GSExpressionPointer expression = _multiplicative();

        while (true) {
            if (_checkTokenType(TokenType::SYMBOL_PLUS)) {
                _nextToken();

                expression = GSExpressionPointer(new Expressions::GS_BinaryExpression(
                        Expressions::BinaryOperation::PLUS,
                        expression,
                        _multiplicative()));

                continue;
            } else if (_checkTokenType(TokenType::SYMBOL_MINUS)) {
                _nextToken();

                expression = GSExpressionPointer(new Expressions::GS_BinaryExpression(
                        Expressions::BinaryOperation::MINUS,
                        expression,
                        _multiplicative()));

                continue;
            }

            break;
        }

        return expression;
    }

    GSExpressionPointer GS_Parser::_multiplicative() {
        GSExpressionPointer expression = _unary();

        while (true) {
            if (_checkTokenType(TokenType::SYMBOL_STAR)) {
                _nextToken();

                expression = GSExpressionPointer(new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::STAR,
                                expression,
                                _unary()));

                continue;
            } else if (_checkTokenType(TokenType::SYMBOL_SLASH)) {
                _nextToken();

                expression = GSExpressionPointer(new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::SLASH,
                                expression,
                                _unary()));

                continue;
            }

            break;
        }

        return expression;
    }

    GSExpressionPointer GS_Parser::_unary() {
        if (this->_checkTokenType(TokenType::SYMBOL_MINUS)) {
            _nextToken();

            return GSExpressionPointer(new Expressions::GS_UnaryExpression(
                    Expressions::UnaryOperation::MINUS,
                    _primary()));
        }

        return _primary();
    }

    GSExpressionPointer GS_Parser::_primary() {
        GSExpressionPointer expression = nullptr;

        if (_checkTokenType(TokenType::NEW_LINE)) {
            throw Exceptions::GS_NewLineException();
        }

        if (_checkTokenType(TokenType::LITERAL_NUMBER)) {
            expression = GSExpressionPointer(new Expressions::GS_NumberExpression(
                    std::stoi(_currentToken().getValue())));

            _nextToken();
        } else if (_checkTokenType(TokenType::LITERAL_STRING)) {
            expression = GSExpressionPointer(new Expressions::GS_StringExpression(_currentToken().getValue()));

            _nextToken();
        } else if (_checkTokenType(TokenType::SYMBOL_LEFT_PARENTHESES)) {
            _nextToken();

            expression = this->_expression();

            if (!_checkTokenType(TokenType::SYMBOL_RIGHT_PARENTHESES)) {
                throwException("Lost right parentheses!");
            }

            _nextToken();
        }
        else if (_checkTokenType(TokenType::SYMBOL_RIGHT_PARENTHESES)) {
            throwException("Lost left parentheses!");
        }

        if (expression == nullptr) {
            throwException("Unknown expression!");
        }

        return expression;
    }

}