#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    GSStatementPointer GS_Parser::_parsingVariableDeclaration() {
        // skip 'var'
        _nextToken();

        if (_checkTokenType(TokenType::WORD)) {
            GSStatementPointer statement;
            if (_checkTokenType(TokenType::SYMBOL_COLON, 1)) {
                statement = GSStatementPointer(_parsingVariableWithType());
            } else {
                statement = GSStatementPointer(_parsingVariableWithoutType());
            }

            return statement;
        } else {
            _throwException(
                    "Invalid variable declaration! "
                    "\nValid variable declaration: var <name> or var <name>: <type>");
        }
    }

    GS_VariableDeclarationStatement *GS_Parser::_parsingVariableWithoutType() {
        std::string variableName = _currentToken().getValue(); // TODO add checking for valid variable name

        // skip variable name
        _nextToken();

        return new GS_VariableDeclarationStatement(variableName);
    }

    GS_VariableDeclarationStatement *GS_Parser::_parsingVariableWithType() {
        std::string variableName = _currentToken().getValue(); // TODO add checking for valid variable name

        // skip variable name
        _nextToken();

        // skip ':'
        _nextToken();

        std::string variableType = convertTokenTypeToStringType(_currentToken().getType());

        // skip variable type
        _nextToken();

        return new GS_VariableDeclarationStatement(variableName, variableType);
    }

    GSStatementPointer GS_Parser::_parsingAssignmentStatement() {
        // skip '='
        _nextToken();

        GSStatementPointer statement = _statements.back();

        _statements.pop_back();

        return GSStatementPointer(
                new GS_AssignmentStatement(
                        *static_cast<GS_VariableDeclarationStatement*>(statement.get()), _expression()));
    }

}