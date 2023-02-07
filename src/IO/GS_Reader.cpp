#include <GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_Reader::GS_Reader(LRef<InputStream> stream)
            : _stream(stream) {}

    GS_Reader GS_Reader::Create(LRef<InputStream> stream) {
        return GS_Reader(stream);
    }

    UString GS_Reader::Run(LRef<InputStream> stream) {
        auto reader = GS_Reader::Create(stream);

        auto text = reader.Read();

        return text;
    }

    UString GS_Reader::Read() {
        UString text;

        while (true) {
            USymbol symbol;

            _stream >> symbol;

            if (_stream.eof()) {
                break;
            }

            text += symbol;
        }

        // adding EOF symbol
        text += USymbol();

        return text;
    }

}