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
            _nextToken(); // skip 'var'

            auto name = _currentToken().getValue();

            _nextToken(); // skip name

            if (_checkTokenType(Lexer::TokenType::SYMBOL_COLON)) {
                _nextToken(); // skip ':'

                auto type = _currentToken().getValue();

                _nextToken(); // skip type

                if (_checkTokenType(Lexer::TokenType::SYMBOL_EQ)) {
                    _nextToken(); // skip '='

                    auto node = _expression();

                    return std::make_shared<GS_VariableNode>(name, type, node);
                } else {
                    return std::make_shared<GS_VariableNode>(name, type);
                }
            } else if (_checkTokenType(Lexer::TokenType::SYMBOL_EQ)) {
                _nextToken(); // skip '='

                auto node = _expression();

                return std::make_shared<GS_VariableNode>(name, node);
            } else {
                return std::make_shared<GS_VariableNode>(name);
            }
        }
        else if (_checkTokenType(Lexer::TokenType::KEYWORD_PRINT)) {
            _nextToken(); // skip 'print'

            _nextToken(); // skip '('

            auto node = _primary(); // string value

            auto valueNode = *dynamic_cast<GS_ValueNode*>(node.get());

            auto value = valueNode.getValue();

            _nextToken(); // skip ')'

            _nextToken();

            return std::make_shared<GS_PrintNode>(value);
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
                std::move(errorMessage)
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