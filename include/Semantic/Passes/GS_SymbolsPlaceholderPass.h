#ifndef GSLANGUAGE_GS_SYMBOLSPLACEHOLDERPASS_H
#define GSLANGUAGE_GS_SYMBOLSPLACEHOLDERPASS_H

#include <AST/GS_Pass.h>

#include <Semantic/GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    /**
     * Visitor class for adding symbols with data from nodes to table of symbols
     */
    class GS_SymbolsPlaceholderVisitor : public AST::GS_Visitor {
    public:

        /*
         *
         * GS_SymbolsPlaceholderVisitor PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Default constructor for symbols placeholder pass
         */
        GS_SymbolsPlaceholderVisitor();

    public:

        /*
         *
         * GS_SymbolsPlaceholderVisitor PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Visiting function declaration statement
         * @param session Session
         * @param functionDeclaration Function declaration
         * @return Void return
         */
        Void VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                      AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration) override;

        /**
         * Visiting variable declaration statement
         * @param session Session
         * @param variableDeclarationStatement Variable declaration statement
         * @return Void return
         */
        Void VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                               AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override;
    };

    /**
     * Pass class for run symbol placeholder visitor on nodes
     */
    class GS_SymbolsPlaceholderPass : public AST::GS_VisitPass<GS_SymbolsPlaceholderVisitor> {};

    /**
     * Creating symbols placeholder pass
     * @return Symbols placeholder pass ptr
     */
    AST::GSPassPtr CreateSymbolsPlaceholderPass();

}

#endif //GSLANGUAGE_GS_SYMBOLSPLACEHOLDERPASS_H
