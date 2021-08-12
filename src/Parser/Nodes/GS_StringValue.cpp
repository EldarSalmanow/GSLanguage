#include <Nodes/GS_StringValue.h>

namespace GSLanguageCompiler::Parser {

    GS_StringValue::GS_StringValue()
            : GS_Value("String", "") {}

    GS_StringValue::GS_StringValue(GSString value)
            : GS_Value("String", std::move(value)) {
        tableOfConstants.addConstant(getData<GSString>());
    }

}
