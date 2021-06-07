#include <GS_Variable.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_Variable::GS_Variable(const std::string &name, const std::string &type, std::any &data) {
        this->_name = name;
        this->_type = type;
        this->_data = data;
    }

    std::string GS_Variable::getName() {
        return this->_name;
    }

    std::string GS_Variable::getType() {
        return this->_type;
    }

    std::any GS_Variable::getData() {
        return this->_data;
    }

}