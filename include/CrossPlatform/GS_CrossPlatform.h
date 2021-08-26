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
     * A class for erasing a boundary in the operating system.
     * Contains functions for working with the system on different operating systems.
     */
    class GS_CrossPlatform {
    public:

        /**
         * Setting console color
         * @param text Text color
         */
        static GSVoid setConsoleColor(ConsoleColor text);

        /**
         *
         * @return
         */
        static GSVoid resetConsoleColor();

    };

}

#endif //GSLANGUAGE_GS_CROSSPLATFORM_H
