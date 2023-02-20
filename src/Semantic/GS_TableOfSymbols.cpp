#include <GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    GS_Symbol::~GS_Symbol() = default;

    GS_FunctionSymbol::GS_FunctionSymbol(UString name,
                                         AST::GS_FunctionSignature signature)
            : _name(std::move(name)),
              _signature(std::move(signature)) {}

    std::shared_ptr<GS_FunctionSymbol> GS_FunctionSymbol::Create(UString name,
                                                                 AST::GS_FunctionSignature signature) {
        return std::make_shared<GS_FunctionSymbol>(std::move(name),
                                                   std::move(signature));
    }

    ConstLRef<UString> GS_FunctionSymbol::GetName() const {
        return _name;
    }

    ConstLRef<AST::GS_FunctionSignature> GS_FunctionSymbol::GetSignature() const {
        return _signature;
    }

    SymbolType GS_FunctionSymbol::GetSymbolType() const {
        return SymbolType::Function;
    }

    GS_VariableSymbol::GS_VariableSymbol(UString name,
                                         GSTypePtr type)
            : _name(std::move(name)),
              _type(std::move(type)) {}

    std::shared_ptr<GS_VariableSymbol> GS_VariableSymbol::Create(UString name,
                                                                 GSTypePtr type) {
        return std::make_shared<GS_VariableSymbol>(std::move(name),
                                                   std::move(type));
    }

    ConstLRef<UString> GS_VariableSymbol::GetName() const {
        return _name;
    }

    ConstLRef<GSTypePtr> GS_VariableSymbol::GetType() const {
        return _type;
    }

    SymbolType GS_VariableSymbol::GetSymbolType() const {
        return SymbolType::Variable;
    }

    GS_TableOfSymbols::GS_TableOfSymbols(GSSymbolPtrArray symbols)
            : _symbols(std::move(symbols)) {}

    std::unique_ptr<GS_TableOfSymbols> GS_TableOfSymbols::Create(GSSymbolPtrArray symbols) {
        return std::make_unique<GS_TableOfSymbols>(std::move(symbols));
    }

    std::unique_ptr<GS_TableOfSymbols> GS_TableOfSymbols::Create() {
        return GS_TableOfSymbols::Create(GSSymbolPtrArray());
    }

    ConstLRef<GSSymbolPtr> GS_TableOfSymbols::AddSymbol(GSSymbolPtr symbol) {
        _symbols.emplace_back(std::move(symbol));

        return _symbols[_symbols.size() - 1];
    }

    ConstLRef<GS_FunctionSymbol> GS_TableOfSymbols::AddFunction(UString name,
                                                                AST::GS_FunctionSignature signature) {
        auto function = GS_FunctionSymbol::Create(std::move(name), std::move(signature));

        auto symbol = AddSymbol(function);

        return *ToSymbol<GS_FunctionSymbol>(symbol);
    }

    ConstLRef<GS_VariableSymbol> GS_TableOfSymbols::AddVariable(UString name,
                                                                GSTypePtr type) {
        auto variable = GS_VariableSymbol::Create(std::move(name), std::move(type));

        auto symbol = AddSymbol(variable);

        return *ToSymbol<GS_VariableSymbol>(symbol);
    }

    std::optional<GS_FunctionSymbol> GS_TableOfSymbols::GetFunction(UString name) const {
        auto movedName = std::move(name);

        for (auto &symbol : _symbols) {
            if (auto functionSymbol = ToSymbol<GS_FunctionSymbol>(symbol)) {
                if (functionSymbol->GetName() == movedName) {
                    return std::make_optional(*functionSymbol);
                }
            }
        }

        return std::nullopt;
    }

    std::optional<GS_VariableSymbol> GS_TableOfSymbols::GetVariable(UString name) const {
        auto movedName = std::move(name);

        for (auto &symbol : _symbols) {
            if (auto variableSymbol = ToSymbol<GS_VariableSymbol>(symbol)) {
                if (variableSymbol->GetName() == movedName) {
                    return std::make_optional(*variableSymbol);
                }
            }
        }

        return std::nullopt;
    }

    ConstLRef<GSSymbolPtrArray> GS_TableOfSymbols::GetSymbols() const {
        return _symbols;
    }

}
