#include <GS_TokenStream.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenStream::GS_TokenStream(LRef<GS_Lexer> lexer)
            : _tokens(lexer.Tokenize()), _tokenIterator(_tokens.begin()) {}

    GS_Token GS_TokenStream::CurrentToken() {
        return *_tokenIterator;
    }

    Void GS_TokenStream::NextToken() {
        ++_tokenIterator;
    }

    Void GS_TokenStream::PrevToken() {
        --_tokenIterator;
    }

}
