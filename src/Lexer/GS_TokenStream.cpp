#include <GS_TokenStream.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenStream::GS_TokenStream(GSTokenPtrArray tokens)
            : _lexer(nullptr), _tokens(std::move(tokens)), _tokenIterator(_tokens.begin()) {}

    GS_TokenStream::GS_TokenStream(Ptr<GS_Lexer> lexer)
            : _lexer(lexer) {}

    GSTokenPtr GS_TokenStream::getToken() {
        if (!_lexer) {
            auto token = _tokenIterator[0];

            ++_tokenIterator;

            return token;
        }

        return _lexer->getToken();
    }

    GS_TokenStream &GS_TokenStream::operator>>(GSTokenPtr &token) {
        token = getToken();

        return *this;
    }

}
