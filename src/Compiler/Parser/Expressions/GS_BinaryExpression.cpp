#include <Expressions/GS_BinaryExpression.h>

namespace GSLanguageCompiler::Parser {

    GS_BinaryExpression::GS_BinaryExpression(BinaryOperation operation,
                                             GSExpressionPointer firstValue,
                                             GSExpressionPointer secondValue) {
        this->_operation = operation;
        this->_firstExpression = firstValue;
        this->_secondExpression = secondValue;
    }

    ExpressionType GS_BinaryExpression::getExpressionType() {
        return ExpressionType::BINARY;
    }

    std::string GS_BinaryExpression::generateCode() {
        switch (_operation) {
            case BinaryOperation::PLUS:
                return _firstExpression->generateCode() + _secondExpression->generateCode() + "add\n";
            case BinaryOperation::MINUS:
                return _firstExpression->generateCode() + _secondExpression->generateCode() + "sub\n";
            case BinaryOperation::STAR:
            case BinaryOperation::SLASH:
                throw Exceptions::GS_NotSupportedException(
                        "Generating code for multiplicative and division not supported!");
        }
    }

    std::string GS_BinaryExpression::toStringForDebug() {
        return "[ "
               + this->_firstExpression->toStringForDebug()
               + " "
               + std::string(1, static_cast<char>(this->_operation))
               + " "
               + this->_secondExpression->toStringForDebug()
               + " ]";
    }

}