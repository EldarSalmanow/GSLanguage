#include <Values/GS_IntegerValue.h>

#include <Values/GS_StringValue.h>

namespace GSLanguageCompiler::Parser {

    GS_IntegerValue::GS_IntegerValue() {
        this->setType("Int");
        this->setIsLiteralType(true);
    }

    GS_IntegerValue::GS_IntegerValue(int value) {
        this->setData(value);
        this->setType("Int");
        this->setIsLiteralType(true);
    }

    GSValuePointer GS_IntegerValue::castTo(Literal type) {
        switch (type) {
            case Literal::LITERAL_INT:
                return GSValuePointer(new GS_IntegerValue(std::any_cast<int>(getData())));
            case Literal::LITERAL_STRING:
                return GSValuePointer(new GS_StringValue(std::to_string(std::any_cast<int>(getData()))));
            case Literal::LITERAL_NULL:
                return nullptr;
        }
    }

}