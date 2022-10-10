#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

//    GS_Optimizer::GS_Optimizer(AST::GSPassPtrArray passes, Driver::GSContextPtr context)
//            : _passes(std::move(passes)), _context(std::move(context)) {}

    GS_Optimizer::GS_Optimizer(Driver::GSContextPtr context)
            : _context(std::move(context)) {}

//    std::shared_ptr<GS_Optimizer> GS_Optimizer::Create(AST::GSPassPtrArray passes, Driver::GSContextPtr context) {
//        return std::make_shared<GS_Optimizer>(std::move(passes), std::move(context));
//    }

    std::shared_ptr<GS_Optimizer> GS_Optimizer::Create(Driver::GSContextPtr context) {
        return std::make_shared<GS_Optimizer>(std::move(context));
//        return GS_Optimizer::Create(AST::GSPassPtrArray(), std::move(context));
    }

    AST::GSNodePtr GS_Optimizer::Optimize(AST::GSNodePtr node, AST::GSPassPtrArray passes) {
        auto optimizedNode = std::move(node);

        auto passManager = AST::GS_PassManager::Create();

        for (auto &pass : passes) {
            passManager->AddPass(pass);
        }

        passManager->Run(node, _context);

        return node;
    }

//    Void GS_Optimizer::AddPass(AST::GSPassPtr pass) {
//        _passes.emplace_back(std::move(pass));
//    }

}