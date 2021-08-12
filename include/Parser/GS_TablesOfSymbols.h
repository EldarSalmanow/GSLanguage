#ifndef GSLANGUAGE_GS_TABLESOFSYMBOLS_H
#define GSLANGUAGE_GS_TABLESOFSYMBOLS_H

#include <map>

#include <Parser/Nodes/GS_IntegerValue.h>
#include <Parser/Nodes/GS_StringValue.h>

namespace GSLanguageCompiler::Parser {

    class GS_TableOfVariables {
    public:

        GS_TableOfVariables();

    public:

        GSVoid addVariable(GSString name, GSValuePtr value);

        GSValuePtr getValueById(GSInt id);

        GSInt getIdByName(GSString name);

    private:

        std::map<GSInt, GSValuePtr> _idToValue;

        std::map<GSString, GSInt> _nameToId;
    };

    class GS_TableOfConstants {
    public:

        GS_TableOfConstants();

    public:

        GSVoid addConstant(GSString value);

        GSString getValueById(GSInt id);

        GSInt getIdByValue(GSString value);

    private:

        std::map<GSInt, GSString> _idToValue;

        std::map<GSString, GSInt> _valueToId;
    };

    extern GS_TableOfVariables tableOfVariables;

    extern GS_TableOfConstants tableOfConstants;

}

#endif //GSLANGUAGE_GS_TABLESOFSYMBOLS_H
