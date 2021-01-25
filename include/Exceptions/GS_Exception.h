#ifndef GSLANGUAGE_GS_EXCEPTION_H
#define GSLANGUAGE_GS_EXCEPTION_H

#include "GS_IException.h"

namespace GSLanguageCompiler::Exceptions {
    /**
     * Base error class for GS_LanguageCompiler<br>
     * Note: Do not create objects of this class!
     */
    class _GS_Exception : public GS_IException {
    public:
        /**
         * Function for receiving an error message
         * @return Error message
         */
        std::string _getErrorMessage() override {
            return this->errorMessage + "\nLine: " + std::to_string(this->line) + "\nColumn: " + std::to_string(this->column);
        }

        /**
         * Function to output the error message to the error stream
         */
        void _printErrorMessage() override {
            std::cerr << this->errorMessage << "\nLine: " << this->line << "\nColumn: " << this->column << std::endl;
        }

    public:
        /**
         * Overloading the output operator to display an error message for inherited classes
         * @param out Output stream
         * @param exception Base error class GS_LanguageCompiler<br>
         * Note: All inherited classes can accept _GS_Exception
         * @return Output stream
         */
        friend std::ostream &operator<<(std::ostream &out, const _GS_Exception &exception) {
            out << exception.errorMessage << "\nLine: " << exception.line << "\nColumn: " << exception.column;
            return out;
        }

    public:
        /**
         * Error message
         */
        std::string errorMessage;

        /**
         * The position in the file that threw the error
         */
        int line, column;
    };
}

#endif //GSLANGUAGE_GS_EXCEPTION_H
