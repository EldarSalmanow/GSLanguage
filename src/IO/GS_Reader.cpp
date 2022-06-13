#include <GS_TextStream.h>

#include <GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_Reader::GS_Reader(GSInStreamPtr stream)
            : _stream(std::move(stream)) {}

    GS_Reader GS_Reader::Create(GSInStreamPtr stream) {
        return GS_Reader(std::move(stream));
    }

    GSSymbolArray GS_Reader::ReadSymbols() {
        GSSymbolArray symbols;

        auto &stream = _stream->GetInStream();
        auto streamInfo = _stream->GetStreamInfo();

        auto sourceName = streamInfo->GetFileName();
        U64 line = 1;
        U64 column = 1;

        while (true) {
            USymbol symbol;

            stream >> symbol;

            if (stream.eof()) {
                break;
            }

            auto location = GS_SymbolLocation::Create(sourceName, line, column);

            symbols.emplace_back(GS_Symbol::Create(symbol, location));

            if (symbol == '\n') {
                ++line;

                column = 1;
            } else {
                ++column;
            }
        }

        symbols.emplace_back(GS_Symbol::Create());

        return symbols;
    }

    GS_TextStream GS_Reader::CreateStream() {
        return GS_TextStream::Create(*this);
    }

}