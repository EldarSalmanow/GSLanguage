#include <Expressions/GS_UnaryExpression.h>

namespace GSLanguageCompiler::Parser {

    GS_UnaryExpression::GS_UnaryExpression(UnaryOperation operation, GSExpressionPointer expression) {
        this->_operation = operation;
        this->_expression = expression;
    }

    ExpressionType GS_UnaryExpression::getExpressionType() {
        return ExpressionType::UNARY;
    }

    std::string GS_UnaryExpression::generateCode() {
        switch (_operation) {
            case UnaryOperation::MINUS:
                throw Exceptions::GS_Exception("Generating for unary operations not supported!");
        }
    }

    std::string GS_UnaryExpression::toStringForDebug() {
        return "[ "
               + std::string(1, static_cast<char>(this->_operation))
               + this->_expression->toStringForDebug()
               + " ]";
    }

}