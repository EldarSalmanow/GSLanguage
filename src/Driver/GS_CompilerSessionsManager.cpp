#include <GS_CompilerSessionsManager.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSessionsManager::GS_CompilerSessionsManager(GSCompilerSessionPtrArray sessions)
            : _sessions(std::move(sessions)) {}

    SharedPtr<GS_CompilerSessionsManager> GS_CompilerSessionsManager::Create(GSCompilerSessionPtrArray sessions) {
        return std::make_shared<GS_CompilerSessionsManager>(std::move(sessions));
    }

    SharedPtr<GS_CompilerSessionsManager> GS_CompilerSessionsManager::Create() {
        return GS_CompilerSessionsManager::Create(GSCompilerSessionPtrArray());
    }

    Vector<CompilingResult> GS_CompilerSessionsManager::RunSessions() {
        Vector<CompilingResult> compilingResults;

        for (auto &session : _sessions) {
            auto result = session->Run();

            compilingResults.emplace_back(result);
        }

        return compilingResults;
    }

    Void GS_CompilerSessionsManager::AddSession(GSCompilerSessionPtr session) {
        _sessions.emplace_back(std::move(session));
    }

    GSCompilerSessionPtrArray GS_CompilerSessionsManager::GetSessions() const {
        return _sessions;
    }

}
