#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GSScopePtr scope)
            : _name(std::move(name)), GS_Declaration(std::move(scope)) {
        _functionScope = std::make_shared<GS_Scope>(getScope());

        getScope()->addScope(_functionScope);
    }

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GSStatementPtrArray body, GSScopePtr scope)
            : _name(std::move(name)), _body(std::move(body)), GS_Declaration(std::move(scope)) {
        _functionScope = std::make_shared<GS_Scope>(getScope());

        getScope()->addScope(_functionScope);
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GSScopePtr scope) {
        return std::make_shared<GS_FunctionDeclaration>(std::move(name), std::move(scope));
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GSStatementPtrArray body, GSScopePtr scope) {
        return std::make_shared<GS_FunctionDeclaration>(std::move(name), std::move(body), std::move(scope));
    }

    Void GS_FunctionDeclaration::addStatement(GSStatementPtr statement) {
        auto bodyStatement = std::move(statement);

        _body.emplace_back(bodyStatement);

        _functionScope->addNode(bodyStatement);
    }

    LRef<UString> GS_FunctionDeclaration::getName() {
        return _name;
    }

    LRef<GSStatementPtrArray> GS_FunctionDeclaration::getBody() {
        return _body;
    }

    LRef<GSScopePtr> GS_FunctionDeclaration::getFunctionScope() {
        return _functionScope;
    }

    DeclarationType GS_FunctionDeclaration::getDeclarationType() const {
        return DeclarationType::FunctionDeclaration;
    }

}
