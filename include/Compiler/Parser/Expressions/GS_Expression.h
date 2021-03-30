#ifndef GSLANGUAGE_GS_EXPRESSION_H
#define GSLANGUAGE_GS_EXPRESSION_H

#include "../Values/GS_Value.h"

namespace GSLanguageCompiler {

    /**
     * Base class for _statements
     */
    class GS_Expression {
    public:

        /**
         *
         * @return
         */
        virtual GSValuePointer result() = 0;

        /**
         *
         * @return
         */
        virtual std::string toStringForDebug() = 0;
    };

    typedef std::shared_ptr<GS_Expression> GSExpressionPointer;
    typedef std::vector<GSExpressionPointer> GSExpressionPointerArray;

}

#endif //GSLANGUAGE_GS_EXPRESSION_H
