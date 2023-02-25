#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer(LRef<Driver::GS_Session> session,
                               AST::GSPassPtrArray optimizingPasses)
            : _session(session),
              _optimizingPasses(std::move(optimizingPasses)) {}

    std::unique_ptr<GS_Optimizer> GS_Optimizer::Create(LRef<Driver::GS_Session> session,
                                                       AST::GSPassPtrArray optimizingPasses) {
        return std::make_unique<GS_Optimizer>(session,
                                              std::move(optimizingPasses));
    }

    std::unique_ptr<GS_Optimizer> GS_Optimizer::Create(LRef<Driver::GS_Session> session) {
        AST::GSPassPtrArray optimizingPasses = {
                CreateConstantFoldingPass()
        };

        return std::make_unique<GS_Optimizer>(session,
                                              optimizingPasses);
    }

    Void GS_Optimizer::Optimize(LRef<AST::GSNodePtr> node) {
        auto passManager = AST::GS_PassManager::Create(std::move(_optimizingPasses));

        passManager->Run(_session,
                         node);
    }

}