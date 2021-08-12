#ifndef GSLANGUAGE_GS_STRINGVALUE_H
#define GSLANGUAGE_GS_STRINGVALUE_H

#include <Parser/Nodes/GS_Value.h>

#include <Parser/GS_TablesOfSymbols.h>

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
         * @param value
         */
        GS_StringValue(GSString value);
    };

}

#endif //GSLANGUAGE_GS_STRINGVALUE_H
