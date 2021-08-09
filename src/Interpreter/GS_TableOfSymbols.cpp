#include <GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Interpreter {

    GS_TableOfSymbols::GS_TableOfSymbols() = default;

    GSVoid GS_TableOfSymbols::addVariable(GSString name, Parser::GSValuePtr value) {
        _variableNameToValue[std::move(name)] = std::move(value);
    }

    Parser::GSValuePtr GS_TableOfSymbols::findVariable(GSString name) {
        return _variableNameToValue[std::move(name)];
    }

    GS_TableOfSymbols tableOfSymbols;

}
