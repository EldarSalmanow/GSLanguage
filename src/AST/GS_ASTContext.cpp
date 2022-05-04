#include <GS_ASTContext.h>

namespace GSLanguageCompiler::AST {

    GS_ASTContext::GS_ASTContext()
            : _typeContext(Semantic::GS_TypeContext::Create()) {}

    SharedPtr<GS_ASTContext> GS_ASTContext::Create() {
        return std::make_shared<GS_ASTContext>();
    }

    SharedPtr<Semantic::GS_VoidType> GS_ASTContext::GetVoidType() const {
        return _typeContext->GetVoidType();
    }

    SharedPtr<Semantic::GS_I32Type> GS_ASTContext::GetI32Type() const {
        return _typeContext->GetI32Type();
    }

    SharedPtr<Semantic::GS_StringType> GS_ASTContext::GetStringType() const {
        return _typeContext->GetStringType();
    }

    Semantic::GSTypeContextPtr GS_ASTContext::GetTypeContext() const {
        return _typeContext;
    }

}
