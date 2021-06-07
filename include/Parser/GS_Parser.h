#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <vector>
#include <iostream>
#include <memory>

#include <Lexer/GS_Token.h>
#include <Parser/GS_IncludeExpressions.h>
#include <Parser/GS_IncludeStatements.h>
#include <Parser/GS_IncludeValues.h>

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
        GS_Parser(GSTokenArray &tokens);

    public:

        /**
         * Function for parsing _input tokens
         */
        GSStatementPointerArray parse();

    private:

        /**
         *
         * @return
         */
        GSStatementPointer _statement();

        /**
         *
         * @return
         */
        GSStatementPointer _parsingVariableDeclaration();

        /**
         *
         * @return
         */
         GS_VariableDeclarationStatement *_parsingVariableWithoutType();

        /**
         *
         * @return
         */
         GS_VariableDeclarationStatement *_parsingVariableWithType();

        /**
         *
         * @param statement
         * @return
         */
         GSStatementPointer _parsingAssignmentStatement();

    private:

        /**
         *
         * @return
         */
        GSExpressionPointer _expression();

        /**
         *
         * @return
         */
        GSExpressionPointer _additive();

        /**
         *
         * @return
         */
        GSExpressionPointer _multiplicative();

        /**
         *
         * @return
         */
        GSExpressionPointer _unary();

        /**
         *
         * @return
         */
        GSExpressionPointer _primary();

        /**
         *
         * @param typeForCheck
         * @param numberOfToken
         * @return
         */
        bool _checkTokenType(TokenType typeForCheck, int numberOfToken = 0);

        /**
         *
         * @param errorMessage
         */
        void _throwException(std::string errorMessage);

        /**
         *
         * @param statement
         */
        inline void _addStatement(GSStatementPointer &statement);

        /**
         *
         */
        void _nextToken();

        /**
         *
         * @return
         */
        GS_Token _currentToken();

    private:

        /**
         * Input tokens, before lexing analyzing
         */
        GSTokenArray _tokens;

        /**
         *
         */
        GSStatementPointerArray _statements;

        /**
         * Iterator _input container with tokens
         */
        GSTokenArray::iterator _tokenIterator;
    };

    typedef std::shared_ptr<GS_Parser> GSParserPointer;

}

#endif //GSLANGUAGE_GS_PARSER_H
