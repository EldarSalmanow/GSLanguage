#ifndef GSLANGUAGE_GS_BINARYEXPRESSION_H
#define GSLANGUAGE_GS_BINARYEXPRESSION_H

#include "../Values/GS_IntegerValue.h"

#include "GS_Expression.h"

#include "../../../Exceptions/GS_ArithmeticException.h"

namespace GSLanguageCompiler::Expressions {

    /**
     *
     */
    enum class BinaryOperation : char {
        PLUS  = '+',
        MINUS = '-',
        STAR  = '*',
        SLASH = '/'
    };

    /**
     *
     */
    class GS_BinaryExpression : public GS_Expression {
    public:

        /**
         *
         * @param operation
         * @param firstValue
         * @param secondValue
         */
        GS_BinaryExpression(BinaryOperation operation, GSExpressionPointer firstValue, GSExpressionPointer secondValue) {
            this->_operation = operation;
            this->_firstExpression = firstValue;
            this->_secondExpression = secondValue;
        }

    public:

        /**
         *
         * @return
         */
        GSValuePointer result() override {
            int result;

            GSValuePointer firstValueResult = this->_firstExpression->result();
            GSValuePointer secondValueResult = this->_secondExpression->result();

            switch (this->_operation) {
                case BinaryOperation::PLUS:
                    result = firstValueResult->getInt() + secondValueResult->getInt();
                    break;
                case BinaryOperation::MINUS:
                    result = firstValueResult->getInt() - secondValueResult->getInt();
                    break;
                case BinaryOperation::STAR:
                    result = firstValueResult->getInt() * secondValueResult->getInt();
                    break;
                case BinaryOperation::SLASH:
                    if (secondValueResult->getInt() == 0) {
                        throw Exceptions::GS_ArithmeticException("Division by zero!");
                    } else {
                        result = firstValueResult->getInt() / secondValueResult->getInt();
                        break;
                    }
            }

            return GSValuePointer(new Values::GS_IntegerValue(result));
        }

        /**
         *
         * @return
         */
        std::string toStringForDebug() override {
            return "[ "
            + this->_firstExpression->toStringForDebug()
            + " "
            + std::string(1, static_cast<char>(this->_operation))
            + " "
            + this->_secondExpression->toStringForDebug()
            + " ]";
        }

    private:

        /**
         *
         */
        BinaryOperation _operation;

        /**
         *
         */
        GSExpressionPointer _firstExpression;

        /**
         *
         */
        GSExpressionPointer _secondExpression;
    };

}

#endif //GSLANGUAGE_GS_BINARYEXPRESSION_H
