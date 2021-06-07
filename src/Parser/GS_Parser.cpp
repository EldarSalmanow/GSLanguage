#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    GS_Parser::GS_Parser(GSTokenArray &tokens) {
        this->_tokens = tokens;

        _tokenIterator = this->_tokens.begin();
    }

    GSStatementPointerArray GS_Parser::parse() {
        while (!_checkTokenType(TokenType::END_OF_FILE)) {
            GSStatementPointer statement;

            try {
                statement = _statement();
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
            return _parsingVariableDeclaration();
        }
        else if (_checkTokenType(TokenType::SYMBOL_EQ)) {
            return _parsingAssignmentStatement();
        }
        //else if (_checkTokenType())
        else if (_checkTokenType(TokenType::NEW_LINE)) {
            throw Exceptions::GS_NewLineException();
        }
        else {
            _throwException("Unknown statement!");
        }
    }

//--------------------------------------------------------------------------------

    void GS_Parser::_throwException(std::string errorMessage) {
        throw Exceptions::GS_Exception((errorMessage +
        _currentToken().getPosition().getCode() +
        std::to_string(_currentToken().getPosition().getEndPosition().getLine()) +
        std::to_string(_currentToken().getPosition().getEndPosition().getColumn())).c_str());
    }

    bool GS_Parser::_checkTokenType(TokenType typeForCheck, int numberOfToken) {
        return _tokenIterator[numberOfToken].getType() == typeForCheck;
    }

    inline void GS_Parser::_addStatement(GSStatementPointer &statement) {
        _statements.emplace_back(statement);
    }

    GS_Token GS_Parser::_currentToken() {
        return _tokenIterator[0];
    }

    void GS_Parser::_nextToken() {
        ++_tokenIterator;
    }

}