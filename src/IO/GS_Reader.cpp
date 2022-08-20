#include <GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_Reader::GS_Reader(GSInStreamPtr stream)
            : _stream(std::move(stream)) {}

    GS_Reader GS_Reader::Create(GSInStreamPtr stream) {
        return GS_Reader(std::move(stream));
    }

    UString GS_Reader::Run(GSInStreamPtr stream) {
        auto reader = GS_Reader::Create(std::move(stream));

        auto text = reader.Read();

        return text;
    }

    UString GS_Reader::Read() {
        UString text;

        auto &stream = _stream->GetInStream();

        while (true) {
            USymbol symbol;

            stream >> symbol;

            if (stream.eof()) {
                break;
            }

            text += symbol;
        }

        text += USymbol();

        return text;
    }

}