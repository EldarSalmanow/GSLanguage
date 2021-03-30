#include "../../../include/Compiler/Parser/GS_Parser.h"

#include "../../../include/Compiler/Parser/GS_TableOfSymbols.h"

namespace GSLanguageCompiler {

    Statements::GS_VariableStatement *GS_Parser::_parsingVariable() {
        // skip 'var'
        _nextToken();

        // var <name> = <value>
        if (_checkTokenType(TokenType::SYMBOL_EQ, 1)) {
            return _parsingVariableWithoutType();
        }
        // var <name>: <type> = <value>
        else if (_checkTokenType(TokenType::SYMBOL_COLON, 1)
                 && _checkTokenType(TokenType::SYMBOL_EQ, 3)) {
            return _parsingVariableWithType();
        }
        // if none of the available types of declaration
        else {
            throwException("Invalid variable declaration! \nValid variable declaration: var <name> = <value>");
            // TODO add GS_Documentation for valid code
        }
    }

    Statements::GS_VariableStatement *GS_Parser::_parsingVariableWithoutType() {
        std::string variableName = _currentToken().getValue();

        // skip variable name and '='
        _tokenIterator += 2;

        GSValuePointer variableValue = _expression()->result();

        switch (variableValue->getLiteralType()) {
            case Literal::LITERAL_INT:
                variableValue = GSValuePointer(new Values::GS_IntegerValue(variableValue->getInt()));
                break;
            case Literal::LITERAL_STRING:
                variableValue = GSValuePointer(new Values::GS_StringValue(variableValue->getString()));
                break;
            case Literal::LITERAL_NULL:
                throwException("Unknown type for variable declaration!");
        }

        GS_TableOfSymbols::add(variableName, variableValue);

        return new Statements::GS_VariableStatement(variableName, variableValue);
    }

    Statements::GS_VariableStatement *GS_Parser::_parsingVariableWithType() {
        std::string variableName = _currentToken().getValue();

        // skip variable name and :
        _tokenIterator += 2;

        Literal variableType = convertTokenTypeToLiteral(_currentToken().getType());

        _tokenIterator += 2;

        GSValuePointer variableValue = _expression()->result();

        if (variableValue->getLiteralType() != variableType) {
            variableValue = variableValue->castTo(variableType);
        }

        GS_TableOfSymbols::add(variableName, variableValue);

        return new Statements::GS_VariableStatement(variableName, variableValue);
    }

}