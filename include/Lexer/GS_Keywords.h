#ifndef GSLANGUAGE_GS_KEYWORDS_H
#define GSLANGUAGE_GS_KEYWORDS_H

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::Lexer {

    /**
     * Type of token
     */
    enum class TokenType {
        EndOfFile,

        Identifier,             // main

        LiteralNumber,          // 12

        KeywordVar,             // var
        KeywordFunc,            // func

        SymbolLeftParen,        // (
        SymbolRightParen,       // )
        SymbolLeftBrace,        // {
        SymbolRightBrace,       // }

        SymbolDoubleQuotes,     // "
        SymbolColon,            // :
        SymbolComma,            // ,

        SymbolPlus,             // +
        SymbolMinus,            // -
        SymbolStar,             // *
        SymbolSlash,            // /
        SymbolEq                // =
    };

}

#endif //GSLANGUAGE_GS_KEYWORDS_H
