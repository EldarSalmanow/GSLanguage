#include <GS_TableOfSymbolsDumper.h>

namespace GSLanguageCompiler::Debug {

    GS_TableOfSymbolsDumper::GS_TableOfSymbolsDumper(Semantic::GSTableOfSymbolsPtr tableOfSymbols)
            : _tableOfSymbols(std::move(tableOfSymbols)) {}

    std::shared_ptr<GS_TableOfSymbolsDumper> GS_TableOfSymbolsDumper::Create(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        return std::make_shared<GS_TableOfSymbolsDumper>(std::move(tableOfSymbols));
    }

    Void GS_TableOfSymbolsDumper::Dump() {
        std::cout << "---------- Table Of Symbols Dump ----------"_us << std::endl;

        auto functions = _tableOfSymbols->GetFunctions();

        if (!functions.empty()) {
            std::cout << "----------       Functions       ----------"_us << std::endl;

            for (auto index = 0; index < functions.size(); ++index) {
                auto function = functions[index];

                std::cout << UString(std::to_string(index + 1)) << ": " << std::endl << "  Name -> "_us << function->GetName() << std::endl;
            }
        }

        auto variables = _tableOfSymbols->GetVariables();

        if (!variables.empty()) {
            std::cout << "----------       Variables       ----------"_us << std::endl;

            for (auto index = 0; index < variables.size(); ++index) {
                auto variable = variables[index];

                std::cout << UString(std::to_string(index + 1)) << ": " << std::endl << "  Name -> "_us << variable->GetName() << std::endl << "  Type -> " << variable->GetType()->GetName() << std::endl;
            }
        }

        std::cout << "-------------------------------------------"_us << std::endl;
    }

    Void DumpTableOfSymbols(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        auto dumper = GS_TableOfSymbolsDumper::Create(std::move(tableOfSymbols));

        dumper->Dump();
    }

}
