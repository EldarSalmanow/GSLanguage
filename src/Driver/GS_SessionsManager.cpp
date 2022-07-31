#include <GS_SessionsManager.h>

namespace GSLanguageCompiler::Driver {

    GS_SessionsManager::GS_SessionsManager(GSSessionPtrArray sessions)
            : _sessions(std::move(sessions)) {}

    std::shared_ptr<GS_SessionsManager> GS_SessionsManager::Create(GSSessionPtrArray sessions) {
        return std::make_shared<GS_SessionsManager>(std::move(sessions));
    }

    std::shared_ptr<GS_SessionsManager> GS_SessionsManager::Create() {
        return GS_SessionsManager::Create(GSSessionPtrArray());
    }

    std::vector<CompilingResult> GS_SessionsManager::RunSessions() {
        std::vector<CompilingResult> compilingResults;

        for (auto &session : _sessions) {
            auto result = session->Run();

            compilingResults.emplace_back(result);
        }

        return compilingResults;
    }

    Void GS_SessionsManager::AddSession(GSSessionPtr session) {
        _sessions.emplace_back(std::move(session));
    }

    GSSessionPtrArray GS_SessionsManager::GetSessions() const {
        return _sessions;
    }

}
