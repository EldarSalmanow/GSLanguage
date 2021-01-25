#ifndef GSLANGUAGE_GS_PARSER_H
#define GSLANGUAGE_GS_PARSER_H

#include <vector>
#include <iostream>

#include "../Lexer/GS_Token.h"
#include "../../../include/Exceptions/GS_ParserException.h"

namespace GSLanguageCompiler {

    /**
     * Class for generating AST and parsing AST
     */
    class GS_Parser {
    public:
        GS_Parser(std::vector<GS_Token> &tokens) {
            this->tokens = tokens;
        }

    public:

        /**
         * Function for parsing input tokens
         */
        void parse();

    private:

        /**
         * Input tokens, before lexing analyzing
         */
        std::vector<GS_Token> tokens;

        /**
         * Position of parser analyzing
         */
        int line, column;
    };

}

#endif //GSLANGUAGE_GS_PARSER_H
