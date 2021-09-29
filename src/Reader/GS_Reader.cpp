#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler::Reader {

    GS_Reader::GS_Reader(StreamT stream, String filename)
            : _stream(std::move(stream)), _filename(std::move(filename)), _line(1), _column(1) {}

    GS_Code GS_Reader::read() {
        _openFile();

        Vector<GS_Line> lines;

        while (!_stream.eof()) {
            auto line = _getLine();

            lines.emplace_back(line);
        }

        return GS_Code(lines);
    }

    Void GS_Reader::_openFile() {
        _stream.open(_filename);

        if (!_stream.is_open()) {
//            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
//                                           "Can`t open file for reading!");
//
//            SStream stream;
//
//            stream << "Filename: \"" << _filename << "\"!";
//
//            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
//                                           stream.str());
//
//            Exceptions::errorHandler.throw_(); todo add throwing exception
        }
    }

    GS_Line GS_Reader::_getLine() {
        Vector<GS_Symbol> symbols;

        for (auto symbol = _getSymbol(); symbol.getSymbol() != '\n' && !_stream.eof(); symbol = _getSymbol()) {
#if defined(OS_WINDOWS)
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
        StreamCharType charSymbol;

        _stream.read(&charSymbol, 1);

        _nextSymbol();

        GS_Symbol symbol(charSymbol, _line, _column);

        return symbol;
    }

    Void GS_Reader::_nextLine() {
        ++_line;
    }

    Void GS_Reader::_nextSymbol() {
        ++_column;
    }

}