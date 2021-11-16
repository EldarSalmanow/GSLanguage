#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    GS_Reader::GS_Reader(StreamT stream)
            : _stream(stream) {}

    SymbolT GS_Reader::getSymbol() {
        return static_cast<SymbolT>(_stream->rdbuf()->sgetc());
    }

    SymbolT GS_Reader::nextSymbol() {
        return static_cast<SymbolT>(_stream->rdbuf()->snextc());
    }

    SymbolT GS_Reader::prevSymbol() {
        return static_cast<SymbolT>(_stream->rdbuf()->sungetc());
    }

}