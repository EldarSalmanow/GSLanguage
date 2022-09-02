#include <GS_Compiler.h>

namespace GSLanguageCompiler::Driver {

    GS_Compiler::GS_Compiler(GSLanguageCompiler::Driver::GSSessionPtrArray sessions)
            : _sessions(std::move(sessions)) {}

    std::shared_ptr<GS_Compiler> GS_Compiler::Create(GSSessionPtrArray sessions) {
        return std::make_shared<GS_Compiler>(std::move(sessions));
    }

    std::shared_ptr<GS_Compiler> GS_Compiler::Create() {
        return GS_Compiler::Create(GSSessionPtrArray());
    }

    std::shared_ptr<GS_Compiler> GS_Compiler::Create(GS_Arguments arguments) {
        auto context = GS_Context::Create(std::move(arguments));

        auto session = GS_Session::Create(context);

        return GS_Compiler::Create({session});
    }

    CompilingResult GS_Compiler::Start(I32 argc, Ptr<Ptr<C>> argv) {
        auto arguments = GS_Arguments::Create(argc, argv);

        if (!arguments) {
            // TODO success or failure ?

            return CompilingResult::Success;
        }

        auto compiler = GS_Compiler::Create(arguments.value());

        auto result = compiler->Run();

        return result;
    }

    CompilingResult GS_Compiler::Run() {
        // TODO ?

        auto result = CompilingResult::Success;

        for (auto &session : _sessions) {
            if (session->Run() != CompilingResult::Success) {
                result = CompilingResult::Failure;
            }
        }

        return result;
    }

    Void GS_Compiler::AddSession(GSSessionPtr session) {
        _sessions.emplace_back(std::move(session));
    }

    GSSessionPtrArray GS_Compiler::GetSessions() const {
        return _sessions;
    }

}
