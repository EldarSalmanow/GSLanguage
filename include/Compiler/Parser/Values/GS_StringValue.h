#ifndef GSLANGUAGE_GS_STRINGVALUE_H
#define GSLANGUAGE_GS_STRINGVALUE_H

#include "GS_Value.h"

namespace GSLanguageCompiler::Values {

    /**
     *
     */
    class GS_StringValue : public GS_Value {
    public:

       /**
        *
        */
       GS_StringValue();

       /**
        *
        * @param value
        */
       GS_StringValue(std::string value);

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
       std::string _value;
    };

}

#endif //GSLANGUAGE_GS_STRINGVALUE_H
