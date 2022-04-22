#include <GS_Pass.h>

namespace GSLanguageCompiler::AST {

    GS_Pass::~GS_Pass() = default;

    Void GS_Pass::Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {

    }

    Void GS_Pass::Run(LRef<GSNodePtrArray> nodes) {

    }

    Void GS_Pass::Run(LRef<GSDeclarationPtrArray> declarations) {

    }

    Void GS_Pass::Run(LRef<GSStatementPtrArray> statements) {

    }

    Void GS_Pass::Run(LRef<GSExpressionPtrArray> expressions) {

    }

    GS_PassManager::GS_PassManager(GSPassPtrArray passes)
            : _passes(std::move(passes)) {}

    SharedPtr<GS_PassManager> GS_PassManager::Create(GSPassPtrArray passes) {
        return std::make_shared<GS_PassManager>(std::move(passes));
    }

    SharedPtr<GS_PassManager> GS_PassManager::Create() {
        return GS_PassManager::Create(GSPassPtrArray());
    }

    Void GS_PassManager::Run(LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        for (auto &pass: _passes) {
            pass->Run(translationUnitDeclaration);
        }
    }

    Void GS_PassManager::Run(LRef<GSNodePtrArray> nodes) {
        for (auto &pass: _passes) {
            pass->Run(nodes);
        }
    }

    Void GS_PassManager::Run(LRef<GSDeclarationPtrArray> declarations) {
        for (auto &pass: _passes) {
            pass->Run(declarations);
        }
    }

    Void GS_PassManager::Run(LRef<GSStatementPtrArray> statements) {
        for (auto &pass: _passes) {
            pass->Run(statements);
        }
    }

    Void GS_PassManager::Run(LRef<GSExpressionPtrArray> expressions) {
        for (auto &pass: _passes) {
            pass->Run(expressions);
        }
    }

    Void GS_PassManager::AddPass(GSPassPtr pass) {
        _passes.emplace_back(std::move(pass));
    }

    GSPassPtrArray GS_PassManager::GetPasses() const {
        return _passes;
    }

}
