#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GSStatementPtrArray body)
            : _name(std::move(name)), _body(std::move(body)) {}

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GSStatementPtrArray body) {
        return std::make_shared<GS_FunctionDeclaration>(std::move(name), std::move(body));
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name) {
        return GS_FunctionDeclaration::Create(std::move(name), GSStatementPtrArray());
    }

    Void GS_FunctionDeclaration::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));
    }

    LRef<UString> GS_FunctionDeclaration::GetName() {
        return _name;
    }

    LRef<GSStatementPtrArray> GS_FunctionDeclaration::GetBody() {
        return _body;
    }

    DeclarationType GS_FunctionDeclaration::GetDeclarationType() const {
        return DeclarationType::FunctionDeclaration;
    }

}
