#include <GS_ASTContext.h>

namespace GSLanguageCompiler::AST {

    GS_ASTContext::GS_ASTContext(Semantic::GSTypeContextPtr typeContext)
            : _typeContext(std::move(typeContext)) {}

    std::unique_ptr<GS_ASTContext> GS_ASTContext::Create(Semantic::GSTypeContextPtr typeContext) {
        return std::make_unique<GS_ASTContext>(std::move(typeContext));
    }

    std::unique_ptr<GS_ASTContext> GS_ASTContext::Create() {
        return GS_ASTContext::Create(Semantic::GS_TypeContext::Create());
    }

    Semantic::TypePtr<Semantic::GS_VoidType> GS_ASTContext::GetVoidType() const {
        return _typeContext->GetVoidType();
    }

    Semantic::TypePtr<Semantic::GS_BoolType> GS_ASTContext::GetBoolType() const {
        return _typeContext->GetBoolType();
    }

    Semantic::TypePtr<Semantic::GS_CharType> GS_ASTContext::GetCharType() const {
        return _typeContext->GetCharType();
    }

    Semantic::TypePtr<Semantic::GS_I8Type> GS_ASTContext::GetI8Type() const {
        return _typeContext->GetI8Type();
    }

    Semantic::TypePtr<Semantic::GS_I16Type> GS_ASTContext::GetI16Type() const {
        return _typeContext->GetI16Type();
    }

    Semantic::TypePtr<Semantic::GS_I32Type> GS_ASTContext::GetI32Type() const {
        return _typeContext->GetI32Type();
    }

    Semantic::TypePtr<Semantic::GS_I64Type> GS_ASTContext::GetI64Type() const {
        return _typeContext->GetI64Type();
    }

    Semantic::TypePtr<Semantic::GS_U8Type> GS_ASTContext::GetU8Type() const {
        return _typeContext->GetU8Type();
    }

    Semantic::TypePtr<Semantic::GS_U16Type> GS_ASTContext::GetU16Type() const {
        return _typeContext->GetU16Type();
    }

    Semantic::TypePtr<Semantic::GS_U32Type> GS_ASTContext::GetU32Type() const {
        return _typeContext->GetU32Type();
    }

    Semantic::TypePtr<Semantic::GS_U64Type> GS_ASTContext::GetU64Type() const {
        return _typeContext->GetU64Type();
    }

    Semantic::TypePtr<Semantic::GS_StringType> GS_ASTContext::GetStringType() const {
        return _typeContext->GetStringType();
    }

    Semantic::TypePtr<Semantic::GS_ArrayType> GS_ASTContext::GetArrayType(Semantic::GSTypePtr elementsType,
                                                                          U64 size) const {
        return _typeContext->GetArrayType(std::move(elementsType),
                                          size);
    }

    LRef<Semantic::GS_TypeContext> GS_ASTContext::GetTypeContext() {
        return *_typeContext;
    }

}
