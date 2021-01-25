#ifndef GSLANGUAGE_GS_ARGUMENTEXCEPTION_H
#define GSLANGUAGE_GS_ARGUMENTEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Exception for throwing argument parsing error
     */
    class GS_ArgumentException : public _GS_Exception {
    public:
        GS_ArgumentException(std::string errorMessage, int line = -1, int column = -1) {
            this->errorMessage = errorMessage;
            this->line = line;
            this->column = column;
        }


    public:
        std::string getErrorMessage() {
            return this->_getErrorMessage();
        }

        void printErrorMessage() {
            this->_printErrorMessage();
        }
    };

}

#endif //GSLANGUAGE_GS_ARGUMENTEXCEPTION_H
