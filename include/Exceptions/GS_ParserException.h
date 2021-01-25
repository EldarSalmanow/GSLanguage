#ifndef GSLANGUAGE_GS_PARSEREXCEPTION_H
#define GSLANGUAGE_GS_PARSEREXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing parsing errors
     */
    class GS_ParserException : public _GS_Exception {
    public:
        GS_ParserException(std::string errorMessage, int line = -1, int column = -1) {
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


#endif //GSLANGUAGE_GS_PARSEREXCEPTION_H
