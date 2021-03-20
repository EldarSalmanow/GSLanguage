#include "../../../include/Compiler/Parser/GS_Parser.h"

namespace GSLanguageCompiler {

    GSStatementPointerArray GS_Parser::parse() {
        this->tokenIterator = this->tokens.begin();
        this->line = 1;

        while (this->tokenIterator != tokens.end()) {
            GSStatementPointer statement = this->statement();

            // end of file
            if (this->isEndOfFile) {
                break;
            }
            // new line
            else if (statement == nullptr) {
                ++this->tokenIterator;

                continue;
            }

            this->statements.emplace_back(statement);
        }

        return this->statements;
    }

//--------------------------------------------------------------------------

    GSStatementPointer GS_Parser::statement() {
        if (this->checkTokenType(TokenType::NEW_LINE)) {
            ++this->line;

            return nullptr;
        } else if (this->checkTokenType(TokenType::END_OF_FILE)) {
            this->isEndOfFile = true;

            return nullptr;
        }

        // var
        if (this->checkTokenType(TokenType::KEYWORD_VAR)) {
            ++this->tokenIterator;

            return GSStatementPointer(this->parsingVariable());
        }
        else {
            throw Exceptions::GS_ParserException("Unknown statement!", this->input[this->line - 1], this->line);
        }
    }

//--------------------------------------------------------------------------------

    GSExpressionPointer GS_Parser::expression() {
        return this->additive();
    }

    GSExpressionPointer GS_Parser::additive() {
        GSExpressionPointer expression = multiplicative();

        while (true) {
            if (this->checkTokenType(TokenType::SYMBOL_PLUS)) {
                ++this->tokenIterator;

                expression = GSExpressionPointer(
                        new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::PLUS,
                                expression,
                                this->multiplicative()
                        )
                );

                continue;
            } else if (this->checkTokenType(TokenType::SYMBOL_MINUS)) {
                ++this->tokenIterator;

                expression = GSExpressionPointer(
                        new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::MINUS,
                                expression,
                                this->multiplicative()
                        )
                );

                continue;
            }

            break;
        }

        return expression;
    }

    GSExpressionPointer GS_Parser::multiplicative() {
        GSExpressionPointer expression = unary();

        while (true) {
            if (this->checkTokenType(TokenType::SYMBOL_STAR)) {
                ++this->tokenIterator;

                expression = GSExpressionPointer(
                        new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::STAR,
                                expression,
                                this->unary()
                        ));

                continue;
            } else if (this->checkTokenType(TokenType::SYMBOL_SLASH)) {
                ++this->tokenIterator;

                expression = GSExpressionPointer(
                        new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::SLASH,
                                expression,
                                this->unary()
                        ));

                continue;
            }

            break;
        }

        return expression;
    }

    GSExpressionPointer GS_Parser::unary() {
        if (this->checkTokenType(TokenType::SYMBOL_MINUS)) {
            ++this->tokenIterator;

            return GSExpressionPointer(new Expressions::GS_UnaryExpression(
                    Expressions::UnaryOperation::MINUS,
                    this->primary())
            );
        } else if (this->checkTokenType(TokenType::SYMBOL_PLUS)) {
            ++this->tokenIterator;

            return this->primary();
        }

        return primary();
    }

    GSExpressionPointer GS_Parser::primary() {
        GSExpressionPointer expression = nullptr;

        if (this->checkTokenType(TokenType::NEW_LINE)) {
            ++this->line;

            return nullptr;
        } else if (this->checkTokenType(TokenType::END_OF_FILE)) {
            this->isEndOfFile = true;

            return nullptr;
        } else if (this->checkTokenType(TokenType::LITERAL_NUMBER)) {
            expression = GSExpressionPointer(new Expressions::GS_NumberExpression(
                    std::stoi(this->tokenIterator[0].getValue())));

            ++this->tokenIterator;
        }
        else if (this->checkTokenType(TokenType::LITERAL_STRING)) {
            expression = GSExpressionPointer(new Expressions::GS_StringExpression(this->tokenIterator[0].getValue()));

            ++this->tokenIterator;
        } else if (this->checkTokenType(TokenType::SYMBOL_LEFT_PARENTHESES)) {
            ++this->tokenIterator;

            expression = this->expression();

            if (!this->checkTokenType(TokenType::SYMBOL_RIGHT_PARENTHESES)) {
                throw Exceptions::GS_ParserException("Lost right parentheses!", this->input[this->line - 1], this->line);
            }

            ++this->tokenIterator;
        } else if (this->checkTokenType(TokenType::SYMBOL_RIGHT_PARENTHESES)) {
            throw Exceptions::GS_ParserException("Lost left parentheses!", this->input[this->line - 1], this->line);
        }

        if (expression == nullptr) {
            throw Exceptions::GS_ParserException("Unknown expression!", this->input[this->line - 1], this->line);
        }

        return expression;
    }

//---------------------------------------------------------------------

    inline bool GS_Parser::checkTokenType(TokenType typeForCheck, int numberOfToken) {
        return this->tokenIterator[numberOfToken].getType() == typeForCheck;
    }

}