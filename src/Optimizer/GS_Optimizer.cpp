#include <GS_Optimizer.h>

namespace GSLanguageCompiler::Optimizer {

    GS_Optimizer::GS_Optimizer(AST::GSPassPtrArray passes)
            : _passes(std::move(passes)) {}

    std::shared_ptr<GS_Optimizer> GS_Optimizer::Create(AST::GSPassPtrArray passes) {
        return std::make_shared<GS_Optimizer>(std::move(passes));
    }

    std::shared_ptr<GS_Optimizer> GS_Optimizer::Create() {
        AST::GSPassPtrArray passes;

        passes.emplace_back(CreateConstantFoldingPass());

        return GS_Optimizer::Create(passes);
    }

    Void GS_Optimizer::Optimize(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        auto passManager = AST::GS_PassManager::Create();

        for (auto &pass : _passes) {
            passManager->AddPass(pass);
        }

        passManager->Run(translationUnitDeclaration);
    }

}