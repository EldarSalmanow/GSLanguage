#ifndef GSLANGUAGE_GS_IEXCEPTION_H
#define GSLANGUAGE_GS_IEXCEPTION_H

#include <iostream>

namespace GSLanguageCompiler::Exceptions {

    /**
     * Interface for GS_LanguageCompiler errors
     */
    class GS_IException {
    public:

        /**
         * Getting an error message
         * @return Error message
         */
        virtual std::string _getErrorMessage() = 0;

        /**
         * Error message output
         */
        virtual void _printErrorMessage() = 0;
    };

}

#endif //GSLANGUAGE_GS_IEXCEPTION_H
