#include <GS_TableOfSymbolsDumper.h>

namespace GSLanguageCompiler::Debug {

    GS_TableOfSymbolsDumper::GS_TableOfSymbolsDumper(Semantic::GSTableOfSymbolsPtr tableOfSymbols)
            : _tableOfSymbols(std::move(tableOfSymbols)) {}

    std::shared_ptr<GS_TableOfSymbolsDumper> GS_TableOfSymbolsDumper::Create(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        return std::make_shared<GS_TableOfSymbolsDumper>(std::move(tableOfSymbols));
    }

    Void GS_TableOfSymbolsDumper::Dump() {
        std::cout << "---------- Table Of Symbols Dump ----------"_us << std::endl;

        U64 index = 0;

        for (auto &symbol : _tableOfSymbols->GetSymbols()) {
            ++index;

            if (symbol->IsFunction()) {
                auto functionSymbol = std::reinterpret_pointer_cast<Semantic::GS_FunctionSymbol>(symbol);

                std::cout << UString(std::to_string(index + 1)) << ": " << std::endl << "  Name -> "_us << functionSymbol->GetName() << std::endl;
            } else if (symbol->IsVariable()) {
                auto variableSymbol = std::reinterpret_pointer_cast<Semantic::GS_VariableSymbol>(symbol);

                std::cout << UString(std::to_string(index + 1)) << ": " << std::endl << "  Name -> "_us << variableSymbol->GetName() << std::endl << "  Type -> " << variableSymbol->GetType()->GetName() << std::endl;
            }
        }

        std::cout << "-------------------------------------------"_us << std::endl;
    }

    Void DumpTableOfSymbols(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        auto dumper = GS_TableOfSymbolsDumper::Create(std::move(tableOfSymbols));

        dumper->Dump();
    }

}
