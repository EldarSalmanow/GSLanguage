#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionDeclaration::GS_FunctionDeclaration(String name, GSStatementPtrArray body)
            : _name(std::move(name)), _body(std::move(body)) {}

    String GS_FunctionDeclaration::getName() {
        return _name;
    }

    GSStatementPtrArray GS_FunctionDeclaration::getBody() {
        return _body;
    }

    DeclarationType GS_FunctionDeclaration::getDeclarationType() {
        return DeclarationType::FunctionDeclaration;
    }

}
