#include <GS_TextStream.h>

#include <GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_Reader::GS_Reader(LRef<std::istream> stream)
            : _stream(stream) {}

    GS_Reader GS_Reader::Create(LRef<std::istream> stream) {
        return GS_Reader(stream);
    }

    UString GS_Reader::ReadText() {
        UString text;

        while (true) {
            UString string;

            _stream >> string;

            if (_stream.eof()) {
                break;
            }

            string += "\n"_us;

            text += string;
        }

        return text;
    }

    GS_TextStream GS_Reader::CreateStream() {
        return GS_TextStream::Create(*this);
    }

}