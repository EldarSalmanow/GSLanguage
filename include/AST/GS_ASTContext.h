#ifndef GSLANGUAGE_GS_ASTCONTEXT_H
#define GSLANGUAGE_GS_ASTCONTEXT_H

#include <AST/GS_Type.h>

namespace GSLanguageCompiler::AST {

    /**
     * Context for containing information about types
     */
    class GS_ASTTypeContext {
    public:

        /**
         * Constructor for AST type context
         */
        GS_ASTTypeContext()
                : _voidType(AST::GS_VoidType::Create()),
                  _i32Type(AST::GS_I32Type::Create()),
                  _stringType(AST::GS_StringType::Create()) {}

    public:

        /**
         * Creating AST type context
         * @return AST type context ptr
         */
        static SharedPtr<GS_ASTTypeContext> Create() {
            return std::make_shared<GS_ASTTypeContext>();
        }

    public:

        /**
         * Getter for default Void type
         * @return Void type
         */
        SharedPtr<AST::GS_VoidType> GetVoidType() const {
            return _voidType;
        }

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        SharedPtr<AST::GS_I32Type> GetI32Type() const {
            return _i32Type;
        }

        /**
         * Getter for default String type
         * @return String type
         */
        SharedPtr<AST::GS_StringType> GetStringType() const {
            return _stringType;
        }

    private:

        /**
         * Void type
         */
        SharedPtr<AST::GS_VoidType>   _voidType;

        /**
         * I32 type
         */
        SharedPtr<AST::GS_I32Type>    _i32Type;

        /**
         * String type
         */
        SharedPtr<AST::GS_StringType> _stringType;
    };

    /**
     * AST type context ptr type
     */
    using GSASTTypeContextPtr = SharedPtr<GS_ASTTypeContext>;

    /**
     * Context for containing information about AST
     */
    class GS_ASTContext {
    public:

        /**
         * Constructor for AST context
         */
        GS_ASTContext()
                : _typeContext(GS_ASTTypeContext::Create()) {}

    public:

        /**
         * Creating AST context
         * @return AST context ptr
         */
        static SharedPtr<GS_ASTContext> Create() {
            return std::make_shared<GS_ASTContext>();
        }

    public:

        /**
         * Getter for default Void type
         * @return Void type
         */
        SharedPtr<AST::GS_VoidType> GetVoidType() const {
            return _typeContext->GetVoidType();
        }

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        SharedPtr<AST::GS_I32Type> GetI32Type() const {
            return _typeContext->GetI32Type();
        }

        /**
         * Getter for default String type
         * @return String type
         */
        SharedPtr<AST::GS_StringType> GetStringType() const {
            return _typeContext->GetStringType();
        }

    public:

        /**
         * Getter for AST type context
         * @return AST type context
         */
        GSASTTypeContextPtr GetTypeContext() const {
            return _typeContext;
        }

    private:

        /**
         * AST type context
         */
        GSASTTypeContextPtr _typeContext;
    };

    /**
     * AST context ptr type
     */
    using GSASTContextPtr = SharedPtr<GS_ASTContext>;

}

#endif //GSLANGUAGE_GS_ASTCONTEXT_H
