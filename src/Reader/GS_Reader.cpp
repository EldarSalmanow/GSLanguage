#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    GS_Reader::GS_Reader(StreamT stream)
            : _stream(stream) {}

    SymbolT GS_Reader::getSymbol() {
        auto symbol = _stream->Get();

        return symbol;
    }

}