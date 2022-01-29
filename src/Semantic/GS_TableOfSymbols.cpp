#include <GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    Bool GS_Symbol::isVariable() const {
        return false;
    }

    GS_VariableSymbol::GS_VariableSymbol(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)) {}

    UString GS_VariableSymbol::getName() const {
        return _name;
    }

    AST::GSTypePtr GS_VariableSymbol::getType() const {
        return _type;
    }

    LRef<AST::GSExpressionPtr> GS_VariableSymbol::getExpression() {
        return _expression;
    }

    Bool GS_VariableSymbol::isVariable() const {
        return true;
    }

    GS_TableOfSymbols::GS_TableOfSymbols() = default;

    Void GS_TableOfSymbols::addSymbol(GSSymbolPtr symbol) {
        _symbols.emplace_back(std::move(symbol));
    }

    Void GS_TableOfSymbols::addVariable(UString name, AST::GSTypePtr type, AST::GSExpressionPtr expression) {
        _symbols.emplace_back(std::make_shared<GS_VariableSymbol>(std::move(name), std::move(type), std::move(expression)));
    }

    SharedPtr<GS_VariableSymbol> GS_TableOfSymbols::getVariable(UString name) {
        for (auto &symbol : _symbols) {
            if (symbol->isVariable()) {
                auto variable = std::reinterpret_pointer_cast<GS_VariableSymbol>(symbol);

                if (variable->getName() == name) {
                    return variable;
                }
            }
        }

        return nullptr;
    }

}
