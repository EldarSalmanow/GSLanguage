#include "../../../include/Compiler/Lexer/GS_Position.h"

namespace GSLanguageCompiler::Lexer {

    GS_Position::GS_Position(size_t line, size_t column) {
        this->_line = line;
        this->_column = column;
    }

    size_t GS_Position::getLine() {
        return this->_line;
    }

    size_t GS_Position::getColumn() {
        return this->_column;
    }

}