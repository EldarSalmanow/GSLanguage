#include <GS_TextStream.h>

namespace GSLanguageCompiler::Reader {

    GS_TextStream::GS_TextStream(Ptr<GS_Reader> reader)
            : _reader(reader) {}

    SymbolT GS_TextStream::getSymbol() {
        auto symbol = _reader->getSymbol();

        return symbol;
    }

    LRef<GS_TextStream> GS_TextStream::operator>>(LRef<SymbolT> symbol) {
        symbol = getSymbol();

        return *this;
    }

    TextStream::TextStream(Ptr<GS_Reader> reader) {
        auto symbol = reader->getSymbol();

        while (symbol.getCodePoint() != 0) {
            _symbols.emplace_back(symbol);

            symbol = reader->getSymbol();
        }

        _index = 0;
    }

    TextStream::TextStream(Vector<SymbolT> symbols)
            : _symbols(std::move(symbols)), _index(0) {}

    TextStream::DataT TextStream::Get() {
        auto symbol = _symbols[_index];

        ++_index;

        return symbol;
    }

    Void TextStream::Put(TextStream::DataT data) {
        throw UException(U"TextStream::Put(TextStream::DataT): TextStream only input stream!");
    }

    StreamPosition TextStream::GetPosition() {
        return StreamPosition(Seek::Begin, StaticCast<I64>(_index));
    }

    Bool TextStream::SetPosition(StreamPosition position) {
        U64 index = 0;

        switch (position.getSeek()) {
            case Seek::Begin:
                index = 0;

                break;
            case Seek::Current:
                index = _index;

                break;
            case Seek::End:
                index = _symbols.size() - 1;

                break;
        }

        index += position.getOffset();

        if (index < 0 && index >= _symbols.size()) {
            return false;
        }

        _index = index;

        return true;
    }

}
