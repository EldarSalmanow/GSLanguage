#ifndef GSLANGUAGE_GS_VALUE_H
#define GSLANGUAGE_GS_VALUE_H

#include "LiteralTypes.h"

#include "../../../Exceptions/GS_TypeCastException.h"

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
        virtual int getInt() = 0;

        /**
         *
         * @return
         */
        virtual std::string getString() = 0;

        /**
         *
         * @return
         */
        virtual Literal getLiteralType() = 0;
    };

    typedef std::shared_ptr<GS_Value> GSValuePointer;

}

#endif //GSLANGUAGE_GS_VALUE_H
