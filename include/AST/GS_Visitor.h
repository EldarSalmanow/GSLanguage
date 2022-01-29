#ifndef GSLANGUAGE_GS_VISITOR_H
#define GSLANGUAGE_GS_VISITOR_H

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_ConstantExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler::AST {

    /**
     * Interface class for all AST visitors
     */
    template<typename T>
    class GS_Visitor {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Visitor() = default;

    public:

        /**
         * Visit node
         * @param node Node
         * @return Data
         */
        virtual T visit(ConstLRef<GSNodePtr> node) = 0;

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return Data
         */
        virtual T visit(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) = 0;

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return Data
         */
        virtual T visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) = 0;

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return Data
         */
        virtual T visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) = 0;

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return Data
         */
        virtual T visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) = 0;

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return Data
         */
        virtual T visit(SharedPtr<GS_ExpressionStatement> expressionStatement) = 0;

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return Data
         */
        virtual T visit(SharedPtr<GS_ConstantExpression> constantExpression) = 0;

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return Data
         */
        virtual T visit(SharedPtr<GS_UnaryExpression> unaryExpression) = 0;

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return Data
         */
        virtual T visit(SharedPtr<GS_BinaryExpression> binaryExpression) = 0;

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return Data
         */
        virtual T visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) = 0;

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Data
         */
        virtual T visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) = 0;
    };

    /**
     * Visitor ptr type
     */
    template<typename T>
    using GSVisitorPtr = SharedPtr<GS_Visitor<T>>;

    /**
     * Base class for all AST visitors
     */
    class GS_BaseVisitor : public GS_Visitor<Void> {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        ~GS_BaseVisitor() override;

    public:

        /**
         * Visit node
         * @param node Node
         * @return
         */
        Void visit(ConstLRef<GSNodePtr> node) override;

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        Void visit(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) override;

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return
         */
        Void visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) override;

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return
         */
        Void visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return
         */
        Void visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) override;

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return
         */
        Void visit(SharedPtr<GS_ExpressionStatement> expressionStatement) override;

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return
         */
        Void visit(SharedPtr<GS_ConstantExpression> constantExpression) override;

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return
         */
        Void visit(SharedPtr<GS_UnaryExpression> unaryExpression) override;

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return
         */
        Void visit(SharedPtr<GS_BinaryExpression> binaryExpression) override;

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return
         */
        Void visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) override;

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return
         */
        Void visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) override;
    };

}

#endif //GSLANGUAGE_GS_VISITOR_H
