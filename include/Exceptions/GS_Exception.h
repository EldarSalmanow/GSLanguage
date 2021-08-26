#ifndef GSLANGUAGE_GS_EXCEPTION_H
#define GSLANGUAGE_GS_EXCEPTION_H

#include <iostream>

#include <CrossPlatform/GS_PlatformTypes.h>

namespace GSLanguageCompiler::Exceptions {

    /**
     *
     */
    class GS_Exception : std::exception {
    public:

        /**
         *
         */
        GS_Exception() = default;

    public:

        /**
         *
         * @return
         */
        const GSChar *what() {
            return "Error or fatal exception! Please, stop program, if you catch this error!";
        }
    };

}

#endif //GSLANGUAGE_GS_EXCEPTION_H
