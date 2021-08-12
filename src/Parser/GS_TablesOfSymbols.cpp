#include <GS_TablesOfSymbols.h>

namespace GSLanguageCompiler::Parser {

    GS_TableOfVariables::GS_TableOfVariables() = default;

    GSVoid GS_TableOfVariables::addVariable(GSString name, GSValuePtr value) {
        static GSInt id = 0;

        _idToValue[id] = std::move(value);

        _nameToId[std::move(name)] = id;

        ++id;
    }

    GSValuePtr GS_TableOfVariables::getValueById(GSInt id) {
        return _idToValue[id];
    }

    GSInt GS_TableOfVariables::getIdByName(GSString name) {
        return _nameToId[std::move(name)];
    }

    GS_TableOfConstants::GS_TableOfConstants() = default;

    GSVoid GS_TableOfConstants::addConstant(GSString value) {
        static GSInt id = 0;

        _idToValue[id] = std::move(value);

        _valueToId[std::move(value)] = id;

        ++id;
    }

    GSString GS_TableOfConstants::getValueById(GSInt id) {
        return _idToValue[id];
    }

    GSInt GS_TableOfConstants::getIdByValue(GSString value) {
        return _valueToId[std::move(value)];
    }

    GS_TableOfVariables tableOfVariables;

    GS_TableOfConstants tableOfConstants;

}
