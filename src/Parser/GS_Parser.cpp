#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    GS_Parser::GS_Parser(Lexer::GSTokenArray &tokens)
            : _tokens(tokens), _tokenIterator(_tokens.begin()) {}

    GSNodePtrArray GS_Parser::parse() {
        while (!_checkTokenType(Lexer::TokenType::END_OF_FILE)) {
            GSNodePtr node;

            try {
                node = _node();
            } catch (Exceptions::GS_NewLineException) {
                _nextToken();

                continue;
            }

            _addNode(node);
        }

        return _statements;
    }

//--------------------------------------------------------------------------

    GSNodePtr GS_Parser::_node() {
        // var
        if (_checkTokenType(Lexer::TokenType::KEYWORD_VAR)) {
            throw Exceptions::GS_Exception("Unsupported parsing for variables declaration in this version!");
        }
        // new line
        else if (_checkTokenType(Lexer::TokenType::NEW_LINE)) {
            throw Exceptions::GS_NewLineException();
        }
        else {
            return _expression();
        }
    }

//--------------------------------------------------------------------------------

    GSVoid GS_Parser::_throwException(GSString errorMessage) {
        Lexer::GS_Position position = _currentToken().getPosition();

        throw Exceptions::GS_Exception(
                errorMessage
                + "\nCode: "
                + position.getCode()
                + "\nLine: "
                + std::to_string(position.getEndPosition().getLine())
                + "\nColumn: "
                + std::to_string(position.getEndPosition().getColumn()));
    }

    GSBool GS_Parser::_checkTokenType(Lexer::TokenType typeForCheck, GSInt numberOfToken) {
        return _tokenIterator[numberOfToken].getType() == typeForCheck;
    }

    inline GSVoid GS_Parser::_addNode(GSNodePtr &statement) {
        _statements.emplace_back(statement);
    }

    Lexer::GS_Token GS_Parser::_currentToken() {
        return _tokenIterator[0];
    }

    GSVoid GS_Parser::_nextToken() {
        ++_tokenIterator;
    }

}