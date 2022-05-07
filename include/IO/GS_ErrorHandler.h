#ifndef GSLANGUAGE_GS_ERRORHANDLER_H
#define GSLANGUAGE_GS_ERRORHANDLER_H

#include <IO/GS_Error.h>

namespace GSLanguageCompiler::IO {

    class GS_ErrorHandler {
    public:

        GS_ErrorHandler() = default;

    public:

        static SharedPtr<GS_ErrorHandler> Create() {
            return std::make_shared<GS_ErrorHandler>();
        }

    public:

        Void AddError(UString message, ErrorLevel level) {
            _errors.emplace_back(GS_Error::Create(std::move(message), level));
        }

        Void AddMessage(UString message) {
            AddError(std::move(message), ErrorLevel::Message);
        }

        Void AddWarning(UString message) {
            AddError(std::move(message), ErrorLevel::Warning);
        }

        Void AddError(UString message) {
            AddError(std::move(message), ErrorLevel::Error);
        }

        Void AddFatal(UString message) {
            AddError(std::move(message), ErrorLevel::Fatal);
        }

    public:

        Void PrintErrors() {

        }

    public:

        Vector<GS_Error> GetErrors() const {
            return _errors;
        }

    private:

        Vector<GS_Error> _errors;
    };

    using GSErrorHandlerPtr = SharedPtr<GS_ErrorHandler>;

}

#endif //GSLANGUAGE_GS_ERRORHANDLER_H
