#ifndef GSLANGUAGE_GS_INTEGERVALUE_H
#define GSLANGUAGE_GS_INTEGERVALUE_H

#include <Compiler/Parser/Values/GS_Value.h>

namespace GSLanguageCompiler::Parser {

    /**
     *
     */
    class GS_IntegerValue : public GS_Value {
    public:

        /**
         *
         */
        GS_IntegerValue();

        /**
         *
         * @param value
         */
        GS_IntegerValue(int value);

    public:

        /**
         *
         * @param type
         * @return
         */
        GSValuePointer castTo(Literal type) override;
    };

}

#endif //GSLANGUAGE_GS_INTEGERVALUE_H
