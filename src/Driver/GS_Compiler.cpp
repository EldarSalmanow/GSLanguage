#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSSessionContextPtrArray sessionContexts)
            : _sessionContexts(std::move(sessionContexts)) {}

    std::shared_ptr<GS_Compiler> GS_Compiler::Create(GSSessionContextPtrArray sessionContexts) {
        return std::make_shared<GS_Compiler>(std::move(sessionContexts));
    }

    std::shared_ptr<GS_Compiler> GS_Compiler::Create() {
        return GS_Compiler::Create(GSSessionContextPtrArray());
    }

    I32 GS_Compiler::Start(I32 argc, Ptr<Ptr<C>> argv) {
        auto sessionContext = GS_SessionContext::Create(argc, argv);

        if (!sessionContext) {
            return 1;
        }

        auto compiler = GS_Compiler::Create();

        compiler->AddSessionContext(sessionContext);

        return compiler->Run();
    }

    I32 GS_Compiler::Run() {
        try {
            auto sessionsManager = GS_SessionsManager::Create();

            for (auto &sessionContext : _sessionContexts) {
                auto session = GS_Session::Create(sessionContext);

                sessionsManager->AddSession(session);
            }

            auto compilingResults = sessionsManager->RunSessions();

            for (auto &compilingResult : compilingResults) {
                if (compilingResult == CompilingResult::Failure) {
                    return 1;
                }
            }
        } catch (LRef<std::exception> exception) {
            std::cout << exception.what() << std::endl;

            return 1;
        }

        return 0;
    }

    Void GS_Compiler::AddSessionContext(GSSessionContextPtr sessionContext) {
        _sessionContexts.emplace_back(std::move(sessionContext));
    }

    GSSessionContextPtrArray GS_Compiler::GetSessionContexts() const {
        return _sessionContexts;
    }

}
