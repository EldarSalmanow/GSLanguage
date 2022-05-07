#ifndef GSLANGUAGE_GS_ERROR_H
#define GSLANGUAGE_GS_ERROR_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    enum class ErrorLevel {
        Message,
        Warning,
        Error,
        Fatal
    };

    class GS_Error {
    public:

        GS_Error(UString message, ErrorLevel level)
                : _message(std::move(message)), _errorLevel(level) {}

    public:

        static GS_Error Create(UString message, ErrorLevel level) {
            return GS_Error(std::move(message), level);
        }

    public:

        UString GetMessage() const {
            return _message;
        }

        ErrorLevel GetErrorLevel() const {
            return _errorLevel;
        }

    private:

        UString _message;

        ErrorLevel _errorLevel;
    };

}

#endif //GSLANGUAGE_GS_ERROR_H
