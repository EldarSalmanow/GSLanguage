#include <GS_Coordinate.h>

namespace GSLanguageCompiler::Lexer {

    GS_Coordinate::GS_Coordinate(GSULongLong line, GSULongLong column) {
        this->_line = line;
        this->_column = column;
    }

    GSULongLong GS_Coordinate::getLine() {
        return this->_line;
    }

    GSULongLong GS_Coordinate::getColumn() {
        return this->_column;
    }

}