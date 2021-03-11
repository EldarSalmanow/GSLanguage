#ifndef GSLANGUAGE_GS_CROSSPLATFORM_H
#define GSLANGUAGE_GS_CROSSPLATFORM_H

#if defined(__WIN32)
#include <windows.h>
#else
#error Platform not supported
#endif

namespace Platform {

    /**
     * A class for erasing a boundary in the operating system.
     * Contains functions for working with the system on different operating systems.
     */
    class GS_CrossPlatform {
    public:

        /**
         * Available console colors for Windows
         */
        enum ConsoleColor {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            CYAN = 3,
            RED = 4,
            MAGENTA = 5,
            BROWN = 6,
            LIGHT_GRAY = 7,
            DARK_GRAY = 8,
            LIGHT_BLUE = 9,
            LIGHT_GREEN = 10,
            LIGHT_CYAN = 11,
            LIGHT_RED = 12,
            LIGHT_MAGENTA = 13,
            YELLOW = 14,
            WHITE = 15
        };

    public:

        /**
         * Setting console color
         * @param background Background color
         * @param text Text color
         */
        static void setConsoleColor(ConsoleColor background, ConsoleColor text);

    };

}

#endif //GSLANGUAGE_GS_CROSSPLATFORM_H
