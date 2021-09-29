#include <GS_Semantic.h>

#include <Parser/Nodes/GS_Node.h>

namespace GSLanguageCompiler::Semantic {

    GS_Semantic::GS_Semantic() = default;

    GSVoid GS_Semantic::run(Starter::GSContextPtr &context) {
        auto root = context->getRootNode();
        auto passes = context->getSemanticPasses();

        for (auto &pass : passes) {
            pass->setup(context);

            root->accept(pass.get());
        }
    }

}
