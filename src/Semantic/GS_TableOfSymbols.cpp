#include <GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    Bool GS_Symbol::isVariable() {
        return false;
    }

    GS_VariableSymbol::GS_VariableSymbol(String name, AST::GSTypePtr type, AST::GSExpressionPtr expression)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)) {}

    String GS_VariableSymbol::getName() {
        return _name;
    }

    AST::GSTypePtr GS_VariableSymbol::getType() {
        return _type;
    }

    AST::GSExpressionPtr GS_VariableSymbol::getExpression() {
        return _expression;
    }

    Bool GS_VariableSymbol::isVariable() {
        return true;
    }

    GS_TableOfSymbols::GS_TableOfSymbols() = default;

    Void GS_TableOfSymbols::addSymbol(GSSymbolPtr symbol) {
        _symbols.emplace_back(std::move(symbol));
    }

    Void GS_TableOfSymbols::addVariable(String name, AST::GSTypePtr type, AST::GSExpressionPtr expression) {
        _symbols.emplace_back(std::make_shared<GS_VariableSymbol>(std::move(name), std::move(type), std::move(expression)));
    }

}
