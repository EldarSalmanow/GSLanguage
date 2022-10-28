#include <Lexer/Lexer.h>
#include <Parser/Parser.h>
#include <AST/AST.h>
#include <Semantic/Semantic.h>
#include <Optimizer/Optimizer.h>

#include <GS_CompilationUnit.h>
#include "Optimizer/Passes/GS_ConstantFoldingPass.h"

namespace GSLanguageCompiler::Driver {

    GS_CompilationUnit::GS_CompilationUnit(IO::GSSourcePtr source, Driver::GSContextPtr context)
            : _source(std::move(source)),
              _tokens(Lexer::GSTokenArray()),
              _node(AST::GSNodePtr()),
              _context(std::move(context)) {}

    std::shared_ptr<GS_CompilationUnit> GS_CompilationUnit::Create(IO::GSSourcePtr source, Driver::GSContextPtr context) {
        return std::make_shared<GS_CompilationUnit>(std::move(source), std::move(context));
    }

    CompilingResult GS_CompilationUnit::Compile() {
        auto lexer = Lexer::GS_Lexer::Create(_context);

        _tokens = lexer.Tokenize(_source);

        auto parser = Parser::GS_Parser::Create(_context);

        _node = parser.ParseProgram(_tokens, _source->GetName().GetName());

        auto optimizer = Optimizer::GS_Optimizer::Create(_context);

        AST::GSPassPtrArray optimizingPasses = {
                Optimizer::CreateConstantFoldingPass()
        };

        optimizer->Optimize(_node, optimizingPasses);

        return CompilingResult::Success;
    }

    IO::GSSourcePtr GS_CompilationUnit::GetSource() const {
        return _source;
    }

    Lexer::GSTokenArray GS_CompilationUnit::GetTokens() const {
        return _tokens;
    }

    AST::GSNodePtr GS_CompilationUnit::GetNode() const {
        return _node;
    }

    Semantic::GSTableOfSymbolsPtr GS_CompilationUnit::GetTableOfSymbols() const {
        return _tableOfSymbols;
    }

    Driver::GSContextPtr GS_CompilationUnit::GetContext() const {
        return _context;
    }

    U64 GS_CompilationUnit::GetId() const {
        return _id;
    }

    GS_CompilationUnitsManager::GS_CompilationUnitsManager(GSCompilationUnitPtrArray compilationUnits)
            : _compilationUnits(std::move(compilationUnits)) {}

    std::shared_ptr<GS_CompilationUnitsManager> GS_CompilationUnitsManager::Create(GSCompilationUnitPtrArray compilationUnits) {
        return std::make_shared<GS_CompilationUnitsManager>(std::move(compilationUnits));
    }

    std::shared_ptr<GS_CompilationUnitsManager> GS_CompilationUnitsManager::Create() {
        return GS_CompilationUnitsManager::Create(GSCompilationUnitPtrArray());
    }

    U64 GS_CompilationUnitsManager::AddCompilationUnit(GSCompilationUnitPtr compilationUnit) {
        auto compilationUnitId = compilationUnit->GetId();

        _compilationUnits.emplace_back(std::move(compilationUnit));

        return compilationUnitId;
    }

    GSCompilationUnitPtr GS_CompilationUnitsManager::GetCompilationUnit(U64 compilationUnitId) {
        for (auto &compilationUnit : _compilationUnits) {
            if (compilationUnit->GetId() == compilationUnitId) {
                return compilationUnit;
            }
        }

        return nullptr;
    }

    GSCompilationUnitPtrArray GS_CompilationUnitsManager::GetCompilationUnits() const {
        return _compilationUnits;
    }

}
