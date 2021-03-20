#ifndef GSLANGUAGE_GS_PARSEREXCEPTION_H
#define GSLANGUAGE_GS_PARSEREXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing parsing errors
     */
    class GS_ParserException : public GS_CompilingException {
    public:

        GS_ParserException(std::string errorMessage, std::string &code, size_t line = 0, size_t column = 0) {
            this->errorMessage = errorMessage + "\nCode: " + code;
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


#endif //GSLANGUAGE_GS_PARSEREXCEPTION_H
