#include <GS_GlobalContext.h>

#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSSessionsManagerPtr sessionsManager)
            : _sessionsManager(std::move(sessionsManager)) {}

    std::unique_ptr<GS_Compiler> GS_Compiler::Create(GSSessionsManagerPtr sessionsManager) {
        return std::make_unique<GS_Compiler>(std::move(sessionsManager));
    }

    std::unique_ptr<GS_Compiler> GS_Compiler::Create() {
        return GS_Compiler::Create(GS_SessionsManager::Create());
    }

    std::unique_ptr<GS_Compiler> GS_Compiler::Create(GS_Arguments arguments) {
        auto session = GS_Session::Create(std::move(arguments));

        auto sessionsManager = GS_SessionsManager::Create();

        sessionsManager->AddSession(std::move(session));

        return GS_Compiler::Create(std::move(sessionsManager));
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
            auto compilingResults = _sessionsManager->RunSessions();

            for (auto &compilingResult : compilingResults) {
                if (compilingResult != CompilingResult::Success) {
                    return CompilingResult::Failure;
                }
            }

            return CompilingResult::Success;
        } catch (LRef<std::exception> exception) {
            UStringStream stringStream;

            stringStream << "Internal GSLanguageCompiler error: "_us
                         << UString(exception.what())
                         << "\n"_us;

            GlobalContext().Err() << stringStream.String();

            return CompilingResult::Failure;
        }
    }

    ConstLRef<GS_Session> GS_Compiler::AddSession(GSSessionPtr session) {
        return _sessionsManager->AddSession(std::move(session));
    }

    ConstLRef<GSSessionPtrArray> GS_Compiler::GetSessions() const {
        return _sessionsManager->GetSessions();
    }

    ConstLRef<GS_SessionsManager> GS_Compiler::GetSessionsManager() const {
        return *_sessionsManager;
    }

}
