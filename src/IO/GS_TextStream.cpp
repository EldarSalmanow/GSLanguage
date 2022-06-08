#include <GS_TextStream.h>

namespace GSLanguageCompiler::IO {

    GS_TextStream::GS_TextStream(GSSymbolArray symbols)
            : _symbols(std::move(symbols)), _symbolsIterator(_symbols.begin()) {}

    GS_TextStream GS_TextStream::Create(GSSymbolArray symbols) {
        return GS_TextStream(std::move(symbols));
    }

    GS_TextStream GS_TextStream::Create(LRef<GS_Reader> reader) {
        auto symbols = reader.ReadSymbols();

        return GS_TextStream::Create(symbols);
    }

    GS_TextStream GS_TextStream::Create(UString text) {
        GSSymbolArray symbols;

        for (auto &symbol : text) {
            symbols.emplace_back(GS_Symbol::Create(symbol));
        }

        return GS_TextStream::Create(symbols);
    }

    GS_Symbol GS_TextStream::CurrentSymbol() {
        return *_symbolsIterator;
    }

    Void GS_TextStream::NextSymbol() {
        ++_symbolsIterator;
    }

    Void GS_TextStream::PrevSymbol() {
        --_symbolsIterator;
    }

}
