#include <rang/rang.hpp>

#include <GS_CrossPlatform.h>

namespace Platform {

    std::map<ConsoleColor, rang::fg> consoleColorToFgColor = {
            {ConsoleColor::BLACK,   rang::fg::black},
            {ConsoleColor::RED,     rang::fg::red},
            {ConsoleColor::GREEN,   rang::fg::green},
            {ConsoleColor::YELLOW,  rang::fg::yellow},
            {ConsoleColor::BLUE,    rang::fg::blue},
            {ConsoleColor::MAGENTA, rang::fg::magenta},
            {ConsoleColor::CYAN,    rang::fg::cyan},
            {ConsoleColor::GRAY,    rang::fg::gray}
    };

    std::map<ConsoleColor, rang::bg> consoleColorToBgColor = {
            {ConsoleColor::BLACK,   rang::bg::black},
            {ConsoleColor::RED,     rang::bg::red},
            {ConsoleColor::GREEN,   rang::bg::green},
            {ConsoleColor::YELLOW,  rang::bg::yellow},
            {ConsoleColor::BLUE,    rang::bg::blue},
            {ConsoleColor::MAGENTA, rang::bg::magenta},
            {ConsoleColor::CYAN,    rang::bg::cyan},
            {ConsoleColor::GRAY,    rang::bg::gray}
    };

    std::map<ConsoleStyle, rang::style> consoleStyleToToStyle = {
            {ConsoleStyle::BOLD,      rang::style::bold},
            {ConsoleStyle::DIM,       rang::style::dim},
            {ConsoleStyle::ITALIC,    rang::style::italic},
            {ConsoleStyle::UNDERLINE, rang::style::underline},
            {ConsoleStyle::BLINK,     rang::style::blink},
            {ConsoleStyle::RBLINK,    rang::style::rblink},
            {ConsoleStyle::REVERSED,  rang::style::reversed},
            {ConsoleStyle::CONCEAL,   rang::style::conceal},
            {ConsoleStyle::CROSSED,   rang::style::crossed}
    };

    GSVoid GS_CrossPlatform::setFgConsoleColor(ConsoleColor fg) {
        std::cout << consoleColorToFgColor[fg];
    }

    GSVoid GS_CrossPlatform::setBgConsoleColor(ConsoleColor bg) {
        std::cout << consoleColorToBgColor[bg];
    }

    GSVoid GS_CrossPlatform::setConsoleStyle(ConsoleStyle style) {
        std::cout << consoleStyleToToStyle[style];
    }

    GSVoid GS_CrossPlatform::resetFgConsoleColor() {
        std::cout << rang::fg::reset;
    }

    GSVoid GS_CrossPlatform::resetBgConsoleColor() {
        std::cout << rang::bg::reset;
    }

    GSVoid GS_CrossPlatform::resetConsoleStyle() {
        std::cout << rang::style::reset;
    }

}