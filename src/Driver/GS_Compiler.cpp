#include <GS_GlobalContext.h>

#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSSessionPtrArray sessions)
            : _sessions(std::move(sessions)) {}

    std::unique_ptr<GS_Compiler> GS_Compiler::Create(GSSessionPtrArray sessions) {
        return std::make_unique<GS_Compiler>(std::move(sessions));
    }

    std::unique_ptr<GS_Compiler> GS_Compiler::Create() {
        return GS_Compiler::Create(GSSessionPtrArray());
    }

    std::unique_ptr<GS_Compiler> GS_Compiler::Create(GS_Arguments arguments) {
        auto context = GS_Context::Create(std::move(arguments));

        auto session = GS_Session::Create(std::move(context));

        GSSessionPtrArray sessions;

        sessions.emplace_back(std::move(session));

        return GS_Compiler::Create(std::move(sessions));
    }

    CompilingResult GS_Compiler::Start(I32 argc, Ptr<Ptr<C>> argv) {
        auto arguments = GS_Arguments::Create(argc, argv);

        if (!arguments) {
            return CompilingResult::Failure;
        }

        auto compiler = GS_Compiler::Create(arguments.value());

        auto result = compiler->Run();

        return result;
    }

    CompilingResult GS_Compiler::Run() {
        try {
            auto sessionsManager = GS_SessionsManager::Create(std::move(_sessions));

            auto compilingResults = sessionsManager->RunSessions();

            for (auto &compilingResult : compilingResults) {
                if (compilingResult != CompilingResult::Success) {
                    return CompilingResult::Failure;
                }
            }

            return CompilingResult::Success;
        } catch (LRef<std::exception> exception) {
            UStringStream stringStream;

            stringStream << "Internal GSLanguageCompiler error: \""_us
                         << UString(exception.what())
                         << "\"\n"_us;

            GlobalContext().Err(stringStream.String());

            return CompilingResult::Failure;
        }
    }

    ConstLRef<GS_Session> GS_Compiler::AddSession(GSSessionPtr session) {
        _sessions.emplace_back(std::move(session));

        return *_sessions[_sessions.size() - 1];
    }

    ConstLRef<GSSessionPtrArray> GS_Compiler::GetSessions() const {
        return _sessions;
    }

}
