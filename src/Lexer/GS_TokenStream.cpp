#include <GS_TokenStream.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenStream::GS_TokenStream(Ptr<GS_Lexer> lexer)
            : _lexer(lexer) {}

    GSTokenPtr GS_TokenStream::getToken() {
        return _lexer->getToken();
    }

    GS_TokenStream &GS_TokenStream::operator>>(GSTokenPtr &token) {
        token = getToken();

        return *this;
    }

}
