#ifndef GSLANGUAGE_GS_INTEGERVALUE_H
#define GSLANGUAGE_GS_INTEGERVALUE_H

#include <Parser/Nodes/GS_Value.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Integer value
     */
    class GS_IntegerValue : public GS_Value {
    public:

        /**
         *
         */
        GS_IntegerValue();

        /**
         * Constructor for integer value
         * @param value Integer value
         */
        GS_IntegerValue(GSInt value);
    };

}

#endif //GSLANGUAGE_GS_INTEGERVALUE_H
