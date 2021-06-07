#ifndef GSLANGUAGE_LITERALTYPES_H
#define GSLANGUAGE_LITERALTYPES_H

#include <vector>
#include <string>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler {

    using namespace Lexer;

    /**
     *
     */
    enum class Literal {
        LITERAL_NULL,  // invalid type

        LITERAL_INT,   // 14
        LITERAL_STRING // "testing"
    };

    /**
     *
     */
    extern std::vector<Literal> types;

    /**
     *
     */
    extern Literal convertTokenTypeToLiteral(TokenType type);

    /**
     *
     * @param type
     * @return
     */
    extern std::string convertTokenTypeToStringType(TokenType type);

    /**
     *
     * @param literal
     * @return
     */
    extern std::string convertLiteralToString(Literal literal);

}

#endif //GSLANGUAGE_LITERALTYPES_H
