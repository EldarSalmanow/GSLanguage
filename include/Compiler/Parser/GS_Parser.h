#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <vector>
#include <iostream>
#include <memory>

#include "../Lexer/GS_Token.h"
#include "GS_IncludeExpressions.h"
#include "GS_IncludeStatements.h"
#include "GS_IncludeValues.h"

#include "../../../include/Exceptions/GS_ParserException.h"
#include "../../../include/Exceptions/GS_NewLineException.h"

namespace GSLanguageCompiler {

    typedef std::vector<std::string> GSText;

    /**
     * Class for generating AST and parsing AST
     */
    class GS_Parser {
    public:

        /**
         * Constructor for GS_Parser
         * @param tokens Container with tokens, before lexing analyzing
         */
        GS_Parser(GSTokenArray &tokens, GSText &input) {
            this->_tokens = tokens;
            this->_input = input;
        }

    public:

        /**
         * Function for parsing input tokens
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
        Statements::GS_VariableStatement *_parsingVariable();

        /**
         *
         * @return
         */
        Statements::GS_VariableStatement *_parsingVariableWithoutType();

        /**
         *
         * @return
         */
        Statements::GS_VariableStatement *_parsingVariableWithType();

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
        void throwException(std::string errorMessage);

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

        GSText _input;

        /**
         * Input tokens, before lexing analyzing
         */
        GSTokenArray _tokens;

        /**
         *
         */
        GSStatementPointerArray _statements;

        /**
         * Iterator input container with tokens
         */
        GSTokenArray::iterator _tokenIterator;
    };

    typedef std::shared_ptr<GS_Parser> GSParserPointer;

}

#endif //GSLANGUAGE_GS_PARSER_H
