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

            this->expressions.emplace_back(statement);

            ++this->tokenIterator;
        }
        return this->expressions;
    }

    GSStatementPointer GS_Parser::statement() {
        GS_Token currentToken = this->tokenIterator[0];
        GS_Statement *statement = nullptr;

        if (currentToken.getType() == TokenType::NEW_LINE) {
            ++this->line;

            return nullptr;
        } else if (currentToken.getType() == TokenType::END_OF_FILE) {
            this->isEndOfFile = true;

            return nullptr;
        } else if (currentToken.getType() == TokenType::KEYWORD_VAR) {
            ++this->tokenIterator;

            statement = (GS_Statement*) this->parsingVariable();
        }

        if (statement == nullptr) {
            throw Exceptions::GS_ParserException("Unknown statement!");
        }

        return GSStatementPointer(statement);
    }

    Statements::GS_VariableStatement *GS_Parser::parsingVariable() {
        Statements::GS_VariableStatement *statement;

        if (this->tokenIterator[0].getType() != TokenType::WORD) {
            throw Exceptions::GS_ParserException("Invalid variable declaration!", this->line);
        }

        if (this->tokenIterator[1].getType() == TokenType::SYMBOL_COLON) {
            Literal literalType = this->convertTokenTypeToReservedLiteral(this->tokenIterator[2].getType());

            statement = new Statements::GS_VariableStatement(
                    this->tokenIterator[0].getValue(),
                    Values::GS_IntegerValue(
                            std::stoi(this->tokenIterator[4].getValue())
                            ),
                            literalType
                    );

            ++this->tokenIterator;
            ++this->tokenIterator;
            ++this->tokenIterator;
            ++this->tokenIterator;

            return statement;
        }

        statement = new Statements::GS_VariableStatement(
                this->tokenIterator[0].getValue(),
                Values::GS_IntegerValue(
                        std::stoi(this->tokenIterator[2].getValue())
                        )
                );

        ++this->tokenIterator;
        ++this->tokenIterator;


        return statement;
    }

    Literal GS_Parser::convertTokenTypeToReservedLiteral(TokenType type) {
        switch (type) {
            case TokenType::KEYWORD_INT:
                return Literal::LITERAL_INT;
            case TokenType::KEYWORD_STRING:
                return Literal::LITERAL_STRING;
            default:
                throw Exceptions::GS_ParserException("Invalid reserved type!", this->line);
        }

    }

}