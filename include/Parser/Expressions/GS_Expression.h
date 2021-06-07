#ifndef GSLANGUAGE_GS_EXPRESSION_H
#define GSLANGUAGE_GS_EXPRESSION_H

#include <memory>

#include <Parser/Expressions/GS_ExpressionTypes.h>

#include <Exceptions/GS_Exception.h>

namespace GSLanguageCompiler::Parser {

    /**
     * Base class for expressions
     */
    class GS_Expression {
    public:

        /**
         *
         */
        virtual ~GS_Expression() = default;

    public:

        /**
         *
         * @return
         */
        virtual ExpressionType getExpressionType() = 0;

        /**
         * Generating code
         * @return String with code
         */
        virtual std::string generateCode() = 0;

        /**
         * Converting expression to string
         * @return Converted string
         */
        virtual std::string toStringForDebug() = 0;
    };

    typedef std::shared_ptr<GS_Expression>   GSExpressionPointer;

}

#endif //GSLANGUAGE_GS_EXPRESSION_H
