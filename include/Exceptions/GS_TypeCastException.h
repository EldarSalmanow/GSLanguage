#ifndef GSLANGUAGE_GS_TYPECASTEXCEPTION_H
#define GSLANGUAGE_GS_TYPECASTEXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing errors with type casting
     */
    class GS_TypeCastException : public GS_CompilingException {
    public:

        GS_TypeCastException(std::string message, size_t line = 0, size_t column = 0) {
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
