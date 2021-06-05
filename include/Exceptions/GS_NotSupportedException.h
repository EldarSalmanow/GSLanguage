#ifndef GSLANGUAGE_GS_NOTSUPPORTEDEXCEPTION_H
#define GSLANGUAGE_GS_NOTSUPPORTEDEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Special error for throwing errors with not supporting possibilities
     */
    class GS_NotSupportedException : public _GS_Exception {
    public:

        GS_NotSupportedException(std::string errorMessage) {
            this->errorMessage = errorMessage;
        }

    public:

        std::string getErrorMessage() {
            return this->_getErrorMessage();
        }

        void printErrorMessage() {
            return this->_printErrorMessage();
        }

    };

}

#endif //GSLANGUAGE_GS_NOTSUPPORTEDEXCEPTION_H
