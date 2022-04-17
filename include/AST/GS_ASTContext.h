#ifndef GSLANGUAGE_GS_ASTCONTEXT_H
#define GSLANGUAGE_GS_ASTCONTEXT_H

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::AST {

    // TODO comment all
    class GS_ASTTypeContext {
    public:

        GS_ASTTypeContext()
                : _voidType(AST::GS_VoidType::Create()),
                  _i32Type(AST::GS_I32Type::Create()),
                  _stringType(AST::GS_StringType::Create()) {}

    public:

        static SharedPtr<GS_ASTTypeContext> Create() {
            return std::make_shared<GS_ASTTypeContext>();
        }

    public:

        SharedPtr<AST::GS_VoidType> GetVoidType() const {
            return _voidType;
        }

        SharedPtr<AST::GS_I32Type> GetI32Type() const {
            return _i32Type;
        }

        SharedPtr<AST::GS_StringType> GetStringType() const {
            return _stringType;
        }

    private:

        SharedPtr<AST::GS_VoidType>   _voidType;

        SharedPtr<AST::GS_I32Type>    _i32Type;

        SharedPtr<AST::GS_StringType> _stringType;
    };

    using GSASTTypeContextPtr = SharedPtr<GS_ASTTypeContext>;

    class GS_ASTContext {
    public:

        GS_ASTContext()
                : _typeContext(GS_ASTTypeContext::Create()) {}

    public:

        static SharedPtr<GS_ASTContext> Create() {
            return std::make_shared<GS_ASTContext>();
        }

    public:

        SharedPtr<AST::GS_VoidType> GetVoidType() const {
            return _typeContext->GetVoidType();
        }

        SharedPtr<AST::GS_I32Type> GetI32Type() const {
            return _typeContext->GetI32Type();
        }

        SharedPtr<AST::GS_StringType> GetStringType() const {
            return _typeContext->GetStringType();
        }

    public:

        GSASTTypeContextPtr GetTypeContext() const {
            return _typeContext;
        }

    private:

        GSASTTypeContextPtr _typeContext;
    };

    using GSASTContextPtr = SharedPtr<GS_ASTContext>;

}

#endif //GSLANGUAGE_GS_ASTCONTEXT_H
