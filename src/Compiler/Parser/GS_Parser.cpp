#include "../../../include/Compiler/Parser/GS_Parser.h"

namespace GSLanguageCompiler {

    GSStatementPointerArray GS_Parser::parse() {
        _tokenIterator = _tokens.begin();

        while (!_checkTokenType(TokenType::END_OF_FILE)) {
            GSStatementPointer statement;

            try {
                statement = this->_statement();
            } catch (Exceptions::GS_NewLineException) {
                _nextToken();

                continue;
            }

            _addStatement(statement);
        }

        return _statements;
    }

//--------------------------------------------------------------------------

    GSStatementPointer GS_Parser::_statement() {
        // var
        if (_checkTokenType(TokenType::KEYWORD_VAR)) {
            return GSStatementPointer(_parsingVariable());
        }
        else if (_checkTokenType(TokenType::NEW_LINE)) {
            throw Exceptions::GS_NewLineException();
        }
        else {
            throwException("Unknown statement!");
        }
    }

//--------------------------------------------------------------------------------

    void GS_Parser::throwException(std::string errorMessage) {
        throw Exceptions::GS_ParserException(errorMessage,
                                             _currentToken().getPosition().getCode(),
                                             _currentToken().getPosition().getEndPosition().getLine(),
                                             _currentToken().getPosition().getEndPosition().getColumn());
    }

    bool GS_Parser::_checkTokenType(TokenType typeForCheck, int numberOfToken) {
        return _tokenIterator[numberOfToken].getType() == typeForCheck;
    }

    inline void GS_Parser::_addStatement(GSStatementPointer &statement) {
        _statements.emplace_back(statement);
    }

    inline GS_Token GS_Parser::_currentToken() {
        return _tokenIterator[0];
    }

    void GS_Parser::_nextToken() {
        ++_tokenIterator;
    }

}