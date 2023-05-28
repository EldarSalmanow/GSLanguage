#include <GS_TableOfSymbolsDumper.h>

namespace GSLanguageCompiler::Debug {

    GS_TableOfSymbolsDumper::GS_TableOfSymbolsDumper(ConstLRef<Semantic::GS_TableOfSymbols> tableOfSymbols)
            : _tableOfSymbols(tableOfSymbols) {}

    std::shared_ptr<GS_TableOfSymbolsDumper> GS_TableOfSymbolsDumper::Create(ConstLRef<Semantic::GS_TableOfSymbols> tableOfSymbols) {
        return std::make_shared<GS_TableOfSymbolsDumper>(tableOfSymbols);
    }

    Void GS_TableOfSymbolsDumper::Dump() {
        std::cout << "---------- Table Of Symbols Dump ----------"_us << std::endl;

        U64 index = 0;

        for (auto &symbol : _tableOfSymbols.GetSymbols()) {
            ++index;

            UStringStream stringStream;

            auto symbolType = symbol->GetSymbolType();

            switch (symbolType) {
                case Semantic::SymbolType::Function: {
                    auto functionSymbol = Semantic::ToSymbol<Semantic::GS_FunctionSymbol>(symbol);

                    stringStream
                            << index << ": Function {\n"_us
                            << "  Name: "_us << functionSymbol->GetName() << "\n}\n"_us;

                    break;
                }
                case Semantic::SymbolType::Variable: {
                    auto variableSymbol = Semantic::ToSymbol<Semantic::GS_VariableSymbol>(symbol);

                    // TODO Add UnknownType

                    stringStream
                            << index << ": Variable {\n"_us
                            << "  Name: "_us << variableSymbol->GetName() << "\n"_us
                            << "  Type: "_us << (variableSymbol->GetType() ? variableSymbol->GetType()->GetName() : "<unknown>"_us) << "\n}\n"_us;

                    break;
                }
            }

            std::cout << stringStream.String();
        }

        std::cout << "-------------------------------------------"_us << std::endl;
    }

    Void DumpTableOfSymbols(ConstLRef<Semantic::GS_TableOfSymbols> tableOfSymbols) {
        auto dumper = GS_TableOfSymbolsDumper::Create(tableOfSymbols);

        dumper->Dump();
    }

}
