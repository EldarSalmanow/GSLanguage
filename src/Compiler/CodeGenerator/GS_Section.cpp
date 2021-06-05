#include <GS_Section.h>

namespace GSLanguageCompiler::CodeGenerator {

    void GS_Section::addLineToSection(const std::string &line) {
        this->_sectionCode += line;
    }

    std::string GS_Section::getSectionCode() {
        return this->_sectionCode;
    }

}