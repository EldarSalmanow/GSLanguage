#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    GS_Reader::GS_Reader(StreamT stream)
            : _stream(stream), _line(1), _column(1) {}

    GS_Code GS_Reader::read() {
        Vector<GS_Line> lines;

        while (!_stream->eof()) {
            auto line = _getLine();

            lines.emplace_back(line);
        }

        return GS_Code(lines);
    }

    GS_Line GS_Reader::_getLine() {
        Vector<GS_Symbol> symbols;

        for (auto symbol = _getSymbol(); symbol.getSymbol() != '\n' && !_stream->eof(); symbol = _getSymbol()) {
#if defined(GS_OS_WINDOWS)
            if (symbol.getSymbol() == '\r') {
                continue;
            }
#endif

            symbols.emplace_back(symbol);
        }

        symbols.emplace_back(GS_Symbol('\n', _line, _column));

        _nextLine();

        _column = 1;

        return GS_Line(symbols);
    }

    GS_Symbol GS_Reader::_getSymbol() {
        auto charSymbol = _stream->get();

        _nextSymbol();

        GS_Symbol symbol(static_cast<SymbolT>(charSymbol), _line, _column);

        return symbol;
    }

    Void GS_Reader::_nextLine() {
        ++_line;
    }

    Void GS_Reader::_nextSymbol() {
        ++_column;
    }

}