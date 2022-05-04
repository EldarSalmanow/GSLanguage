#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionSignature::GS_FunctionSignature(Semantic::GSTypePtrArray paramTypes, Semantic::GSTypePtr returnType)
            : _paramTypes(std::move(paramTypes)), _returnType(std::move(returnType)) {}

    GS_FunctionSignature GS_FunctionSignature::Create(Semantic::GSTypePtrArray paramTypes, Semantic::GSTypePtr returnType) {
        return GS_FunctionSignature(std::move(paramTypes), std::move(returnType));
    }

    GS_FunctionSignature GS_FunctionSignature::Create(Semantic::GSTypePtrArray paramTypes) {
        return GS_FunctionSignature::Create(std::move(paramTypes), Semantic::GS_VoidType::Create());
    }

    GS_FunctionSignature GS_FunctionSignature::Create(Semantic::GSTypePtr returnType) {
        return GS_FunctionSignature::Create(Semantic::GSTypePtrArray(), std::move(returnType));
    }

    GS_FunctionSignature GS_FunctionSignature::Create() {
        return GS_FunctionSignature::Create(Semantic::GSTypePtrArray(), Semantic::GS_VoidType::Create());
    }

    Semantic::GSTypePtrArray GS_FunctionSignature::GetParamTypes() const {
        return _paramTypes;
    }

    Semantic::GSTypePtr GS_FunctionSignature::GetReturnType() const {
        return _returnType;
    }

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name, GS_FunctionSignature signature, GSStatementPtrArray body)
            : _name(std::move(name)), _signature(std::move(signature)), _body(std::move(body)) {}

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GS_FunctionSignature signature, GSStatementPtrArray body) {
        return std::make_shared<GS_FunctionDeclaration>(std::move(name), std::move(signature), std::move(body));
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GS_FunctionSignature signature) {
        return GS_FunctionDeclaration::Create(std::move(name), std::move(signature), GSStatementPtrArray());
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name, GSStatementPtrArray body) {
        return GS_FunctionDeclaration::Create(std::move(name), GS_FunctionSignature::Create(), std::move(body));
    }

    SharedPtr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name) {
        return GS_FunctionDeclaration::Create(std::move(name), GS_FunctionSignature::Create(), GSStatementPtrArray());
    }

    Void GS_FunctionDeclaration::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));
    }

    LRef<UString> GS_FunctionDeclaration::GetName() {
        return _name;
    }

    LRef<GS_FunctionSignature> GS_FunctionDeclaration::GetSignature() {
        return _signature;
    }

    LRef<GSStatementPtrArray> GS_FunctionDeclaration::GetBody() {
        return _body;
    }

    DeclarationType GS_FunctionDeclaration::GetDeclarationType() const {
        return DeclarationType::FunctionDeclaration;
    }

}
