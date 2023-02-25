#include <GS_Pass.h>

namespace GSLanguageCompiler::AST {

    GS_Pass::~GS_Pass() = default;

    Void GS_Pass::Run(LRef<Driver::GS_Session> session,
                      LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {

    }

    Void GS_Pass::Run(LRef<Driver::GS_Session> session,
                      LRef<GSNodePtr> node) {

    }

    Void GS_Pass::Run(LRef<Driver::GS_Session> session,
                      LRef<GSNodePtrArray> nodes) {

    }

    Void GS_Pass::Run(LRef<Driver::GS_Session> session,
                      LRef<GSDeclarationPtrArray> declarations) {

    }

    Void GS_Pass::Run(LRef<Driver::GS_Session> session,
                      LRef<GSStatementPtrArray> statements) {

    }

    Void GS_Pass::Run(LRef<Driver::GS_Session> session,
                      LRef<GSExpressionPtrArray> expressions) {

    }

    GS_PassManager::GS_PassManager(GSPassPtrArray passes)
            : _passes(std::move(passes)) {}

    std::unique_ptr<GS_PassManager> GS_PassManager::Create(GSPassPtrArray passes) {
        return std::make_unique<GS_PassManager>(std::move(passes));
    }

    std::unique_ptr<GS_PassManager> GS_PassManager::Create() {
        return GS_PassManager::Create(GSPassPtrArray());
    }

    Void GS_PassManager::Run(LRef<Driver::GS_Session> session,
                             LRef<GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        for (auto &pass : _passes) {
            pass->Run(session,
                      translationUnitDeclaration);
        }
    }

    Void GS_PassManager::Run(LRef<Driver::GS_Session> session,
                             LRef<GSNodePtr> node) {
        for (auto &pass : _passes) {
            pass->Run(session,
                      node);
        }
    }

    Void GS_PassManager::Run(LRef<Driver::GS_Session> session,
                             LRef<GSNodePtrArray> nodes) {
        for (auto &pass : _passes) {
            pass->Run(session,
                      nodes);
        }
    }

    Void GS_PassManager::Run(LRef<Driver::GS_Session> session,
                             LRef<GSDeclarationPtrArray> declarations) {
        for (auto &pass : _passes) {
            pass->Run(session,
                      declarations);
        }
    }

    Void GS_PassManager::Run(LRef<Driver::GS_Session> session,
                             LRef<GSStatementPtrArray> statements) {
        for (auto &pass : _passes) {
            pass->Run(session,
                      statements);
        }
    }

    Void GS_PassManager::Run(LRef<Driver::GS_Session> session,
                             LRef<GSExpressionPtrArray> expressions) {
        for (auto &pass : _passes) {
            pass->Run(session,
                      expressions);
        }
    }

    ConstLRef<GS_Pass> GS_PassManager::AddPass(GSPassPtr pass) {
        _passes.emplace_back(std::move(pass));

        return *_passes[_passes.size() - 1];
    }

    ConstLRef<GSPassPtrArray> GS_PassManager::GetPasses() const {
        return _passes;
    }

}
