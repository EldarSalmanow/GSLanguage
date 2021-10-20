#include <GS_TokenStream.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenStream::GS_TokenStream(GSTokenArrayIterator &tokenIterator)
            : _tokenIterator(tokenIterator) {}

    GS_Token GS_TokenStream::currentToken() {
        return _tokenIterator[0];
    }

    TokenType GS_TokenStream::tokenType(I32 offset) {
        return _tokenIterator[offset].getType();
    }

    String GS_TokenStream::tokenValue(I32 offset) {
        return _tokenIterator[offset].getValue();
    }

    Void GS_TokenStream::next() {
        ++_tokenIterator;
    }

    Void GS_TokenStream::prev() {
        --_tokenIterator;
    }

    Bool GS_TokenStream::isEqualTypes(TokenType type, I32 offset) {
        return type == tokenType(offset);
    }

}
