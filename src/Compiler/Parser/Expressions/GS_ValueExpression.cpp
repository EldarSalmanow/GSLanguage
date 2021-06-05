#include <Expressions/GS_VaLueExpression.h>

namespace GSLanguageCompiler::Parser {

    GS_ValueExpression::GS_ValueExpression(GSValuePointer value) {
        this->_value = value;
//        this->_type = value->getLiteralType();
    }

//    GS_ValueExpression::GS_ValueExpression(GSValuePointer value, Literal type) {
//        if (value->getLiteralType() != type) {
//            this->_value = value->castTo(type);
//            this->_type = type;
//        } else {
//            this->_value = value;
//            this->_type = type;
//        }
//    }

    GSValuePointer GS_ValueExpression::getValue() {
        return this->_value;
    }

//    Literal GS_ValueExpression::getType() {
//        return this->_value->getType();
//    }

    ExpressionType GS_ValueExpression::getExpressionType() {
        return ExpressionType::VALUE;
    }

//    std::string GS_ValueExpression::generateCode() {
//        switch (this->_type) {
//            case Literal::LITERAL_INT:
//                return "push " + this->_value->getString() + "\n";
//            case Literal::LITERAL_NULL:
//            case Literal::LITERAL_STRING:
//                throw Exceptions::GS_NotSupportedException(
//                        "Generating code for null and string types not supported!");
//        }
//    }

    std::string GS_ValueExpression::generateCode() {
        std::string type = _value->getType();

        if (type == "Int") {
            return "push " + std::to_string(std::any_cast<int>(_value->getData())) + "\n";
        } else if (type == "String") {
            throw Exceptions::GS_NotSupportedException("Generating code for string types not supported!");
        } else {
            throw Exceptions::GS_NotSupportedException("Generating code for null types not supported!");
        }
    }

    std::string GS_ValueExpression::toStringForDebug() {
        return _value->getType();
    }

}
