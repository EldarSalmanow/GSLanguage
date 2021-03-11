#ifndef GSLANGUAGE_GS_PARSEREXCEPTION_H
#define GSLANGUAGE_GS_PARSEREXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing parsing errors
     */
    class GS_ParserException : public GS_CompilingException {
    public:

        GS_ParserException(std::string errorMessage, std::string &code, int line = -1, int column = -1) {
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
