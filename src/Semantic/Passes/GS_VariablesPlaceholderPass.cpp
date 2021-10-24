#include <Passes/GS_VariablesPlaceholderPass.h>

#include <Visitors/GS_VariablesPlaceholderVisitor.h>

namespace GSLanguageCompiler::Semantic {

    GS_VariablesPlaceholderPass::GS_VariablesPlaceholderPass(GSTableOfSymbolsPtr tableOfSymbols)
            : AST::GS_Pass(std::make_shared<GS_VariablesPlaceholderVisitor>(this)), _tableOfSymbols(std::move(tableOfSymbols)) {}

    GSTableOfSymbolsPtr GS_VariablesPlaceholderPass::getTableOfSymbols() {
        return _tableOfSymbols;
    }

    Void GS_VariablesPlaceholderPass::runForStatements(AST::GSStatementPtrArray &statements) {
        for (auto &statement : statements) {
            statement->accept(getVisitor().get());
        }
    }

}
