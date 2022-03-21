#include <Reader/GS_TextStream.h>

namespace GSLanguageCompiler::Reader {

    GS_TextStream::GS_TextStream(LRef<GS_Reader> reader)
            : _string(reader.ReadText()), _stringIterator(_string.begin()) {}

    USymbol GS_TextStream::CurrentSymbol() {
        return *_stringIterator;
    }

    Void GS_TextStream::NextSymbol() {
        ++_stringIterator;
    }

    Void GS_TextStream::PrevSymbol() {
        --_stringIterator;
    }

}
