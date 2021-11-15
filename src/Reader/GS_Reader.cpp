#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    GS_Reader::GS_Reader(StreamT stream)
            : _stream(stream), _streamIterator(*_stream) {}

    SymbolT GS_Reader::currentSymbol() {
        return *_streamIterator;
    }

    Void GS_Reader::nextSymbol() {
        --_streamIterator;
    }

}