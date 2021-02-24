#ifndef GSLANGUAGE_GS_ARITHMETICEXCEPTION_H
#define GSLANGUAGE_GS_ARITHMETICEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Exception for throwing arithmetic error
     */
    class GS_ArithmeticException : public _GS_Exception {
    public:

        GS_ArithmeticException(std::string  errorMessage, int line = -1, int column = -1) {
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

#endif //GSLANGUAGE_GS_ARITHMETICEXCEPTION_H
