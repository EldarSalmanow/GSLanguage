#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSCompilerSessionConfigPtrArray sessionConfigs)
            : _sessionConfigs(std::move(sessionConfigs)) {}

    SharedPtr<GS_Compiler> GS_Compiler::Create(GSCompilerSessionConfigPtrArray sessionConfigs) {
        return std::make_shared<GS_Compiler>(std::move(sessionConfigs));
    }

    SharedPtr<GS_Compiler> GS_Compiler::Create() {
        return GS_Compiler::Create(GSCompilerSessionConfigPtrArray());
    }

    I32 GS_Compiler::Start(I32 argc, Ptr<Ptr<C8>> argv) {
        auto sessionConfig = GS_CompilerSessionConfig::Create(argc, argv);

        if (!sessionConfig) {
            return 1;
        }

        auto compiler = GS_Compiler::Create();

        compiler->AddSessionConfig(sessionConfig);

        return compiler->Run();
    }

    I32 GS_Compiler::Run() {
        GSCompilerSessionPtrArray sessions;

        for (auto &sessionConfig : _sessionConfigs) {
            auto session = GS_CompilerSession::Create(sessionConfig);

            sessions.emplace_back(session);
        }

        for (auto &session : sessions) {
            auto sessionResult = session->Run();

            if (sessionResult == CompilingResult::Failure) {
                return 1;
            }
        }

        return 0;
    }

    Void GS_Compiler::AddSessionConfig(GSCompilerSessionConfigPtr sessionConfig) {
        _sessionConfigs.emplace_back(std::move(sessionConfig));
    }

    GSCompilerSessionConfigPtrArray GS_Compiler::GetSessionConfigs() const {
        return _sessionConfigs;
    }

}