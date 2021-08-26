#include <rang/rang.hpp>

#include <Exceptions/GS_ErrorHandler.h>

namespace GSLanguageCompiler::Exceptions {

    std::map<ErrorLevel, rang::fg> errorLevelToFgColor = {
            {ErrorLevel::NOTE_LVL,    rang::fg::blue},
            {ErrorLevel::WARNING_LVL, rang::fg::yellow},
            {ErrorLevel::ERROR_LVL,   rang::fg::red},
            {ErrorLevel::FATAL_LVL,   rang::fg::black}
    };

    std::map<ErrorLevel, GSString> errorLevelToString = {
            {ErrorLevel::NOTE_LVL,    "Note"},
            {ErrorLevel::WARNING_LVL, "Warning"},
            {ErrorLevel::ERROR_LVL,   "Error"},
            {ErrorLevel::FATAL_LVL,   "Fatal"}
    };

    GS_ErrorHandler::GS_ErrorHandler() {
        rang::setControlMode(rang::control::Auto);
        rang::setWinTermMode(rang::winTerm::Auto);
    }

    GSVoid GS_ErrorHandler::print(ErrorLevel errorLevel, Lexer::GS_Position position, GSString message) {
        auto textConsoleStyle = rang::style::bold;
        auto textConsoleColor = errorLevelToFgColor[errorLevel];
        auto codeConsoleColor = rang::fg::green;

        auto stringErrorLevel = errorLevelToString[errorLevel];

        std::cout << textConsoleStyle << textConsoleColor;

        std::cout << "| " << position.getEndPosition().getLine() << ": " << stringErrorLevel << " >>  ";

        std::cout << codeConsoleColor;

        std::cout << position.getCode() << std::endl;

        std::cout << textConsoleColor;

        std::cout << "|";

        for (int i = 0; i < position.getEndPosition().getColumn()
        + std::to_string(position.getEndPosition().getLine()).size()
        + stringErrorLevel.size() + 7; ++i) {
            std::cout << " ";
        }

        std::cout << "^^^" << std::endl << "| " << message << std::endl;

        std::cout << rang::fg::reset << rang::style::reset;
    }

    GSVoid GS_ErrorHandler::print(ErrorLevel errorLevel, GSString message) {
        auto textConsoleStyle = rang::style::bold;
        auto textConsoleColor = errorLevelToFgColor[errorLevel];
        auto codeConsoleColor = rang::fg::green;

        auto stringErrorLevel = errorLevelToString[errorLevel];

        std::cout << textConsoleStyle << textConsoleColor;

        std::cout << "| " << stringErrorLevel << " >>  " << message << std::endl;

        std::cout << rang::fg::reset << rang::style::reset;
    }

    GSVoid GS_ErrorHandler::throw_() {
        throw GS_Exception();
    }

    GS_ErrorHandler errorHandler;

}
