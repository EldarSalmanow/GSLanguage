#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <vector>
#include <iostream>
#include <memory>

#include "../Lexer/GS_Token.h"
#include "GS_Expression.h"

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
        std::vector<std::shared_ptr<GS_Expression>> parse();

    private:

        void analyzeToken();

        GS_Expression *higherOrder();

        GS_Expression *middleOrder();

        GS_Expression *lowerOrder();

    private:

        /**
         * Input tokens, before lexing analyzing
         */
        std::vector<GS_Token> tokens;

        /**
         * Expressions, before parsing analyzing
         */
        std::vector<std::shared_ptr<GS_Expression>> expressions;

        /**
         * Iterator input container with tokens
         */
        std::vector<GS_Token>::iterator tokenIterator;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
