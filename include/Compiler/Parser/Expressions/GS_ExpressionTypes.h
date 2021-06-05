#ifndef GSLANGUAGE_GS_EXPRESSIONTYPES_H
#define GSLANGUAGE_GS_EXPRESSIONTYPES_H

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    enum class ExpressionType {
        VALUE,

        BINARY,
        UNARY
    };

}

#endif //GSLANGUAGE_GS_EXPRESSIONTYPES_H
