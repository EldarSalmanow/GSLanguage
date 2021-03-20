#ifndef GSLANGUAGE_GS_INTEGERVALUE_H
#define GSLANGUAGE_GS_INTEGERVALUE_H

#include "GS_Value.h"

namespace GSLanguageCompiler::Values {

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
         * @return
         */
        int getValue();

    public:

        /**
         *
         * @return
         */
        int getInt() override;

        /**
         *
         * @return
         */
        std::string getString() override;

        /**
         *
         * @param type
         * @return
         */
        GSValuePointer castTo(Literal type) override;

        /**
         *
         * @return
         */
        Literal getLiteralType() override;

    private:

        /**
         *
         */
        Literal _type;

        /**
         *
         */
        int _value;
    };

}

#endif //GSLANGUAGE_GS_INTEGERVALUE_H
