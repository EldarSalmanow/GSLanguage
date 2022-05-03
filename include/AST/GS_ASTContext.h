#ifndef GSLANGUAGE_GS_ASTCONTEXT_H
#define GSLANGUAGE_GS_ASTCONTEXT_H

#include <AST/GS_Expression.h>

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
        GS_ASTTypeContext();

    public:

        /**
         * Creating AST type context
         * @return AST type context ptr
         */
        static SharedPtr<GS_ASTTypeContext> Create();

    public:

        /**
         * Getter for default Void type
         * @return Void type
         */
        SharedPtr<GS_VoidType> GetVoidType() const;

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        SharedPtr<GS_I32Type> GetI32Type() const;

        /**
         * Getter for default String type
         * @return String type
         */
        SharedPtr<GS_StringType> GetStringType() const;

    private:

        /**
         * Void type
         */
        SharedPtr<GS_VoidType> _voidType;

        /**
         * I32 type
         */
        SharedPtr<GS_I32Type> _i32Type;

        /**
         * String type
         */
        SharedPtr<GS_StringType> _stringType;
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
        GS_ASTContext();

    public:

        /**
         * Creating AST context
         * @return AST context ptr
         */
        static SharedPtr<GS_ASTContext> Create();

    public:

        /**
         * Getter for default Void type
         * @return Void type
         */
        SharedPtr<GS_VoidType> GetVoidType() const;

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        SharedPtr<GS_I32Type> GetI32Type() const;

        /**
         * Getter for default String type
         * @return String type
         */
        SharedPtr<GS_StringType> GetStringType() const;

    public:

        /**
         * Getter for AST type context
         * @return AST type context
         */
        GSASTTypeContextPtr GetTypeContext() const;

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
