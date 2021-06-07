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
         * @param errorMessage
         */
        GS_Exception(const GSChar *errorMessage)
        : _errorMessage(errorMessage) {}

    public:

        /**
         *
         * @return
         */
        const GSChar *what() {
            return _errorMessage;
        }

    private:

        /**
         *
         */
        const GSChar *_errorMessage;
    };

}

#endif //GSLANGUAGE_GS_EXCEPTION_H
