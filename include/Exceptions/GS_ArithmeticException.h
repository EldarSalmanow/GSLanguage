#ifndef GSLANGUAGE_GS_ARITHMETICEXCEPTION_H
#define GSLANGUAGE_GS_ARITHMETICEXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing math errors
     */
    class GS_ArithmeticException : public GS_CompilingException {
    public:

        GS_ArithmeticException(std::string message, int line = -1, int column = -1) {
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
