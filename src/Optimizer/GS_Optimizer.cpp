#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer(Driver::GSContextPtr context)
            : _context(std::move(context)) {}

    std::shared_ptr<GS_Optimizer> GS_Optimizer::Create(Driver::GSContextPtr context) {
        return std::make_shared<GS_Optimizer>(std::move(context));
    }

    Void GS_Optimizer::Optimize(LRef<AST::GSNodePtr> node, AST::GSPassPtrArray passes) {
        auto passManager = AST::GS_PassManager::Create(std::move(passes));

        passManager->Run(node, _context);
    }

}