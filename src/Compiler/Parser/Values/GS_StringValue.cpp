#include "../../../../include/Compiler/Parser/Values/GS_StringValue.h"

#include "../../../../include/Compiler/Parser/Values/GS_IntegerValue.h"

namespace GSLanguageCompiler::Values {

    GS_StringValue::GS_StringValue() {
        this->_type = Literal::LITERAL_NULL;
    }

    GS_StringValue::GS_StringValue(std::string value) {
        this->_value = value;
        this->_type = Literal::LITERAL_STRING;
    }

    int GS_StringValue::getInt() {
        int number;
        try {
            number = std::stoi(this->_value);
        } catch (std::exception &exception) {
            throw Exceptions::GS_TypeCastException("Can not cast string value to int!");
        }
        return number;
    }

    std::string GS_StringValue::getString() {
        return this->_value;
    }

    GSValuePointer GS_StringValue::castTo(Literal type) {
        switch (type) {
            case Literal::LITERAL_INT:
                return GSValuePointer(new Values::GS_IntegerValue(std::stoi(this->_value)));
            case Literal::LITERAL_STRING:
                return GSValuePointer(new Values::GS_StringValue(this->_value));
            case Literal::LITERAL_NULL:
            default:
                throw Exceptions::GS_TypeCastException("Can not cast string value to " + convertLiteralToString(this->_type));
        }
    }

    Literal GS_StringValue::getLiteralType() {
        return this->_type;
    }

}