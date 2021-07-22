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
        GS_Exception(GSString errorMessage)
        : _errorMessage(std::move(errorMessage)) {}

    public:

        /**
         *
         * @return
         */
        const GSChar *what() {
            return _errorMessage.c_str();
        }

    private:

        /**
         *
         */
        GSString _errorMessage;
    };

}

#endif //GSLANGUAGE_GS_EXCEPTION_H
