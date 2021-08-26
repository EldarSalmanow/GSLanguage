#ifndef GSLANGUAGE_GS_ERRORHANDLER_H
#define GSLANGUAGE_GS_ERRORHANDLER_H

#include <map>

#include <Lexer/GS_Position.h>

#include <Exceptions/GS_Exception.h>

namespace GSLanguageCompiler::Exceptions {

    /**
     *
     */
    enum class ErrorLevel {
        NOTE_LVL,
        WARNING_LVL,
        ERROR_LVL,
        FATAL_LVL
    };

    /**
     *
     */
    class GS_ErrorHandler {
    public:

        /**
         *
         */
        GS_ErrorHandler();

    public:

        /**
         *
         * @param errorLevel
         * @param position
         * @param message
         * @return
         */
        GSVoid print(ErrorLevel errorLevel, Lexer::GS_Position position, GSString message);

        /**
         *
         * @param errorLevel
         * @param message
         * @return
         */
        GSVoid print(ErrorLevel errorLevel, GSString message);

        /**
         *
         * @return
         */
        GSVoid throw_();
    };

    extern GS_ErrorHandler errorHandler;

}

#endif //GSLANGUAGE_GS_ERRORHANDLER_H
