#ifndef GSLANGUAGE_GS_ERRORHANDLER_H
#define GSLANGUAGE_GS_ERRORHANDLER_H

#include <IO/GS_Error.h>

namespace GSLanguageCompiler::IO {

    class GS_ErrorHandler {
    public:

        GS_ErrorHandler() = default;

    public:

        static std::shared_ptr<GS_ErrorHandler> Create() {
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
            for (auto &error : _errors) {
                auto errorLevel = error.GetErrorLevel();

                switch (errorLevel) {
                    case ErrorLevel::Message:
                        break;
                    case ErrorLevel::Warning:
                        break;
                    case ErrorLevel::Error:
                        break;
                    case ErrorLevel::Fatal:
                        break;
                }
            }
        }

    public:

        std::vector<GS_Error> GetErrors() const {
            return _errors;
        }

    private:

        std::vector<GS_Error> _errors;
    };

    using GSErrorHandlerPtr = std::shared_ptr<GS_ErrorHandler>;

}

#endif //GSLANGUAGE_GS_ERRORHANDLER_H
