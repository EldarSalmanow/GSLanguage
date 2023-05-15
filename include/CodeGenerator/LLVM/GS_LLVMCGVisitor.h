#ifndef GSLANGUAGE_GS_LLVMCGVISITOR_H
#define GSLANGUAGE_GS_LLVMCGVISITOR_H

#include <llvm/IR/IRBuilder.h>

#include <AST/GS_Visitor.h>

#include <CodeGenerator/LLVM/GS_LLVMCGBackend.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Class for generating LLVM IR from AST
     */
    class GS_LLVMCGVisitor {
    public:

        /**
         * Constructor for LLVM code generation visitor
         * @param codeHolder LLVM code holder
         */
        explicit GS_LLVMCGVisitor(LRef<GS_LLVMCodeHolder> codeHolder);

    public:

        /**
         * Generate node
         * @param session Session
         * @param node Node
         * @return Generated node
         */
        Ptr<llvm::Value> GenerateNode(LRef<Driver::GS_Session> session,
                                      LRef<AST::GSNodePtr> node);

        /**
         * Generate declaration
         * @param session Session
         * @param declaration Declaration
         * @return Generated declaration
         */
        Ptr<llvm::Value> GenerateDeclaration(LRef<Driver::GS_Session> session,
                                             LRef<AST::GSDeclarationPtr> declaration);

        /**
         * Generate statement
         * @param session Session
         * @param statement Statement
         * @return Generated statement
         */
        Ptr<llvm::Value> GenerateStatement(LRef<Driver::GS_Session> session,
                                           LRef<AST::GSStatementPtr> statement);

        /**
         * Generate expression
         * @param session Session
         * @param expression Expression
         * @return Generated expression
         */
        Ptr<llvm::Value> GenerateExpression(LRef<Driver::GS_Session> session,
                                            LRef<AST::GSExpressionPtr> expression);

        /**
         * Generate translation unit declaration
         * @param session Session
         * @param translationUnitDeclaration Translation unit declaration
         * @return Generated translation unit declaration
         */
        Ptr<llvm::Value> GenerateTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                            AST::NodePtrLRef<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration);

        /**
         * Generate function declaration
         * @param session Session
         * @param functionDeclaration Function declaration
         * @return Generated function declaration
         */
        Ptr<llvm::Value> GenerateFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                     AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration);

        /**
         * Generate variable declaration statement
         * @param session Session
         * @param variableDeclarationStatement Variable declaration statement
         * @return Generated variable declaration statement
         */
        Ptr<llvm::Value> GenerateVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                              AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement);

        /**
         * Generate assignment statement
         * @param session Session
         * @param assignmentStatement Assignment statement
         * @return Generated assignment statement
         */
        Ptr<llvm::Value> GenerateAssignmentStatement(LRef<Driver::GS_Session> session,
                                                     AST::NodePtrLRef<AST::GS_AssignmentStatement> assignmentStatement);

        /**
         * Generate expression statement
         * @param session Session
         * @param expressionStatement Expression statement
         * @return Generated expression statement
         */
        Ptr<llvm::Value> GenerateExpressionStatement(LRef<Driver::GS_Session> session,
                                                     AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement);

        /**
         * Generate constant expression
         * @param session Session
         * @param constantExpression Constant expression
         * @return Generated constant expression
         */
        Ptr<llvm::Value> GenerateConstantExpression(LRef<Driver::GS_Session> session,
                                                    AST::NodePtrLRef<AST::GS_ConstantExpression> constantExpression);

        /**
         * Generate unary expression
         * @param session Session
         * @param unaryExpression Unary expression
         * @return Generated unary expression
         */
        Ptr<llvm::Value> GenerateUnaryExpression(LRef<Driver::GS_Session> session,
                                                 AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression);

        /**
         * Generate binary expression
         * @param session Session
         * @param binaryExpression Binary expression
         * @return Generated binary expression
         */
        Ptr<llvm::Value> GenerateBinaryExpression(LRef<Driver::GS_Session> session,
                                                  AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression);

        /**
         * Generate array expression
         * @param session Session
         * @param arrayExpression Array expression
         * @return Generated array expression
         */
        Ptr<llvm::Value> GenerateArrayExpression(LRef<Driver::GS_Session> session,
                                                 AST::NodePtrLRef<AST::GS_ArrayExpression> arrayExpression);

        /**
         * Generate variable using expression
         * @param session Session
         * @param variableUsingExpression Variable using expression
         * @return Generated variable using expression
         */
        Ptr<llvm::Value> GenerateVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                         AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression);

        /**
         * Generate function calling expression
         * @param session Session
         * @param functionCallingExpression Function calling expression
         * @return Generated function calling expression
         */
        Ptr<llvm::Value> GenerateFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                           AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression);

    private:

        /**
         * Getter for LLVM context
         * @return LLVM context
         */
        LRef<llvm::LLVMContext> GetContext();

        /**
         * Getter for LLVM IR module
         * @return LLVM IR module
         */
        LRef<llvm::Module> GetModule();

    private:

        /**
         * LLVM code holder
         */
        LRef<GS_LLVMCodeHolder> _codeHolder;

        /**
         * LLVM IR builder
         */
        llvm::IRBuilder<> _builder;
    };

}

#endif //GSLANGUAGE_GS_LLVMCGVISITOR_H
