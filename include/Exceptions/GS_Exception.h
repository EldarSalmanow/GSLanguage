#ifndef GSLANGUAGE_GS_EXCEPTION_H
#define GSLANGUAGE_GS_EXCEPTION_H

#include "../Compiler/Util/GS_CrossPlatform.h"

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
            return this->errorMessage;
        }

        /**
         * Function to output the error message to the error stream
         */
        void _printErrorMessage() override {
            Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::RED);

            std::cerr << this->errorMessage << std::endl;
            
            Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::WHITE);
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
            out << exception.errorMessage;

            return out;
        }

    public:

        /**
         * Error message
         */
        std::string errorMessage;
    };

}

#endif //GSLANGUAGE_GS_EXCEPTION_H
