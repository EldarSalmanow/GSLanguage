#ifndef GSLANGUAGE_GS_CROSSPLATFORM_H
#define GSLANGUAGE_GS_CROSSPLATFORM_H

#include <Compiler/Util/GS_PlatformTypes.h>

#if defined(OS_WINDOWS)
#  if defined(COMPILER_MSVC)
#    include <Windows.h>
#  endif
#  if defined(COMPILER_MINGW)
#    include <windows.h>
#  endif
#endif

#if defined(OS_LINUX)
#  include <iostream>
#endif

namespace Platform {

    /**
     * A class for erasing a boundary in the operating system.
     * Contains functions for working with the system on different operating systems.
     */
    class GS_CrossPlatform {
    public:

        /**
         * Available console colors for coloring console
         */
#if defined(OS_WINDOWS)
        enum ConsoleColor {
            BLACK = 0,
            BLUE = 1,
            GREEN = 2,
            CYAN = 3,
            RED = 4,
            MAGENTA = 5,
            YELLOW = 14,
            WHITE = 15
        };
#endif

#if defined(OS_LINUX)
        enum ConsoleColor {
            BLACK = 0,
            RED = 1,
            GREEN = 2,
            YELLOW = 3,
            BLUE = 4,
            MAGENTA = 5,
            CYAN = 6,
            WHITE = 7
        };
#endif

    public:

        /**
         * Setting console color
         * @param background Background color
         * @param text Text color
         */
        static GSVoid setConsoleColor(ConsoleColor background, ConsoleColor text);

    };

}

#endif //GSLANGUAGE_GS_CROSSPLATFORM_H
