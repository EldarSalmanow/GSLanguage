#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Type of token
     */
    enum class TokenType {
#include <Lexer/GS_Keywords.def>
    };

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
