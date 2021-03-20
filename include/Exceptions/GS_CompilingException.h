#ifndef GSLANGUAGE_GS_COMPILINGEXCEPTION_H
#define GSLANGUAGE_GS_COMPILINGEXCEPTION_H

#include "GS_Exception.h"

namespace GSLanguageCompiler::Exceptions {

    /**
     * Base class for compilation errors
     */
    class GS_CompilingException : public _GS_Exception {
    public:

        std::string _getErrorMessage() {
            return this->errorMessage + "\nLine: " + std::to_string(this->line) + "\nColumn: " + std::to_string(this->column);
        }

        void _printErrorMessage() {
            Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::RED);

            std::cerr << this->errorMessage << "\nLine: " << this->line << "\nColumn: " << this->column << std::endl;

            Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::LIGHT_GRAY);
        }

    public:

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

        size_t line = 0, column = 0;
    };

}

#endif //GSLANGUAGE_GS_COMPILINGEXCEPTION_H
