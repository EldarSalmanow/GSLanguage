#include "../../../../include/Compiler/Parser/Values/LiteralTypes.h"

namespace GSLanguageCompiler {

    std::vector<Literal> types = {
            Literal::LITERAL_INT,
            Literal::LITERAL_STRING
    };

    std::string literalToString(Literal literal) {
        switch (literal) {
            case Literal::LITERAL_NULL:
                return "LITERAL_NULL";
            case Literal::LITERAL_INT:
                return "LITERAL_INT";
            case Literal::LITERAL_STRING:
                return "LITERAL_STRING";

            default:
                return "!!ERROR!!";
        }
    }

}