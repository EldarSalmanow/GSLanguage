#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

namespace GSLanguageCompiler::Lexer {

    /**
     * Type of token
     */
    enum class TokenType {
        #include <Lexer/GS_Keywords.def>
    };

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
