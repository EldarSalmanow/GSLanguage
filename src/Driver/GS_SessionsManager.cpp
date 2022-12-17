#include <GS_SessionsManager.h>

namespace GSLanguageCompiler::Driver {

    GS_SessionsManager::GS_SessionsManager(GSSessionPtrArray sessions)
            : _sessions(std::move(sessions)) {}

    std::unique_ptr<GS_SessionsManager> GS_SessionsManager::Create(GSSessionPtrArray sessions) {
        return std::make_unique<GS_SessionsManager>(std::move(sessions));
    }

    std::unique_ptr<GS_SessionsManager> GS_SessionsManager::Create() {
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

    ConstLRef<GS_Session> GS_SessionsManager::AddSession(GSSessionPtr session) {
        _sessions.emplace_back(std::move(session));

        return *_sessions[_sessions.size() - 1];
    }

    ConstLRef<GSSessionPtrArray> GS_SessionsManager::GetSessions() const {
        return _sessions;
    }

}
