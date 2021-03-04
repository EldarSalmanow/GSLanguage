#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <vector>
#include <iostream>
#include <memory>

#include "../Lexer/GS_Token.h"
#include "Expressions/GS_Expression.h"
#include "GS_IncludeStatements.h"

#include "../../../include/Exceptions/GS_ParserException.h"

namespace GSLanguageCompiler {

    /**
     * Class for generating AST and parsing AST
     */
    class GS_Parser {
    public:

        /**
         * Constructor for GS_Parser
         * @param tokens Container with tokens, before lexing analyzing
         */
        GS_Parser(std::vector<GS_Token> &tokens) {
            this->tokens = tokens;
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

    private:

        /**
         * Input tokens, before lexing analyzing
         */
        GSTokenArray tokens;

        /**
         * Expressions, before parsing analyzing
         */
        GSStatementPointerArray expressions;

        /**
         *
         */
        int line, column;

        /**
         *
         */
        bool isEndOfFile = false;

        /**
         * Iterator input container with tokens
         */
        std::vector<GS_Token>::iterator tokenIterator;

        Literal convertTokenTypeToReservedLiteral(TokenType type);
    };

    typedef std::shared_ptr<GS_Parser> GSParserPointer;

}

#endif //GSLANGUAGE_GS_PARSER_H
