#ifndef GSLANGUAGE_GS_READEREXCEPTION_H
#define GSLANGUAGE_GS_READEREXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing errors related to reading files
     */
    class GS_ReaderException : public _GS_Exception {
    public:

        GS_ReaderException(std::string errorMessage) {
            this->errorMessage = errorMessage;
        }

    public:

        std::string getErrorMessage() {
            return this->errorMessage;
        }

        void printErrorMessage() {
            this->_printErrorMessage();
        }
    };

}

#endif //GSLANGUAGE_GS_READEREXCEPTION_H
