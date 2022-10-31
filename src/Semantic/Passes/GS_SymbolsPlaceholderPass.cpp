#include <Driver/GS_Session.h>

#include <Semantic/Passes/GS_SymbolsPlaceholderPass.h>

namespace GSLanguageCompiler::Semantic {

    Void AddFunction(ConstLRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration, LRef<GSTableOfSymbolsPtr> tableOfSymbols) {
        tableOfSymbols->AddFunction(functionDeclaration->GetName(), functionDeclaration->GetSignature());
    }

    Void AddVariable(ConstLRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement, LRef<GSTableOfSymbolsPtr> tableOfSymbols) {
        tableOfSymbols->AddVariable(variableDeclarationStatement->GetName(), variableDeclarationStatement->GetType());
    }

    Void GS_SymbolsPlaceholderVisitor::VisitFunctionDeclaration(LRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration,
                                                                LRef<Driver::GS_Session> session) {
        GS_Visitor::VisitFunctionDeclaration(functionDeclaration, session);

        auto tableOfSymbols = session.GetTableOfSymbols();

        AddFunction(functionDeclaration, tableOfSymbols);
    }

    Void GS_SymbolsPlaceholderVisitor::VisitVariableDeclarationStatement(LRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement,
                                                                         LRef<Driver::GS_Session> session) {
        GS_Visitor::VisitVariableDeclarationStatement(variableDeclarationStatement, session);

        auto tableOfSymbols = session.GetTableOfSymbols();

        AddVariable(variableDeclarationStatement, tableOfSymbols);
    }

    AST::GSPassPtr CreateSymbolsPlaceholderPass() {
        return std::make_shared<GS_SymbolsPlaceholderPass>();
    }

}
