#include <GS_TableOfSymbols.h>

namespace GSLanguageCompiler::Semantic {

    GS_Symbol::~GS_Symbol() = default;
    
    Bool GS_Symbol::IsVariable() const {
        return false;
    }

    Bool GS_Symbol::IsFunction() const {
        return false;
    }

    GS_FunctionSymbol::GS_FunctionSymbol(UString name, AST::GSStatementPtrArray body)
            : _name(std::move(name)), _body(std::move(body)) {}

    std::shared_ptr<GS_FunctionSymbol> GS_FunctionSymbol::Create(UString name, AST::GSStatementPtrArray body) {
        return std::make_shared<GS_FunctionSymbol>(std::move(name), std::move(body));
    }

    UString GS_FunctionSymbol::GetName() const {
        return _name;
    }

    LRef<AST::GSStatementPtrArray> GS_FunctionSymbol::GetBody() {
        return _body;
    }

    Bool GS_FunctionSymbol::IsFunction() const {
        return true;
    }

    GS_VariableSymbol::GS_VariableSymbol(UString name, GSTypePtr type, AST::GSExpressionPtr expression)
            : _name(std::move(name)), _type(std::move(type)), _expression(std::move(expression)) {}

    std::shared_ptr<GS_VariableSymbol> GS_VariableSymbol::Create(UString name, GSTypePtr type, AST::GSExpressionPtr expression) {
        return std::make_shared<GS_VariableSymbol>(std::move(name), std::move(type), std::move(expression));
    }

    UString GS_VariableSymbol::GetName() const {
        return _name;
    }

    LRef<GSTypePtr> GS_VariableSymbol::GetType() {
        return _type;
    }

    LRef<AST::GSExpressionPtr> GS_VariableSymbol::GetExpression() {
        return _expression;
    }

    Bool GS_VariableSymbol::IsVariable() const {
        return true;
    }
    
    GS_TableOfSymbols::GS_TableOfSymbols() = default;

    std::shared_ptr<GS_TableOfSymbols> GS_TableOfSymbols::Create() {
        return std::make_shared<GS_TableOfSymbols>();
    }

    Void GS_TableOfSymbols::AddFunction(UString name, AST::GSStatementPtrArray body) {
        auto function = GS_FunctionSymbol::Create(std::move(name), std::move(body));

        _functions.emplace_back(function);
    }

    Void GS_TableOfSymbols::AddVariable(UString name, GSTypePtr type, AST::GSExpressionPtr expression) {
        auto variable = GS_VariableSymbol::Create(std::move(name), std::move(type), std::move(expression));
        
        _variables.emplace_back(variable);
    }

    std::shared_ptr<GS_FunctionSymbol> GS_TableOfSymbols::FindFunction(UString name) {
        for (auto &function : _functions) {
            if (function->GetName() == name) {
                return function;
            }
        }

        return nullptr;
    }

    std::shared_ptr<GS_VariableSymbol> GS_TableOfSymbols::FindVariable(UString name) {
        for (auto &variable : _variables) {
            if (variable->GetName() == name) {
                return variable;
            }
        }

        return nullptr;
    }

    Vector<std::shared_ptr<GS_FunctionSymbol>> GS_TableOfSymbols::GetFunctions() const {
        return _functions;
    }

    Vector<std::shared_ptr<GS_VariableSymbol>> GS_TableOfSymbols::GetVariables() const {
        return _variables;
    }

}
