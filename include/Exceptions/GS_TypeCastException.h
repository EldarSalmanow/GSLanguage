#ifndef GSLANGUAGE_GS_TYPECASTEXCEPTION_H
#define GSLANGUAGE_GS_TYPECASTEXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing errors with type casting
     */
    class GS_TypeCastException : public GS_CompilingException {
    public:

        GS_TypeCastException(std::string message, int line = -1, int column = -1) {
            this->errorMessage = message;
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

#endif //GSLANGUAGE_GS_TYPECASTEXCEPTION_H
