#include <GS_ASTContext.h>

namespace GSLanguageCompiler::AST {

    GS_ASTTypeContext::GS_ASTTypeContext()
            : _voidType(AST::GS_VoidType::Create()),
              _i32Type(AST::GS_I32Type::Create()),
              _stringType(AST::GS_StringType::Create()) {}

    SharedPtr<GS_ASTTypeContext> GS_ASTTypeContext::Create() {
        return std::make_shared<GS_ASTTypeContext>();
    }

    SharedPtr<GS_VoidType> GS_ASTTypeContext::GetVoidType() const {
        return _voidType;
    }

    SharedPtr<GS_I32Type> GS_ASTTypeContext::GetI32Type() const {
        return _i32Type;
    }

    SharedPtr<GS_StringType> GS_ASTTypeContext::GetStringType() const {
        return _stringType;
    }

    GS_ASTContext::GS_ASTContext()
            : _typeContext(GS_ASTTypeContext::Create()) {}

    SharedPtr<GS_ASTContext> GS_ASTContext::Create() {
        return std::make_shared<GS_ASTContext>();
    }

    SharedPtr<GS_VoidType> GS_ASTContext::GetVoidType() const {
        return _typeContext->GetVoidType();
    }

    SharedPtr<GS_I32Type> GS_ASTContext::GetI32Type() const {
        return _typeContext->GetI32Type();
    }

    SharedPtr<GS_StringType> GS_ASTContext::GetStringType() const {
        return _typeContext->GetStringType();
    }

    GSASTTypeContextPtr GS_ASTContext::GetTypeContext() const {
        return _typeContext;
    }

}
