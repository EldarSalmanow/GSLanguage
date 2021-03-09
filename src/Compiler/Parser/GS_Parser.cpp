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
        if (this->checkCurrentTokenType(TokenType::NEW_LINE)) {
            ++this->line;

            return nullptr;
        } else if (this->checkCurrentTokenType(TokenType::END_OF_FILE)) {
            this->isEndOfFile = true;

            return nullptr;
        }

        // var
        if (this->checkCurrentTokenType(TokenType::KEYWORD_VAR)) {
            ++this->tokenIterator;

            return GSStatementPointer(this->parsingVariable());
        }
        else {
            throw Exceptions::GS_ParserException("Unknown statement!", this->line);
        }
    }

    Statements::GS_VariableStatement *GS_Parser::parsingVariable() {
        // var <name> = <value>
        if (this->checkCurrentTokenType(TokenType::SYMBOL_EQ, 1)) {
            return this->parsingVariableWithoutType();
        }
        // if none of the available types of declaration
        else {
            throw Exceptions::GS_ParserException("Invalid variable declaration!", this->line);
        }
    }

    Statements::GS_VariableStatement *GS_Parser::parsingVariableWithoutType() {
        std::string variableName = this->tokenIterator[0].getValue();
        // skip variable name and =
        ++this->tokenIterator;
        ++this->tokenIterator;

        GSValuePointer variableValue;

        GSValuePointer result = this->expression()->result();

        switch (result->getLiteralType()) {
            case Literal::LITERAL_INT:
                variableValue = GSValuePointer(new Values::GS_IntegerValue(result->getInt()));
                break;
            case Literal::LITERAL_STRING:
                variableValue = GSValuePointer(new Values::GS_StringValue(result->getString()));
                break;
            case Literal::LITERAL_NULL:
                throw Exceptions::GS_ParserException("Unknown type for variable declaration!", this->line);
        }

        return new Statements::GS_VariableStatement(variableName, variableValue);
    }

//--------------------------------------------------------------------------------

    GSExpressionPointer GS_Parser::expression() {
        return this->additive();
    }

    GSExpressionPointer GS_Parser::additive() {
        GSExpressionPointer expression = multiplicative();

        while (true) {
            if (this->checkCurrentTokenType(TokenType::SYMBOL_PLUS)) {
                ++this->tokenIterator;

                expression = GSExpressionPointer(
                        new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::PLUS,
                                expression,
                                this->multiplicative()
                        )
                );

                continue;
            } else if (this->checkCurrentTokenType(TokenType::SYMBOL_MINUS)) {
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
            if (this->checkCurrentTokenType(TokenType::SYMBOL_STAR)) {
                ++this->tokenIterator;

                expression = GSExpressionPointer(
                        new Expressions::GS_BinaryExpression(
                                Expressions::BinaryOperation::STAR,
                                expression,
                                this->unary()
                        ));

                continue;
            } else if (this->checkCurrentTokenType(TokenType::SYMBOL_SLASH)) {
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
        if (this->checkCurrentTokenType(TokenType::SYMBOL_MINUS)) {
            ++this->tokenIterator;

            return GSExpressionPointer(new Expressions::GS_UnaryExpression(
                    Expressions::UnaryOperation::MINUS,
                    this->primary())
            );
        } else if (this->checkCurrentTokenType(TokenType::SYMBOL_PLUS)) {
            ++this->tokenIterator;

            return this->primary();
        }

        return primary();
    }

    GSExpressionPointer GS_Parser::primary() {
        GSExpressionPointer expression = nullptr;

        if (this->checkCurrentTokenType(TokenType::NEW_LINE)) {
            ++this->line;

            return nullptr;
        } else if (this->checkCurrentTokenType(TokenType::END_OF_FILE)) {
            this->isEndOfFile = true;

            return nullptr;
        } else if (this->checkCurrentTokenType(TokenType::LITERAL_NUMBER)) {
            expression = GSExpressionPointer(new Expressions::GS_NumberExpression(
                    std::stoi(this->tokenIterator[0].getValue())));

            ++this->tokenIterator;
        }
        else if (this->checkCurrentTokenType(TokenType::LITERAL_STRING)) {
            expression = GSExpressionPointer(new Expressions::GS_StringExpression(this->tokenIterator[0].getValue()));

            ++this->tokenIterator;
        } else if (this->checkCurrentTokenType(TokenType::SYMBOL_LEFT_PARENTHESES)) {
            ++this->tokenIterator;

            expression = this->expression();

            if (!this->checkCurrentTokenType(TokenType::SYMBOL_RIGHT_PARENTHESES)) {
                throw Exceptions::GS_ParserException("Lost right parentheses!", this->line);
            }

            ++this->tokenIterator;
        } else if (this->checkCurrentTokenType(TokenType::SYMBOL_RIGHT_PARENTHESES)) {
            throw Exceptions::GS_ParserException("Lost left parentheses!", this->line);
        }

        if (expression == nullptr) {
            throw Exceptions::GS_ParserException("Unknown expression!", this->line);
        }

        return expression;
    }

//---------------------------------------------------------------------

    inline bool GS_Parser::checkCurrentTokenType(TokenType typeForCheck, int numberOfToken) {
        return this->tokenIterator[numberOfToken].getType() == typeForCheck;
    }
}