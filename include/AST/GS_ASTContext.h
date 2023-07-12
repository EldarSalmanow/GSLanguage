#ifndef GSLANGUAGE_GS_ASTCONTEXT_H
#define GSLANGUAGE_GS_ASTCONTEXT_H

#include <Semantic/GS_Type.h>

#include <AST/GS_Expression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Context for containing information about AST
     */
    class GS_ASTContext {
    public:

        /*
         *
         * GS_ASTContext PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for AST context
         * @param typeContext Type context
         */
        explicit GS_ASTContext(Semantic::GSTypeContextPtr typeContext);

    public:

        /*
         *
         * GS_ASTContext PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating AST context
         * @param typeContext Type context
         * @return AST context ptr
         */
        static std::unique_ptr<GS_ASTContext> Create(Semantic::GSTypeContextPtr typeContext);

        /**
         * Creating AST context
         * @return AST context ptr
         */
        static std::unique_ptr<GS_ASTContext> Create();

    public:

        /*
         *
         * GS_ASTContext PUBLIC METHODS
         *
         */

        /**
         * Getter for default Void type
         * @return Void type
         */
        Semantic::TypePtr<Semantic::GS_VoidType> GetVoidType() const;

        /**
         * Getter for default Bool type
         * @return Bool type
         */
        Semantic::TypePtr<Semantic::GS_BoolType> GetBoolType() const;

        /**
         * Getter for default Char type
         * @return Char type
         */
        Semantic::TypePtr<Semantic::GS_CharType> GetCharType() const;

        /**
         * Getter for default I8 type
         * @return I8 type
         */
        Semantic::TypePtr<Semantic::GS_I8Type> GetI8Type() const;

        /**
         * Getter for default I16 type
         * @return I16 type
         */
        Semantic::TypePtr<Semantic::GS_I16Type> GetI16Type() const;

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        Semantic::TypePtr<Semantic::GS_I32Type> GetI32Type() const;

        /**
         * Getter for default I64 type
         * @return I64 type
         */
        Semantic::TypePtr<Semantic::GS_I64Type> GetI64Type() const;

        /**
         * Getter for default U8 type
         * @return U8 type
         */
        Semantic::TypePtr<Semantic::GS_U8Type> GetU8Type() const;

        /**
         * Getter for default U16 type
         * @return U16 type
         */
        Semantic::TypePtr<Semantic::GS_U16Type> GetU16Type() const;

        /**
         * Getter for default U32 type
         * @return U32 type
         */
        Semantic::TypePtr<Semantic::GS_U32Type> GetU32Type() const;

        /**
         * Getter for default U64 type
         * @return U64 type
         */
        Semantic::TypePtr<Semantic::GS_U64Type> GetU64Type() const;

        /**
         * Getter for default String type
         * @return String type
         */
        Semantic::TypePtr<Semantic::GS_StringType> GetStringType() const;

        /**
         * Getter for default Array type
         * @param elementsType Type of array elements
         * @param size Size of array
         * @return Array type
         */
        Semantic::TypePtr<Semantic::GS_ArrayType> GetArrayType(Semantic::GSTypePtr elementsType,
                                                               U64 size) const;

    public:

        /*
         *
         * GS_ASTContext PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for type context
         * @return Type context
         */
        LRef<Semantic::GS_TypeContext> GetTypeContext();

    private:

        /*
         *
         * GS_ASTContext PRIVATE FIELDS
         *
         */

        /**
         * Type context
         */
        Semantic::GSTypeContextPtr _typeContext;
    };

    /**
     * AST context ptr type
     */
    using GSASTContextPtr = std::unique_ptr<GS_ASTContext>;

}

#endif //GSLANGUAGE_GS_ASTCONTEXT_H
