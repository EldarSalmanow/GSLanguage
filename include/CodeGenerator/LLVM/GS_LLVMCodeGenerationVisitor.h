#ifndef GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H

#include <llvm/IR/Value.h>

#include <CodeGenerator/GS_CodeGenerationVisitor.h>

#include <CodeGenerator/LLVM/GS_LLVMCompilerUnit.h>

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

        Ptr<llvm::Value> visitNode(ConstLRef<AST::GSNodePtr> node) override;

        Ptr<llvm::Value> visitDeclaration(ConstLRef<AST::GSDeclarationPtr> declaration) override;

        Ptr<llvm::Value> visitStatement(ConstLRef<AST::GSStatementPtr> statement) override;

        Ptr<llvm::Value> visitExpression(ConstLRef<AST::GSExpressionPtr> expression) override;

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

    public:

        /**
         *
         * @return
         */
        GSCompilerUnitPtr getCompilerUnit() override;

    private:

        /**
         *
         */
        SharedPtr<GS_LLVMCompilerUnit> _unit;

        /**
         *
         */
        llvm::IRBuilder<> _builder;
    };

}

#endif //GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H
