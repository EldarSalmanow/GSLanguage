#include <GS_Position.h>

namespace GSLanguageCompiler::Lexer {

    GS_Position::GS_Position(std::string code, GS_Coordinate start, GS_Coordinate end)
            : _code(std::move(code)), _startPosition(start), _endPosition(end) {}

    GS_Coordinate GS_Position::getStartPosition() {
        return _startPosition;
    }

    GS_Coordinate GS_Position::getEndPosition() {
        return _endPosition;
    }

    std::string GS_Position::getCode() {
        return _code;
    }

}