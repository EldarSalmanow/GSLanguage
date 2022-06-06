#include <GS_TextStream.h>

#include <GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_Reader::GS_Reader(std::unique_ptr<GS_InStream> stream)
            : _stream(std::move(stream)) {}

    GS_Reader GS_Reader::Create(std::unique_ptr<GS_InStream> stream) {
        return GS_Reader(std::move(stream));
    }

    UString GS_Reader::ReadText() {
        UString text;

        while (true) {
            UString string;

            _stream->GetInStream() >> string;

            if (_stream->GetInStream().eof()) {
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