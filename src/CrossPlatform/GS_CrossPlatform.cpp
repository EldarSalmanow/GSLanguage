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

    GSVoid GS_CrossPlatform::setConsoleColor(ConsoleColor text) {
        std::cout << rang::style::bold << consoleColorToFgColor[text];
    }

    GSVoid GS_CrossPlatform::resetConsoleColor() {
        std::cout << rang::fg::reset << rang::style::reset;
    }

}