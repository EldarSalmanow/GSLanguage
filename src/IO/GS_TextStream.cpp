#include <GS_TextStream.h>

namespace GSLanguageCompiler::IO {

    GS_TextStream::GS_TextStream(UString text)
            : _string(std::move(text)), _stringIterator(_string.begin()) {}

    GS_TextStream GS_TextStream::Create(UString text) {
        return GS_TextStream(std::move(text));
    }

    GS_TextStream GS_TextStream::Create(LRef<GS_Reader> reader) {
        auto text = reader.ReadText();

        return GS_TextStream(text);
    }

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
