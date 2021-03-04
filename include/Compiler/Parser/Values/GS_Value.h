#ifndef GSLANGUAGE_GS_VALUE_H
#define GSLANGUAGE_GS_VALUE_H

#include "LiteralTypes.h"

namespace GSLanguageCompiler {

    /**
     *
     */
    class GS_Value {
    public:

        /**
         *
         * @return
         */
        virtual Literal getLiteralType() = 0;
    };

}

#endif //GSLANGUAGE_GS_VALUE_H
