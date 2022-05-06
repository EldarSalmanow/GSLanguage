#include <GS_TableOfSymbolsDumper.h>

namespace GSLanguageCompiler::Debug {

    GS_TableOfSymbolsDumper::GS_TableOfSymbolsDumper(Semantic::GSTableOfSymbolsPtr tableOfSymbols)
            : _tableOfSymbols(std::move(tableOfSymbols)) {}

    SharedPtr<GS_TableOfSymbolsDumper> GS_TableOfSymbolsDumper::Create(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        return std::make_shared<GS_TableOfSymbolsDumper>(std::move(tableOfSymbols));
    }

    Void GS_TableOfSymbolsDumper::Dump() {
        UCOut() << "---------- Table Of Symbols Dump ----------\n"_us;

        auto functions = _tableOfSymbols->GetFunctions();

        if (!functions.empty()) {
            UCOut() << "----------       Functions       ----------\n"_us;

            for (auto index = 0; index < functions.size(); ++index) {
                auto function = functions[index];

                UCOut() << UString(std::to_string(index + 1)) << ": \n  Name -> "_us << function->GetName() << "\n"_us;
            }
        }

        auto variables = _tableOfSymbols->GetVariables();

        if (!variables.empty()) {
            UCOut() << "----------       Variables       ----------\n"_us;

            for (auto index = 0; index < variables.size(); ++index) {
                auto variable = variables[index];

                UCOut() << UString(std::to_string(index + 1)) << ": \n  Name -> "_us << variable->GetName() << "\n  Type -> " << variable->GetType()->GetName() << "\n"_us;
            }
        }

        UCOut() << "-------------------------------------------\n"_us;
    }

    Void DumpTableOfSymbols(Semantic::GSTableOfSymbolsPtr tableOfSymbols) {
        auto dumper = GS_TableOfSymbolsDumper::Create(std::move(tableOfSymbols));

        dumper->Dump();
    }

}
