#ifndef GSLANGUAGE_GS_IEXCEPTION_H
#define GSLANGUAGE_GS_IEXCEPTION_H

#include <iostream>
#include <string>

namespace GSLanguageCompiler::Exceptions {

    /**
     * Interface for GSLanguageCompiler errors
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
