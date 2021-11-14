#include <GS_TokenStream.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenStream::GS_TokenStream(GS_Lexer lexer)
            : _lexer(lexer) {}

    GS_Token GS_TokenStream::getToken() {
        return _lexer.getToken();
    }

    GS_TokenStream &GS_TokenStream::operator>>(GS_Token &token) {
        token = getToken();

        return *this;
    }

}
