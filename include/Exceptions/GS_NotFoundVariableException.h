#ifndef GSLANGUAGE_GS_NOTFOUNDVARIABLEEXCEPTION_H
#define GSLANGUAGE_GS_NOTFOUNDVARIABLEEXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     *
     */
    class GS_NotFoundVariableException : public GS_CompilingException {
    public:

        GS_NotFoundVariableException(std::string errorMessage, size_t line = 0, size_t column = 0) {
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

#endif //GSLANGUAGE_GS_NOTFOUNDVARIABLEEXCEPTION_H
