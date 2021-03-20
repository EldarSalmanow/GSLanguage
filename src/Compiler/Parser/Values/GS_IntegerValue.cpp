#include "../../../../include/Compiler/Parser/Values/GS_IntegerValue.h"

#include "../../../../include/Compiler/Parser/Values/GS_StringValue.h"

namespace GSLanguageCompiler::Values {

    GS_IntegerValue::GS_IntegerValue() {
        this->_type = Literal::LITERAL_NULL;
    }

    GS_IntegerValue::GS_IntegerValue(int value) {
        this->_value = value;
        this->_type = Literal::LITERAL_INT;
    }

    int GS_IntegerValue::getValue() {
        return this->_value;
    }

    int GS_IntegerValue::getInt() {
        return this->_value;
    }

    std::string GS_IntegerValue::getString() {
        return std::to_string(this->_value);
    }

    GSValuePointer GS_IntegerValue::castTo(Literal type) {
        switch (type) {
            case Literal::LITERAL_INT:
                return GSValuePointer(new Values::GS_IntegerValue(this->_value));
            case Literal::LITERAL_STRING:
                return GSValuePointer(new Values::GS_StringValue(std::to_string(this->_value)));
            case Literal::LITERAL_NULL:
                return nullptr;
        }
    }

    Literal GS_IntegerValue::getLiteralType() {
        return this->_type;
    }

}