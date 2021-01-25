#include "../../../include/Compiler/Lexer/GS_Regex.h"

namespace GSLanguageCompiler {
    std::regex _numberExpression = std::regex(R"(\d)");
    std::regex _wordEnglishLowerCaseExpression = std::regex(R"([a-z])");
    std::regex _wordEnglishUpperCaseExpression = std::regex(R"([A-Z])");
}