#include "../../../include/Compiler/Parser/GS_Parser.h"

namespace GSLanguageCompiler {

    std::vector<std::shared_ptr<GS_Expression>> GS_Parser::parse() {
        this->tokenIterator = this->tokens.begin();
        while (this->tokenIterator != tokens.end()) {
            // parsing code here
            ++this->tokenIterator;
        }
        return this->expressions;
    }

}