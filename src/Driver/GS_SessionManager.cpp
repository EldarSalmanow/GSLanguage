#include <GS_SessionManager.h>

namespace GSLanguageCompiler::Driver {

    GS_SessionManager::GS_SessionManager(GSSessionPtrArray sessions)
            : _sessions(std::move(sessions)) {}

    std::unique_ptr<GS_SessionManager> GS_SessionManager::Create(GSSessionPtrArray sessions) {
        return std::make_unique<GS_SessionManager>(std::move(sessions));
    }

    std::unique_ptr<GS_SessionManager> GS_SessionManager::Create() {
        return GS_SessionManager::Create(GSSessionPtrArray());
    }

    std::vector<CompilingResult> GS_SessionManager::RunSessions() {
        std::vector<CompilingResult> compilingResults;

        for (auto &session : _sessions) {
            auto result = session->Run();

            compilingResults.emplace_back(result);
        }

        return compilingResults;
    }

    ConstLRef<GS_Session> GS_SessionManager::AddSession(GSSessionPtr session) {
        _sessions.emplace_back(std::move(session));

        return *_sessions[_sessions.size() - 1];
    }

    ConstLRef<GSSessionPtrArray> GS_SessionManager::GetSessions() const {
        return _sessions;
    }

}
