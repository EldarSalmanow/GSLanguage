#ifndef GSLANGUAGE_GS_VARIABLESPLACEHOLDERPASS_H
#define GSLANGUAGE_GS_VARIABLESPLACEHOLDERPASS_H

#include <AST/GS_Pass.h>

#include <Semantic/GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    class GS_VariablesPlaceholderVisitor;

    class GS_VariablesPlaceholderPass : public AST::GS_Pass {
    public:

        explicit GS_VariablesPlaceholderPass(GSTableOfSymbolsPtr tableOfSymbols);

    public:

        GSTableOfSymbolsPtr getTableOfSymbols();

    public:

        Void runForStatements(AST::GSStatementPtrArray &statements) override;

    private:

        GSTableOfSymbolsPtr _tableOfSymbols;
    };

}

#endif //GSLANGUAGE_GS_VARIABLESPLACEHOLDERPASS_H
