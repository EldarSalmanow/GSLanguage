#ifndef GSLANGUAGE_GS_VALUE_H
#define GSLANGUAGE_GS_VALUE_H

#include <memory>

#include "LiteralTypes.h"

#include "../../../Exceptions/GS_TypeCastException.h"

namespace GSLanguageCompiler {

    class GS_Value;

    typedef std::shared_ptr<GS_Value> GSValuePointer;

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
         * @param type
         * @return
         */
        virtual GSValuePointer castTo(Literal type) = 0; // TODO доделать систему кастинга и убрать лишний код, связанный с прошлой системой

        /**
         *
         * @return
         */
        virtual Literal getLiteralType() = 0;
    };

}

#endif //GSLANGUAGE_GS_VALUE_H
