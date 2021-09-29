#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <functional>

#include <Starter/GS_Runnable.h>

#include <Lexer/GS_Token.h>

#include <Parser/GS_IncludeNodes.h>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Class for generating AST and parsing AST
     */
    class GS_Parser : public Starter::GS_Runnable {
    public:

        GS_Parser();

    public:

        GSVoid run(Starter::GSContextPtr &context) override;

    private:

        GSNodePtr _parseRoot();

        GSNodePtr _parseBlock();

        GSNodePtr _parseNode();

        GSNodePtr _parseAssignmentNode();

        GSNodePtr _parseVariableDeclarationNode();

        GSNodePtr _parseVariableUsingNode();

        GSNodePtr _parseExpression();

        GSNodePtr _parseBinaryExpression();

        GSNodePtr _parseAdditiveExpression();

        GSNodePtr _parseMultiplicativeExpression();

        GSNodePtr _parseUnaryExpression();

        GSNodePtr _parseLiteralExpression();

    private:

        /**
         *
         * @param typeForCheck
         * @param numberOfToken
         * @return
         */
        GSBool _checkTokenType(Lexer::TokenType typeForCheck, GSInt numberOfToken = 0);

        /**
         *
         * @param errorMessage
         */
        GSVoid _throwException(GSString errorMessage);

        /**
         *
         */
        GSVoid _nextToken();

        /**
         *
         * @return
         */
        Lexer::GS_Token _currentToken();

    private:

        /**
         * Input tokens, before lexing analyzing
         */
        Lexer::GSTokenArray _tokens;

        /**
         * Iterator _input container with tokens
         */
        Lexer::GSTokenArray::iterator _tokenIterator;

        /**
         * AST nodes
         */
        GSNodePtrArray _nodes;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
