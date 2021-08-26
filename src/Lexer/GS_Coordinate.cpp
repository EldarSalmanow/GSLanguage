#include <GS_Coordinate.h>

namespace GSLanguageCompiler::Lexer {

    GS_Coordinate::GS_Coordinate(GSULongLong line, GSULongLong column)
            : _line(line), _column(column) {}

    GSULongLong GS_Coordinate::getLine() {
        return _line;
    }

    GSULongLong GS_Coordinate::getColumn() {
        return _column;
    }

}