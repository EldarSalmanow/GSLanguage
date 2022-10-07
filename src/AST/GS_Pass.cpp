#include <GS_Pass.h>

namespace GSLanguageCompiler::AST {

    GS_Pass::~GS_Pass() = default;

    Void GS_Pass::Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Pass::Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Pass::Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Pass::Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context) {

    }

    Void GS_Pass::Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context) {

    }

    GS_PassManager::GS_PassManager(GSPassPtrArray passes)
            : _passes(std::move(passes)) {}

    std::shared_ptr<GS_PassManager> GS_PassManager::Create(GSPassPtrArray passes) {
        return std::make_shared<GS_PassManager>(std::move(passes));
    }

    std::shared_ptr<GS_PassManager> GS_PassManager::Create() {
        return GS_PassManager::Create(GSPassPtrArray());
    }

    Void GS_PassManager::Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration, LRef<Driver::GSContextPtr> context) {
        for (auto &pass : _passes) {
            pass->Run(translationUnitDeclaration, context);
        }
    }

    Void GS_PassManager::Run(LRef<GSNodePtrArray> nodes, LRef<Driver::GSContextPtr> context) {
        for (auto &pass : _passes) {
            pass->Run(nodes, context);
        }
    }

    Void GS_PassManager::Run(LRef<GSDeclarationPtrArray> declarations, LRef<Driver::GSContextPtr> context) {
        for (auto &pass : _passes) {
            pass->Run(declarations, context);
        }
    }

    Void GS_PassManager::Run(LRef<GSStatementPtrArray> statements, LRef<Driver::GSContextPtr> context) {
        for (auto &pass : _passes) {
            pass->Run(statements, context);
        }
    }

    Void GS_PassManager::Run(LRef<GSExpressionPtrArray> expressions, LRef<Driver::GSContextPtr> context) {
        for (auto &pass : _passes) {
            pass->Run(expressions, context);
        }
    }

    Void GS_PassManager::AddPass(GSPassPtr pass) {
        _passes.emplace_back(std::move(pass));
    }

    GSPassPtrArray GS_PassManager::GetPasses() const {
        return _passes;
    }

}
