#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GSStatementPtrArray body, GSScopePtr scope)
            : _name(std::move(name)), _body(std::move(body)), GS_Declaration(std::move(scope)) {
        _functionScope = GS_Scope::Create(GetScope());

        GetScope()->AddScope(_functionScope);

        for (auto &statement : GetBody()) {
            _functionScope->AddNode(statement);
        }
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GSStatementPtrArray body, GSScopePtr scope) {
        return std::make_shared<GS_FunctionDeclaration>(std::move(name), std::move(body), std::move(scope));
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GSScopePtr scope) {
        return GS_FunctionDeclaration::Create(std::move(name), GSStatementPtrArray(), std::move(scope));
    }

    Void GS_FunctionDeclaration::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(statement);

        _functionScope->AddNode(statement);
    }

    LRef<UString> GS_FunctionDeclaration::GetName() {
        return _name;
    }

    LRef<GSStatementPtrArray> GS_FunctionDeclaration::GetBody() {
        return _body;
    }

    LRef<GSScopePtr> GS_FunctionDeclaration::GetFunctionScope() {
        return _functionScope;
    }

    DeclarationType GS_FunctionDeclaration::GetDeclarationType() const {
        return DeclarationType::FunctionDeclaration;
    }

}
