#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer(LRef<Driver::GS_Session> session)
            : _session(session) {}

    std::shared_ptr<GS_Optimizer> GS_Optimizer::Create(LRef<Driver::GS_Session> session) {
        return std::make_shared<GS_Optimizer>(session);
    }

    Void GS_Optimizer::Optimize(LRef<AST::GSNodePtr> node, AST::GSPassPtrArray passes) {
        auto passManager = AST::GS_PassManager::Create(std::move(passes));

        passManager->Run(_session,
                         node);
    }

}