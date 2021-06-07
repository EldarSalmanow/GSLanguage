#ifndef GSLANGUAGE_GS_STRINGVALUE_H
#define GSLANGUAGE_GS_STRINGVALUE_H

#include <Parser/Values/GS_Value.h>

namespace GSLanguageCompiler::Parser {

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
         * @param type
         * @return
         */
        GSValuePointer castTo(Literal type) override;
    };

}

#endif //GSLANGUAGE_GS_STRINGVALUE_H
