#ifndef GSLANGUAGE_GS_COMPILINGEXCEPTION_H
#define GSLANGUAGE_GS_COMPILINGEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     *
     */
    class GS_CompilingException : public _GS_Exception {
    public:

        /**
         *
         * @return
         */
        std::string _getErrorMessage() {
            return this->errorMessage + "\nLine: " + std::to_string(this->line) + "\nColumn: " + std::to_string(this->column);
        }

        /**
         *
         */
        void _printErrorMessage() {
            std::cerr << this->errorMessage << "\nLine: " << this->line << "\nColumn: " << this->column << std::endl;
        }
    public:

        /**
         *
         * @param out
         * @param exception
         * @return
         */
        friend std::ostream &operator<<(std::ostream &out, const GS_CompilingException &exception) {
            out
            << exception.errorMessage
            << "\nLine: "
            << exception.line
            << "\nColumn: "
            << exception.column;
            return out;
        }

    public:

        /**
         * The position in the file that threw the error
         */
        int line, column;
    };

}

#endif //GSLANGUAGE_GS_COMPILINGEXCEPTION_H
