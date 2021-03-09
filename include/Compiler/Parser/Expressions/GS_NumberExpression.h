#ifndef GSLANGUAGE_GS_NUMBEREXPRESSION_H
#define GSLANGUAGE_GS_NUMBEREXPRESSION_H

#include "../Values/GS_IntegerValue.h"

#include "GS_Expression.h"

namespace GSLanguageCompiler::Expressions {

    /**
     *
     */
    class GS_NumberExpression : public GS_Expression {
    public:

        /**
         *
         * @param number
         */
        GS_NumberExpression(int number) {
            this->_number = Values::GS_IntegerValue(number);
        }

    public:

        /**
         *
         * @return
         */
        Values::GS_IntegerValue getNumber() {
            return this->_number;
        }

    public:

        /**
         *
         * @return
         */
        GSValuePointer result() override {
            return GSValuePointer(new Values::GS_IntegerValue(this->_number));
        }

        /**
         *
         * @return
         */
        std::string toStringForDebug() override {
            return std::to_string(this->_number.getValue());
        }

    private:

        /**
         *
         */
        Values::GS_IntegerValue _number;
    };

}

#endif //GSLANGUAGE_GS_NUMBEREXPRESSION_H
