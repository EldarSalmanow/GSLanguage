#ifndef GSLANGUAGE_GS_TYPEINFERENCEPASS_H
#define GSLANGUAGE_GS_TYPEINFERENCEPASS_H

#include <AST/GS_Pass.h>

namespace GSLanguageCompiler::Semantic {

    class GS_TypeInferenceVisitor : public AST::GS_Visitor {
    public:

        GS_TypeInferenceVisitor();

    public:

        Void VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                      AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) override;

        Void VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                               AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override;
    };

    class GS_TypeInferencePass : public AST::GS_VisitPass<GS_TypeInferenceVisitor> {};

    AST::GSPassPtr CreateTypeInferencePass();

}

#endif //GSLANGUAGE_GS_TYPEINFERENCEPASS_H
