#ifndef GSLANGUAGE_GS_UNARYEXPRESSION_H
#define GSLANGUAGE_GS_UNARYEXPRESSION_H

#include "GS_Expression.h"

#include "../Values/GS_IntegerValue.h"

namespace GSLanguageCompiler::Expressions {

    /**
     *
     */
    enum class UnaryOperation : char {
        MINUS = '-'
    };

    /**
     *
     */
    class GS_UnaryExpression : public GS_Expression {
    public:

        /**
         *
         */
        GS_UnaryExpression(UnaryOperation operation, GSExpressionPointer expression) {
            this->_operation = operation;
            this->_expression = expression;
        }

    public:

        /**
         *
         * @return
         */
        GSValuePointer result() override {
            switch (this->_operation) {
                case UnaryOperation::MINUS:
                    return GSValuePointer(new Values::GS_IntegerValue(-this->_expression->result()->getInt()));
                default:
                    return nullptr;
            }
        }

        /**
         *
         * @return
         */
        std::string toStringForDebug() override {
            return "[ "
            + std::string(1, static_cast<char>(this->_operation))
            + this->_expression->toStringForDebug()
            + " ]";
        }

    private:

        /**
         *
         */
        UnaryOperation _operation;

        /**
         *
         */
        GSExpressionPointer _expression;
    };

}

#endif //GSLANGUAGE_GS_UNARYEXPRESSION_H
