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

        /**
         * Constructor for AST context
         */
        GS_ASTContext();

    public:

        /**
         * Creating AST context
         * @return AST context ptr
         */
        static std::shared_ptr<GS_ASTContext> Create();

    public:

        /**
         * Getter for default Void type
         * @return Void type
         */
        std::shared_ptr<Semantic::GS_VoidType> GetVoidType() const;

        /**
         * Getter for default I32 type
         * @return I32 type
         */
        std::shared_ptr<Semantic::GS_I32Type> GetI32Type() const;

        /**
         * Getter for default String type
         * @return String type
         */
        std::shared_ptr<Semantic::GS_StringType> GetStringType() const;

    public:

        /**
         * Getter for type context
         * @return Type context
         */
        Semantic::GSTypeContextPtr GetTypeContext() const;

    private:

        /**
         * Type context
         */
        Semantic::GSTypeContextPtr _typeContext;
    };

    /**
     * AST context ptr type
     */
    using GSASTContextPtr = std::shared_ptr<GS_ASTContext>;

}

#endif //GSLANGUAGE_GS_ASTCONTEXT_H
