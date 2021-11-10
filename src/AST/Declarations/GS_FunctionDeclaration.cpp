#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionDeclaration::GS_FunctionDeclaration(String name, GSStatementPtrArray body, GSScopePtr scope)
            : _name(std::move(name)), _body(std::move(body)), GS_Declaration(std::move(scope)){}

    String GS_FunctionDeclaration::getName() {
        return _name;
    }

    GSStatementPtrArray GS_FunctionDeclaration::getBody() {
        return _body;
    }

    Void GS_FunctionDeclaration::accept(GS_Visitor *visitor) {
        visitor->visit(this);
    }

    DeclarationType GS_FunctionDeclaration::getDeclarationType() {
        return DeclarationType::FunctionDeclaration;
    }

}