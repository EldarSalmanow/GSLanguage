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
            this->tokens = tokens;
            this->input = input;
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
        GSStatementPointer statement();

        /**
         *
         * @return
         */
        Statements::GS_VariableStatement *parsingVariable();

        /**
         *
         * @return
         */
        Statements::GS_VariableStatement *parsingVariableWithoutType();

    private:

        /**
         *
         * @return
         */
        GSExpressionPointer expression();

        /**
         *
         * @return
         */
        GSExpressionPointer additive();

        /**
         *
         * @return
         */
        GSExpressionPointer multiplicative();

        /**
         *
         * @return
         */
        GSExpressionPointer unary();

        /**
         *
         * @return
         */
        GSExpressionPointer primary();

        /**
         *
         * @param typeForCheck
         * @param numberOfToken
         * @return
         */
        inline bool checkCurrentTokenType(TokenType typeForCheck, int numberOfToken = 0);

    private:

        GSText input;

        /**
         * Input tokens, before lexing analyzing
         */
        GSTokenArray tokens;

        /**
         *
         */
        GSStatementPointerArray statements;

        /**
         *
         */
        int line;

        /**
         *
         */
        bool isEndOfFile = false;

        /**
         * Iterator input container with tokens
         */
        GSTokenArray::iterator tokenIterator;
    };

    typedef std::shared_ptr<GS_Parser> GSParserPointer;

}

#endif //GSLANGUAGE_GS_PARSER_H
