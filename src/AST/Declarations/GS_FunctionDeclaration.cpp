#include <Declarations/GS_FunctionDeclaration.h>

namespace GSLanguageCompiler::AST {

    GS_FunctionQualifiers::GS_FunctionQualifiers(ExternType externType)
            : _externType(externType) {}

    GS_FunctionQualifiers GS_FunctionQualifiers::Create(ExternType externType) {
        return GS_FunctionQualifiers(externType);
    }

    GS_FunctionQualifiers GS_FunctionQualifiers::Create() {
        return GS_FunctionQualifiers::Create(ExternType::No);
    }

    Bool GS_FunctionQualifiers::IsExtern() const {
        return GetExternType() == ExternType::Yes;
    }

    ExternType GS_FunctionQualifiers::GetExternType() const {
        return _externType;
    }

    GS_FunctionParam::GS_FunctionParam(UString name,
                                       Semantic::GSTypePtr type)
            : _name(std::move(name)),
              _type(std::move(type)) {}

    GS_FunctionParam GS_FunctionParam::Create(UString name,
                                              Semantic::GSTypePtr type) {
        return GS_FunctionParam(std::move(name),
                                std::move(type));
    }

    ConstLRef<UString> GS_FunctionParam::GetName() const {
        return _name;
    }

    ConstLRef<Semantic::GSTypePtr> GS_FunctionParam::GetType() const {
        return _type;
    }

    GS_FunctionSignature::GS_FunctionSignature(GSFunctionParamArray params,
                                               Semantic::GSTypePtr returnType,
                                               GS_FunctionQualifiers qualifiers)
            : _params(std::move(params)),
              _returnType(std::move(returnType)),
              _qualifiers(qualifiers) {}

    GS_FunctionSignature GS_FunctionSignature::Create(GSFunctionParamArray params,
                                                      Semantic::GSTypePtr returnType,
                                                      GS_FunctionQualifiers qualifiers) {
        return GS_FunctionSignature(std::move(params),
                                    std::move(returnType),
                                    qualifiers);
    }

    GS_FunctionSignature GS_FunctionSignature::Create(GSFunctionParamArray params,
                                                      Semantic::GSTypePtr returnType) {
        return GS_FunctionSignature::Create(std::move(params),
                                            std::move(returnType),
                                            GS_FunctionQualifiers::Create());
    }

    GS_FunctionSignature GS_FunctionSignature::Create(GSFunctionParamArray params) {
        return GS_FunctionSignature::Create(std::move(params),
                                            Semantic::GS_VoidType::Create());
    }

    GS_FunctionSignature GS_FunctionSignature::Create(Semantic::GSTypePtr returnType) {
        return GS_FunctionSignature::Create(GSFunctionParamArray(),
                                            std::move(returnType));
    }

    GS_FunctionSignature GS_FunctionSignature::Create() {
        return GS_FunctionSignature::Create(GSFunctionParamArray(),
                                            Semantic::GS_VoidType::Create());
    }

    ConstLRef<GSFunctionParamArray> GS_FunctionSignature::GetParams() const {
        return _params;
    }

    ConstLRef<Semantic::GSTypePtr> GS_FunctionSignature::GetReturnType() const {
        return _returnType;
    }

    ConstLRef<GS_FunctionQualifiers> GS_FunctionSignature::GetQualifiers() const {
        return _qualifiers;
    }

    GS_FunctionDeclaration::GS_FunctionDeclaration(UString name,
                                                   GS_FunctionSignature signature,
                                                   GSStatementPtrArray body)
            : _name(std::move(name)),
              _signature(std::move(signature)),
              _body(std::move(body)) {}

    std::shared_ptr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name,
                                                                           GS_FunctionSignature signature,
                                                                           GSStatementPtrArray body) {
        return std::make_shared<GS_FunctionDeclaration>(std::move(name),
                                                        std::move(signature),
                                                        std::move(body));
    }

    std::shared_ptr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name,
                                                                           GS_FunctionSignature signature) {
        return GS_FunctionDeclaration::Create(std::move(name),
                                              std::move(signature),
                                              GSStatementPtrArray());
    }

    std::shared_ptr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name,
                                                                           GSStatementPtrArray body) {
        return GS_FunctionDeclaration::Create(std::move(name),
                                              GS_FunctionSignature::Create(),
                                              std::move(body));
    }

    std::shared_ptr<GS_FunctionDeclaration> GS_FunctionDeclaration::Create(UString name) {
        return GS_FunctionDeclaration::Create(std::move(name),
                                              GS_FunctionSignature::Create(),
                                              GSStatementPtrArray());
    }

    LRef<GSStatementPtr> GS_FunctionDeclaration::AddStatement(GSStatementPtr statement) {
        _body.emplace_back(std::move(statement));

        return _body[_body.size() - 1];
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
