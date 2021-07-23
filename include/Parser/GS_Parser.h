#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <Lexer/GS_Token.h>

#include <Parser/GS_IncludeNodes.h>

#include <Exceptions/GS_Exception.h>
#include <Exceptions/GS_NewLineException.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Class for generating AST and parsing AST
     */
    class GS_Parser {
    public:

        /**
         * Constructor for GS_Parser
         * @param tokens Container with tokens, before lexing analyzing
         */
        GS_Parser(Lexer::GSTokenArray &tokens);

    public:

        /**
         * Function for parsing input tokens
         */
        GSNodePtrArray parse();

    private:

        /**
         *
         * @return
         */
        GSNodePtr _node();

    private:

        /**
         *
         * @return
         */
        GSNodePtr _expression();

        /**
         *
         * @return
         */
        GSNodePtr _additive();

        /**
         *
         * @return
         */
        GSNodePtr _multiplicative();

        /**
         *
         * @return
         */
        GSNodePtr _unary();

        /**
         *
         * @return
         */
        GSNodePtr _primary();

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
         * @param statement
         */
        inline GSVoid _addNode(GSNodePtr &statement);

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
         *
         */
        GSNodePtrArray _statements;

        /**
         * Iterator _input container with tokens
         */
        Lexer::GSTokenArray::iterator _tokenIterator;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
