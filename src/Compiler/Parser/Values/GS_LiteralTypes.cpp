#include "../../../../include/Compiler/Parser/Values/LiteralTypes.h"

namespace GSLanguageCompiler {

    std::vector<Literal> types = {
            Literal::LITERAL_INT,
            Literal::LITERAL_STRING
    };

    Literal convertTokenTypeToLiteral(TokenType type) {
        switch (type) {
            case TokenType::KEYWORD_TYPE_INT:
                return Literal::LITERAL_INT;
            case TokenType::KEYWORD_TYPE_STRING:
                return Literal::LITERAL_STRING;
            default:
                return Literal::LITERAL_NULL;
        }
    }

    std::string convertLiteralToString(Literal literal) {
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