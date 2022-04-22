#ifndef GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H

#include <llvm/IR/IRBuilder.h>

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Class for generating LLVM IR from AST
     */
    class GS_LLVMCodeGenerationVisitor {
    public:

        /**
         * Constructor for LLVM code generation visitor
         */
        GS_LLVMCodeGenerationVisitor();

    public:

        /**
         * Generate node
         * @param node Node
         * @return
         */
        Ptr<llvm::Value> GenerateNode(LRef<AST::GSNodePtr> node);

        /**
         * Generate declaration
         * @param declaration Declaration
         * @return
         */
        Ptr<llvm::Value> GenerateDeclaration(LRef<AST::GSDeclarationPtr> declaration);

        /**
         * Generate statement
         * @param statement Statement
         * @return
         */
        Ptr<llvm::Value> GenerateStatement(LRef<AST::GSStatementPtr> statement);

        /**
         * Generate expression
         * @param expression Expression
         * @return
         */
        Ptr<llvm::Value> GenerateExpression(LRef<AST::GSExpressionPtr> expression);

        /**
         * Generate translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        Ptr<llvm::Value> GenerateTranslationUnitDeclaration(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration);

        /**
         * Generate function declaration
         * @param functionDeclaration Function declaration
         * @return
         */
        Ptr<llvm::Value> GenerateFunctionDeclaration(LRef<SharedPtr<AST::GS_FunctionDeclaration>> functionDeclaration);

        /**
         * Generate variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return
         */
        Ptr<llvm::Value> GenerateVariableDeclarationStatement(LRef<SharedPtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement);

        /**
         * Generate assignment statement
         * @param assignmentStatement Assignment statement
         * @return
         */
        Ptr<llvm::Value> GenerateAssignmentStatement(LRef<SharedPtr<AST::GS_AssignmentStatement>> assignmentStatement);

        /**
         * Generate expression statement
         * @param expressionStatement Expression statement
         * @return
         */
        Ptr<llvm::Value> GenerateExpressionStatement(LRef<SharedPtr<AST::GS_ExpressionStatement>> expressionStatement);

        /**
         * Generate constant expression
         * @param constantExpression Constant expression
         * @return
         */
        Ptr<llvm::Value> GenerateConstantExpression(LRef<SharedPtr<AST::GS_ConstantExpression>> constantExpression);

        /**
         * Generate unary expression
         * @param unaryExpression Unary expression
         * @return
         */
        Ptr<llvm::Value> GenerateUnaryExpression(LRef<SharedPtr<AST::GS_UnaryExpression>> unaryExpression);

        /**
         * Generate binary expression
         * @param binaryExpression Binary expression
         * @return
         */
        Ptr<llvm::Value> GenerateBinaryExpression(LRef<SharedPtr<AST::GS_BinaryExpression>> binaryExpression);

        /**
         * Generate variable using expression
         * @param variableUsingExpression Variable using expression
         * @return
         */
        Ptr<llvm::Value> GenerateVariableUsingExpression(LRef<SharedPtr<AST::GS_VariableUsingExpression>> variableUsingExpression);

        /**
         * Generate function calling expression
         * @param functionCallingExpression Function calling expression
         * @return
         */
        Ptr<llvm::Value> GenerateFunctionCallingExpression(LRef<SharedPtr<AST::GS_FunctionCallingExpression>> functionCallingExpression);

    public:

        LRef<llvm::Module> GetModule();

    private:

        llvm::LLVMContext _context;

        llvm::IRBuilder<> _builder;

        llvm::Module _module;
    };

}

#endif //GSLANGUAGE_GS_LLVMCODEGENERATIONVISITOR_H
