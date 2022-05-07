#include <GS_TokenStream.h>

namespace GSLanguageCompiler::Lexer {

    GS_TokenStream::GS_TokenStream(GSTokenArray tokens)
            : _tokens(std::move(tokens)), _tokenIterator(_tokens.begin()) {}

    GS_TokenStream GS_TokenStream::Create(GSTokenArray tokens) {
        return GS_TokenStream(std::move(tokens));
    }

    GS_TokenStream GS_TokenStream::Create(LRef<GS_Lexer> lexer) {
        auto tokens = lexer.Tokenize();

        return GS_TokenStream::Create(tokens);
    }

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
