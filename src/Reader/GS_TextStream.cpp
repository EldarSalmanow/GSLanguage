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

}
