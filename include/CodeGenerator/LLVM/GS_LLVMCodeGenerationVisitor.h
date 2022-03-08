#ifndef GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H

#include <llvm/IR/IRBuilder.h>

#include <CodeGenerator/GS_CodeGenerationVisitor.h>

#include <CodeGenerator/LLVM/GS_LLVMCodeGenerationVisitorContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_LLVMCodeGenerationVisitor : public GS_CodeGenerationVisitor<Ptr<llvm::Value>> {
    public:

        /**
         *
         */
        GS_LLVMCodeGenerationVisitor();

    public:

        Ptr<llvm::Value> visitTranslationUnitDeclaration(SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) override;

        Ptr<llvm::Value> visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) override;

        Ptr<llvm::Value> visitVariableDeclarationStatement(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        Ptr<llvm::Value> visitAssignmentStatement(SharedPtr<AST::GS_AssignmentStatement> assignmentStatement) override;

        Ptr<llvm::Value> visitExpressionStatement(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) override;

        Ptr<llvm::Value> visitConstantExpression(SharedPtr<AST::GS_ConstantExpression> constantExpression) override;

        Ptr<llvm::Value> visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) override;

        Ptr<llvm::Value> visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) override;

        Ptr<llvm::Value> visitVariableUsingExpression(SharedPtr<AST::GS_VariableUsingExpression> variableUsingExpression) override;

        Ptr<llvm::Value> visitFunctionCallingExpression(SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) override;

    private:

        Ptr<llvm::AllocaInst> _findVariableByName(ConstLRef<UString> name);

    private:

        SharedPtr<GS_LLVMCodeGenerationVisitorContext> _getLLVMVisitorContext();

    private:

        /**
         *
         */
        SharedPtr<llvm::IRBuilder<>> _builder;

        /**
         *
         */
        Vector<std::pair<UString, Ptr<llvm::AllocaInst>>> _variables;
    };

}

#endif //GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H
