#include <GS_Optimizer.h>

#include <AST/GS_Node.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer() = default;

    GSVoid GS_Optimizer::run(Starter::GSContextPtr &context) {
        auto root = context->getRootNode();
        auto passes = context->getOptimizerPasses();

        for (auto &pass : passes) {
            pass->setup(context);

            root = root->accept(pass.get());
        }

        context->setOptimizedRootNode(root);
    }

}