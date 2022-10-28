#ifndef GSLANGUAGE_GS_SYMBOLSPLACEHOLDERPASS_H
#define GSLANGUAGE_GS_SYMBOLSPLACEHOLDERPASS_H

#include <AST/GS_Pass.h>

#include <Semantic/GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    /**
     * Adding function symbol with function declaration data to table of symbols
     * @param functionDeclaration Function declaration
     * @param tableOfSymbols Table of symbols
     * @return
     */
    Void AddFunction(LRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration, LRef<GSTableOfSymbolsPtr> tableOfSymbols);

    /**
     * Adding variable symbol with variable declaration statement data to table of symbols
     * @param variableDeclarationStatement Variable declaration statement
     * @param tableOfSymbols Table of symbols
     * @return
     */
    Void AddVariable(LRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement, LRef<GSTableOfSymbolsPtr> tableOfSymbols);

    /**
     * Visitor class for adding symbols with data from nodes to table of symbols
     */
    class GS_SymbolsPlaceholderVisitor : public AST::GS_Visitor {
    public:

        /**
         * Visiting function declaration statement
         * @param functionDeclaration Function declaration
         * @param context Context
         * @return
         */
        Void VisitFunctionDeclaration(LRef<AST::NodePtr<AST::GS_FunctionDeclaration>> functionDeclaration,
                                      LRef<Driver::GSContextPtr> context) override;

        /**
         * Visiting variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @param context Context
         * @return
         */
        Void VisitVariableDeclarationStatement(LRef<AST::NodePtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement,
                                               LRef<Driver::GSContextPtr> context) override;
    };

    /**
     * Pass class for run symbol placeholder visitor on nodes
     */
    class GS_SymbolsPlaceholderPass : public AST::GS_VisitPass<GS_SymbolsPlaceholderVisitor> {};

    /**
     * Creating symbols placeholder pass
     * @return Symbols placeholder pass
     */
    AST::GSPassPtr CreateSymbolsPlaceholderPass();

}

#endif //GSLANGUAGE_GS_SYMBOLSPLACEHOLDERPASS_H
