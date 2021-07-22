#include <Nodes/GS_IntegerValue.h>

namespace GSLanguageCompiler::Parser {

    GS_IntegerValue::GS_IntegerValue()
            : GS_Value("Int", 0) {}

    GS_IntegerValue::GS_IntegerValue(GSInt value)
            : GS_Value("Int", value) {}

}