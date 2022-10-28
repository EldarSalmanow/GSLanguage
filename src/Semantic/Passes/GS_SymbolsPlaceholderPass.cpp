#include <Semantic/Passes/GS_SymbolsPlaceholderPass.h>

namespace GSLanguageCompiler::Semantic {

    Void AddFunction(LRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration, LRef<GSTableOfSymbolsPtr> tableOfSymbols) {
        tableOfSymbols->AddFunction(functionDeclaration->GetName(), functionDeclaration->GetSignature());
    }

    Void AddVariable(LRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement, LRef<GSTableOfSymbolsPtr> tableOfSymbols) {
        tableOfSymbols->AddVariable(variableDeclarationStatement->GetName(), variableDeclarationStatement->GetType());
    }

    Void GS_SymbolsPlaceholderVisitor::VisitFunctionDeclaration(LRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration,
                                                                LRef<Driver::GSContextPtr> context) {
        GS_Visitor::VisitFunctionDeclaration(functionDeclaration, context);

        // TODO: add getting table of symbols from session context

        auto tableOfSymbols = GS_TableOfSymbols::Create();

        AddFunction(functionDeclaration, tableOfSymbols);
    }

    Void GS_SymbolsPlaceholderVisitor::VisitVariableDeclarationStatement(LRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement,
                                                                         LRef<Driver::GSContextPtr> context) {
        GS_Visitor::VisitVariableDeclarationStatement(variableDeclarationStatement, context);

        auto tableOfSymbols = GS_TableOfSymbols::Create();

        AddVariable(variableDeclarationStatement, tableOfSymbols);
    }

}
