#ifndef GSLANGUAGE_GS_ASTCONTEXT_H
#define GSLANGUAGE_GS_ASTCONTEXT_H

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::AST {

    // TODO comment all
    class GS_TypeContext {
    public:

        GS_TypeContext()
                : _voidType(AST::GS_VoidType::Create()),
                  _i32Type(AST::GS_I32Type::Create()),
                  _stringType(AST::GS_StringType::Create()) {}

    public:

        static SharedPtr<GS_TypeContext> Create() {
            return std::make_shared<GS_TypeContext>();
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

    class GS_ASTContext {
    public:

        GS_ASTContext()
                : _typeContext(GS_TypeContext::Create()) {}

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

        SharedPtr<GS_TypeContext> GetTypeContext() const {
            return _typeContext;
        }

    private:

        SharedPtr<GS_TypeContext> _typeContext;
    };

}

#endif //GSLANGUAGE_GS_ASTCONTEXT_H
