#include <GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    GS_Symbol::~GS_Symbol() = default;
    
    Bool GS_Symbol::IsFunction() const {
        return false;
    }

    Bool GS_Symbol::IsVariable() const {
        return false;
    }

    GS_FunctionSymbol::GS_FunctionSymbol(UString name, AST::GS_FunctionSignature signature)
            : _name(std::move(name)), _signature(std::move(signature)) {}

    std::shared_ptr<GS_FunctionSymbol> GS_FunctionSymbol::Create(UString name, AST::GS_FunctionSignature signature) {
        return std::make_shared<GS_FunctionSymbol>(std::move(name), std::move(signature));
    }

    UString GS_FunctionSymbol::GetName() const {
        return _name;
    }

    AST::GS_FunctionSignature GS_FunctionSymbol::GetSignature() const {
        return _signature;
    }

    Bool GS_FunctionSymbol::IsFunction() const {
        return true;
    }

    GS_VariableSymbol::GS_VariableSymbol(UString name, GSTypePtr type)
            : _name(std::move(name)), _type(std::move(type)) {}

    std::shared_ptr<GS_VariableSymbol> GS_VariableSymbol::Create(UString name, GSTypePtr type) {
        return std::make_shared<GS_VariableSymbol>(std::move(name), std::move(type));
    }

    UString GS_VariableSymbol::GetName() const {
        return _name;
    }

    GSTypePtr GS_VariableSymbol::GetType() const {
        return _type;
    }

    Bool GS_VariableSymbol::IsVariable() const {
        return true;
    }
    
    GS_TableOfSymbols::GS_TableOfSymbols(GSSymbolPtrArray symbols)
            : _symbols(std::move(symbols)) {}

    std::shared_ptr<GS_TableOfSymbols> GS_TableOfSymbols::Create(GSSymbolPtrArray symbols) {
        return std::make_shared<GS_TableOfSymbols>(std::move(symbols));
    }

    std::shared_ptr<GS_TableOfSymbols> GS_TableOfSymbols::Create() {
        return GS_TableOfSymbols::Create(GSSymbolPtrArray());
    }

    Void GS_TableOfSymbols::AddSymbol(GSSymbolPtr symbol) {
        _symbols.emplace_back(std::move(symbol));
    }

    Void GS_TableOfSymbols::AddFunction(UString name, AST::GS_FunctionSignature signature) {
        auto function = GS_FunctionSymbol::Create(std::move(name), std::move(signature));

        AddSymbol(function);
    }

    Void GS_TableOfSymbols::AddVariable(UString name, GSTypePtr type) {
        auto variable = GS_VariableSymbol::Create(std::move(name), std::move(type));
        
        AddSymbol(variable);
    }

    SymbolPtr<GS_FunctionSymbol> GS_TableOfSymbols::GetFunction(UString name) const {
        for (auto &symbol : _symbols) {
            if (symbol->IsFunction()) {
                // TODO: add SymbolCast function for casting symbols from any type to concrete type with check
                auto function = std::reinterpret_pointer_cast<GS_FunctionSymbol>(symbol);

                if (function->GetName() == name) {
                    return function;
                }
            }
        }

        return nullptr;
    }

    SymbolPtr<GS_VariableSymbol> GS_TableOfSymbols::GetVariable(UString name) const {
        for (auto &symbol : _symbols) {
            if (symbol->IsVariable()) {
                auto variable = std::reinterpret_pointer_cast<GS_VariableSymbol>(symbol);

                if (variable->GetName() == name) {
                    return variable;
                }
            }
        }

        return nullptr;
    }

    GSSymbolPtrArray GS_TableOfSymbols::GetSymbols() const {
        return _symbols;
    }

}
