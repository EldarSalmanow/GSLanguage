#include <GS_Parser.h>

namespace GSLanguageCompiler::Parser {

    GS_Parser::GS_Parser() = default;

    GSVoid GS_Parser::run(Starter::GSContextPtr &context) {
        _tokens = context->getTokens();

        _tokenIterator = _tokens.begin();

        auto root = _parseRoot();

        context->setRootNode(root);
    }

    GSNodePtr GS_Parser::_parseRoot() {
        auto block = _parseBlock();

        return std::make_shared<GS_RootNode>(block);
    }

    GSNodePtr GS_Parser::_parseBlock() {
        GSNodePtrArray nodes;

        while (!_checkTokenType(Lexer::TokenType::END_OF_FILE)) {
            nodes.emplace_back(_parseNode());
        }

        return std::make_shared<GS_BlockNode>(nodes);
    }

    GSNodePtr GS_Parser::_parseNode() {
        return _parseAssignmentNode();
    }

    GSNodePtr GS_Parser::_parseAssignmentNode() {
        std::vector<std::function<GSNodePtr(GS_Parser*)>> parserFunctions = {
                std::function<GSNodePtr(GS_Parser*)>(&GS_Parser::_parseVariableDeclarationNode),
                std::function<GSNodePtr(GS_Parser*)>(&GS_Parser::_parseVariableUsingNode)
        };

        for (auto &function : parserFunctions) {
            auto node = function(this);

            if (node && !_checkTokenType(Lexer::TokenType::SYMBOL_EQ)) {
                return node;
            }

            if (_checkTokenType(Lexer::TokenType::SYMBOL_EQ)) {
                _nextToken(); // skip '='

                auto expression = _parseExpression();

                return std::make_shared<GS_AssignmentNode>(node, expression);
            } else {
                _throwException("Unknown node!");
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Parser::_parseVariableDeclarationNode() {
        if (_checkTokenType(Lexer::TokenType::KEYWORD_VAR)) {
            _nextToken(); // skip 'var'

            if (!_checkTokenType(Lexer::TokenType::WORD)) {
                _throwException("Variable name must be valid id!");

                return nullptr;
            }

            auto name = _currentToken().getValue();

            _nextToken(); // skip variable name

            return std::make_shared<GS_VariableDeclarationNode>(name);
        }

        return nullptr;
    }

    GSNodePtr GS_Parser::_parseVariableUsingNode() {
        return nullptr; // todo add code
    }

    GSNodePtr GS_Parser::_parseExpression() {
        return _parseBinaryExpression();
    }

    GSNodePtr GS_Parser::_parseBinaryExpression() {
        return _parseAdditiveExpression();
    }

    GSNodePtr GS_Parser::_parseAdditiveExpression() {
        auto expression = _parseMultiplicativeExpression();

        while (true) {
            if (_checkTokenType(Lexer::TokenType::SYMBOL_PLUS)) {
                _nextToken();

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::PLUS, expression, _parseMultiplicativeExpression());

                continue;
            } else if (_checkTokenType(Lexer::TokenType::SYMBOL_MINUS)) {
                _nextToken();

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::MINUS, expression, _parseMultiplicativeExpression());

                continue;
            }

            break;
        }

        return expression;
    }

    GSNodePtr GS_Parser::_parseMultiplicativeExpression() {
        auto expression = _parseUnaryExpression();

        while (true) {
            if (_checkTokenType(Lexer::TokenType::SYMBOL_STAR)) {
                _nextToken();

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::STAR, expression, _parseUnaryExpression());

                continue;
            } else if (_checkTokenType(Lexer::TokenType::SYMBOL_SLASH)) {
                _nextToken();

                expression = std::make_shared<GS_BinaryNode>(BinaryOperation::SLASH, expression, _parseUnaryExpression());

                continue;
            }

            break;
        }

        return expression;
    }

    GSNodePtr GS_Parser::_parseUnaryExpression() {
        if (_checkTokenType(Lexer::TokenType::SYMBOL_MINUS)) {
            _nextToken();

            auto node = _parseLiteralExpression();

            return std::make_shared<GS_UnaryNode>(UnaryOperation::MINUS, node);
        }

        return _parseLiteralExpression();
    }

    GSNodePtr GS_Parser::_parseLiteralExpression() {
        GSValuePtr value;

        if (_checkTokenType(Lexer::TokenType::LITERAL_NUMBER)) {
            value = std::make_shared<GS_IntegerValue>(std::stoi(_currentToken().getValue()));

            _nextToken();
        } else if (_checkTokenType(Lexer::TokenType::LITERAL_STRING)) {
            value = std::make_shared<GS_StringValue>(_currentToken().getValue());

            _nextToken();
        } else {
            _throwException("Invalid literal!");

            return nullptr;
        }

        return std::make_shared<GS_ValueNode>(value);
    }

    GSVoid GS_Parser::_throwException(GSString errorMessage) {
        Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                       _currentToken().getPosition(),
                                       std::move(errorMessage));

        Exceptions::errorHandler.throw_();
    }

    GSBool GS_Parser::_checkTokenType(Lexer::TokenType typeForCheck, GSInt numberOfToken) {
        return _tokenIterator[numberOfToken].getType() == typeForCheck;
    }

    Lexer::GS_Token GS_Parser::_currentToken() {
        return _tokenIterator[0];
    }

    GSVoid GS_Parser::_nextToken() {
        ++_tokenIterator;
    }

}