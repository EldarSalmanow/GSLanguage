#include <GS_SemanticAnalyzer.h>

namespace GSLanguageCompiler::Semantic {

    GS_SemanticAnalyzer::GS_SemanticAnalyzer(LRef<Driver::GS_Session> session, AST::GSPassPtrArray semanticPasses)
            : _session(session),
              _semanticPasses(std::move(semanticPasses)) {}

    std::unique_ptr<GS_SemanticAnalyzer> GS_SemanticAnalyzer::Create(LRef<Driver::GS_Session> session,
                                                                     AST::GSPassPtrArray semanticPasses) {
        return std::make_unique<GS_SemanticAnalyzer>(session,
                                                     std::move(semanticPasses));
    }

    std::unique_ptr<GS_SemanticAnalyzer> GS_SemanticAnalyzer::Create(LRef<Driver::GS_Session> session) {
        AST::GSPassPtrArray semanticPasses = {
                CreateSymbolsPlaceholderPass()
        };

        return GS_SemanticAnalyzer::Create(session,
                                           semanticPasses);
    }

    Void GS_SemanticAnalyzer::Analyze(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        auto passManager = AST::GS_PassManager::Create(std::move(_semanticPasses));

        passManager->Run(_session,
                         translationUnitDeclaration);
    }

    Void GS_SemanticAnalyzer::Analyze(AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto passManager = AST::GS_PassManager::Create(std::move(_semanticPasses));

        passManager->Run(_session,
                         functionDeclaration);
    }

}
