#ifndef GSLANGUAGE_GS_LEXEREXCEPTION_H
#define GSLANGUAGE_GS_LEXEREXCEPTION_H

#include "GS_CompilingException.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Class for throwing lexical parsing errors
     */
    class GS_LexerException : public GS_CompilingException {
    public:

        GS_LexerException(std::string errorMessage, int line = -1, int column = -1) {
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

#endif //GSLANGUAGE_GS_LEXEREXCEPTION_H
