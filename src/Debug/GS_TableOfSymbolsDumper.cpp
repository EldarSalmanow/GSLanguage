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

            UStringStream stringStream;

            switch (symbol->GetSymbolType()) {
                case Semantic::SymbolType::Function: {
                    auto functionSymbol = Semantic::ToSymbol<Semantic::GS_FunctionSymbol>(symbol);

                    stringStream
                            << index << ": Function {\n"_us
                            << "  Name: "_us << functionSymbol->GetName() << "\n}\n"_us;

                    break;
                }
                case Semantic::SymbolType::Variable: {
                    auto variableSymbol = Semantic::ToSymbol<Semantic::GS_VariableSymbol>(symbol);

                    stringStream
                            << index << ": Variable {\n"_us
                            << "  Name: "_us << variableSymbol->GetName() << "\n"_us
                            << "  Type: "_us << variableSymbol->GetType()->GetName() << "\n}\n"_us;

                    break;
                }
            }

            std::cout << stringStream.String();
        }

        std::cout << "-------------------------------------------"_us << std::endl;
    }

    Void DumpTableOfSymbols(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        auto dumper = GS_TableOfSymbolsDumper::Create(std::move(tableOfSymbols));

        dumper->Dump();
    }

}
