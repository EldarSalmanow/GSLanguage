#include "../../../include/Compiler/Parser/GS_TableOfSymbols.h"

namespace GSLanguageCompiler {

    GSValuePointer GS_TableOfSymbols::get(std::string name) {
        GSValuePointer value;

        try {
            value = tableOfSymbols.at(name);
        } catch (std::exception &exception) {
            throw Exceptions::GS_NotFoundVariableException("Variable " + name + " not declared!");
        }

        return value;
    }

    void GS_TableOfSymbols::add(std::string name, GSValuePointer value) {
        variableNames.emplace_back(name);
        tableOfSymbols.emplace(std::make_pair(name, value));
    }

    std::vector<std::string> GS_TableOfSymbols::getVariableNames() {
        return variableNames;
    }

}