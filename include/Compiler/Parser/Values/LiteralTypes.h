#ifndef GSLANGUAGE_LITERALTYPES_H
#define GSLANGUAGE_LITERALTYPES_H

#include <vector>
#include <string>

namespace GSLanguageCompiler {

    enum class Literal {
        LITERAL_NULL,  // invalid type

        LITERAL_INT,   // 14
        LITERAL_STRING // "testing"
    };

    extern std::vector<Literal> types;

    extern std::string literalToString(Literal literal);

}

#endif //GSLANGUAGE_LITERALTYPES_H
