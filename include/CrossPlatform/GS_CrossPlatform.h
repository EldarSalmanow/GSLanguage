#ifndef GSLANGUAGE_GS_CROSSPLATFORM_H
#define GSLANGUAGE_GS_CROSSPLATFORM_H

#include <map>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace Platform {

    /**
     *
     */
    enum class ConsoleColor {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        GRAY
    };

    /**
     *
     */
    enum class ConsoleStyle {
        BOLD,
        DIM,
        ITALIC,
        UNDERLINE,
        BLINK,
        RBLINK,
        REVERSED,
        CONCEAL,
        CROSSED
    };

    /**
     * A class for erasing a boundary in the operating system.
     * Contains functions for working with the system on different operating systems.
     */
    class GS_CrossPlatform {
    public:

        /**
         *
         * @param fg
         * @return
         */
        static GSVoid setFgConsoleColor(ConsoleColor fg);

        /**
         *
         * @param bg
         * @return
         */
        static GSVoid setBgConsoleColor(ConsoleColor bg);

        /**
         *
         * @param style
         * @return
         */
        static GSVoid setConsoleStyle(ConsoleStyle style);

        /**
         *
         * @return
         */
        static GSVoid resetFgConsoleColor();

        /**
         *
         * @return
         */
        static GSVoid resetBgConsoleColor();

        /**
         *
         * @return
         */
        static GSVoid resetConsoleStyle();

    };

}

#endif //GSLANGUAGE_GS_CROSSPLATFORM_H
