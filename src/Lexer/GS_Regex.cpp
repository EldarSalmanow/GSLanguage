#include <GS_Regex.h>

namespace GSLanguageCompiler::Lexer {

    std::regex _numberExpression               = std::regex(R"(\d)");

    std::regex _wordEnglishExpression          = std::regex(R"([a-zA-Z])");

}