#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GSScopePtr scope)
            : _name(std::move(name)), _functionScope(std::make_shared<GS_Scope>(std::move(scope))), GS_Declaration(std::move(scope)) {
        getScope()->addScope(_functionScope);
    }

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GSStatementPtrArray body, GSScopePtr scope)
            : _name(std::move(name)), _body(std::move(body)), _functionScope(std::make_shared<GS_Scope>(std::move(scope))), GS_Declaration(std::move(scope)) {
        getScope()->addScope(_functionScope);
    }

    Void GS_FunctionDeclaration::addStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));

        _functionScope->addNode(std::move(statement));
    }

    UString GS_FunctionDeclaration::getName() const {
        return _name;
    }

    GSStatementPtrArray GS_FunctionDeclaration::getBody() const {
        return _body;
    }

    GSScopePtr GS_FunctionDeclaration::getFunctionScope() const {
        return _functionScope;
    }

    Void GS_FunctionDeclaration::accept(Ptr<GS_Visitor> visitor) {
        visitor->visit(this);
    }

    DeclarationType GS_FunctionDeclaration::getDeclarationType() const {
        return DeclarationType::FunctionDeclaration;
    }

}
