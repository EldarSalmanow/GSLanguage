#include "../../../include/Compiler/Parser/GS_Parser.h"

#include "../../../include/Compiler/Parser/GS_TableOfSymbols.h"

namespace GSLanguageCompiler {

    Statements::GS_VariableStatement *GS_Parser::parsingVariable() {
        // var <name> = <value>
        if (this->checkTokenType(TokenType::SYMBOL_EQ, 1)) {
            return this->parsingVariableWithoutType();
        }
        // var <name>: <type> = <value>
        else if (this->checkTokenType(TokenType::SYMBOL_COLON, 1)
        && this->checkTokenType(TokenType::SYMBOL_EQ, 3)) {
            return this->parsingVariableWithType();
        }
        // if none of the available types of declaration
        else {
            throw Exceptions::GS_ParserException("Invalid variable declaration! \nValid variable declaration: var <name> = <value>", this->input[this->line - 1], this->line); // TODO add GS_Documentation for valid code
        }
    }

    Statements::GS_VariableStatement *GS_Parser::parsingVariableWithoutType() {
        std::string variableName = this->tokenIterator[0].getValue();

        // skip variable name and =
        this->tokenIterator += 2;

        GSValuePointer variableValue = this->expression()->result();

        switch (variableValue->getLiteralType()) {
            case Literal::LITERAL_INT:
                variableValue = GSValuePointer(new Values::GS_IntegerValue(variableValue->getInt()));
                break;
            case Literal::LITERAL_STRING:
                variableValue = GSValuePointer(new Values::GS_StringValue(variableValue->getString()));
                break;
            case Literal::LITERAL_NULL:
                throw Exceptions::GS_ParserException("Unknown type for variable declaration!", this->input[this->line - 1], this->line);
        }

        GS_TableOfSymbols::add(variableName, variableValue);

        return new Statements::GS_VariableStatement(variableName, variableValue);
    }

    Statements::GS_VariableStatement *GS_Parser::parsingVariableWithType() {
        std::string variableName = this->tokenIterator[0].getValue();

        // skip variable name and :
        this->tokenIterator += 2;

        Literal variableType = convertTokenTypeToLiteral(this->tokenIterator[0].getType());

        this->tokenIterator += 2;

        GSValuePointer variableValue = this->expression()->result();

        if (variableValue->getLiteralType() != variableType) {
            variableValue = variableValue->castTo(variableType);
        }

        GS_TableOfSymbols::add(variableName, variableValue);

        return new Statements::GS_VariableStatement(variableName, variableValue);
    }

}