#include "../../../include/Compiler/Lexer/GS_Coordinate.h"

namespace GSLanguageCompiler::Lexer {

    GS_Coordinate::GS_Coordinate(size_t line, size_t column) {
        this->_line = line;
        this->_column = column;
    }

    size_t GS_Coordinate::getLine() {
        return this->_line;
    }

    size_t GS_Coordinate::getColumn() {
        return this->_column;
    }

}