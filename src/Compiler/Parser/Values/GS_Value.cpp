#include <Values/GS_Value.h>

namespace GSLanguageCompiler::Parser {

    std::any GS_Value::getData() {
        if (!this->_data.has_value()) {
            // TODO изменить систему выброса ошибок (неоправданно много классов)
            throw Exceptions::GS_TypeCastException("Null data in value!");
        }

        return this->_data;
    }

    void GS_Value::deleteData() {
        this->_data.reset();
    }

    std::string GS_Value::getType() {
        return this->_type;
    }

    void GS_Value::setType(const std::string &type) {
        this->_type = type;
    }

    bool GS_Value::getIsLiteralType() {
        return this->_isLiteralType;
    }

    void GS_Value::setIsLiteralType(bool isLiteralType) {
        this->_isLiteralType = isLiteralType;
    }

}