#include <Values/GS_StringValue.h>

#include <Values/GS_IntegerValue.h>

namespace GSLanguageCompiler::Parser {

    GS_StringValue::GS_StringValue() {
        this->setType("String");
        this->setIsLiteralType(true);
    }

    GS_StringValue::GS_StringValue(std::string value) {
        this->setData(value);
        this->setType("String");
        this->setIsLiteralType(true);
    }

    GSValuePointer GS_StringValue::castTo(Literal type) {
        switch (type) {
            case Literal::LITERAL_INT:
                return GSValuePointer(new GS_IntegerValue(std::stoi(std::any_cast<std::string>(getData()))));
            case Literal::LITERAL_STRING:
                return GSValuePointer(new GS_StringValue(std::any_cast<std::string>(getData())));
            case Literal::LITERAL_NULL:
            default:
                throw Exceptions::GS_TypeCastException("Can not cast string value to " + convertLiteralToString(type));
        }
    }

}