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
     * Class for visiting AST nodes without result
     */
    class GS_Visitor {
    public:

        /**
         * Visit node
         * @param node Node
         * @return
         */
        virtual Void VisitNode(LRef<GSNodePtr> node);

        /**
         * Visit declaration
         * @param declaration Declaration
         * @return
         */
        virtual Void VisitDeclaration(LRef<GSDeclarationPtr> declaration);

        /**
         * Visit statement
         * @param statement Statement
         * @return
         */
        virtual Void VisitStatement(LRef<GSStatementPtr> statement);

        /**
         * Visit expression
         * @param expression Expression
         * @return
         */
        virtual Void VisitExpression(LRef<GSExpressionPtr> expression);

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        virtual Void VisitTranslationUnitDeclaration(LRef<SharedPtr<GS_TranslationUnitDeclaration>> translationUnitDeclaration);

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return
         */
        virtual Void VisitFunctionDeclaration(LRef<SharedPtr<GS_FunctionDeclaration>> functionDeclaration);

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return
         */
        virtual Void VisitVariableDeclarationStatement(LRef<SharedPtr<GS_VariableDeclarationStatement>> variableDeclarationStatement);

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return
         */
        virtual Void VisitAssignmentStatement(LRef<SharedPtr<GS_AssignmentStatement>> assignmentStatement);

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return
         */
        virtual Void VisitExpressionStatement(LRef<SharedPtr<GS_ExpressionStatement>> expressionStatement);

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return
         */
        virtual Void VisitConstantExpression(LRef<SharedPtr<GS_ConstantExpression>> constantExpression);

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return
         */
        virtual Void VisitUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression);

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return
         */
        virtual Void VisitBinaryExpression(LRef<SharedPtr<GS_BinaryExpression>> binaryExpression);

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return
         */
        virtual Void VisitVariableUsingExpression(LRef<SharedPtr<GS_VariableUsingExpression>> variableUsingExpression);

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return
         */
        virtual Void VisitFunctionCallingExpression(LRef<SharedPtr<GS_FunctionCallingExpression>> functionCallingExpression);
    };

    /**
     * Class for transforming AST nodes with node result
     */
    class GS_Transformer {
    public:

        /**
         * Transform node
         * @param node Node
         * @return Transformed node
         */
        virtual GSNodePtr TransformNode(LRef<GSNodePtr> node);

        /**
         * Transform declaration
         * @param declaration Declaration
         * @return Transformed declaration
         */
        virtual GSNodePtr TransformDeclaration(LRef<GSDeclarationPtr> declaration);

        /**
         * Transform statement
         * @param statement Statement
         * @return Transformed statement
         */
        virtual GSNodePtr TransformStatement(LRef<GSStatementPtr> statement);

        /**
         * Transform expression
         * @param expression Expression
         * @return Transformed expression
         */
        virtual GSNodePtr TransformExpression(LRef<GSExpressionPtr> expression);

        /**
         * Transform translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return Transformed translation unit declaration
         */
        virtual GSNodePtr TransformTranslationUnitDeclaration(LRef<SharedPtr<GS_TranslationUnitDeclaration>> translationUnitDeclaration);

        /**
         * Transform function declaration
         * @param functionDeclaration Function declaration
         * @return Transformed function declaration
         */
        virtual GSNodePtr TransformFunctionDeclaration(LRef<SharedPtr<GS_FunctionDeclaration>> functionDeclaration);

        /**
         * Transform variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return Transformed variable declaration statement
         */
        virtual GSNodePtr TransformVariableDeclarationStatement(LRef<SharedPtr<GS_VariableDeclarationStatement>> variableDeclarationStatement);

        /**
         * Transform assignment statement
         * @param assignmentStatement Assignment statement
         * @return Transformed assignment statement
         */
        virtual GSNodePtr TransformAssignmentStatement(LRef<SharedPtr<GS_AssignmentStatement>> assignmentStatement);

        /**
         * Transform expression statement
         * @param expressionStatement Expression statement
         * @return Transformed expression statement
         */
        virtual GSNodePtr TransformExpressionStatement(LRef<SharedPtr<GS_ExpressionStatement>> expressionStatement);

        /**
         * Transform constant expression
         * @param constantExpression Constant expression
         * @return Transformed constant expression
         */
        virtual GSNodePtr TransformConstantExpression(LRef<SharedPtr<GS_ConstantExpression>> constantExpression);

        /**
         * Transform unary expression
         * @param unaryExpression Unary expression
         * @return Transformed unary expression
         */
        virtual GSNodePtr TransformUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression);

        /**
         * Transform binary expression
         * @param binaryExpression Binary expression
         * @return Transformed binary expression
         */
        virtual GSNodePtr TransformBinaryExpression(LRef<SharedPtr<GS_BinaryExpression>> binaryExpression);

        /**
         * Transform variable using expression
         * @param variableUsingExpression Variable using expression
         * @return Transformed variable using expression
         */
        virtual GSNodePtr TransformVariableUsingExpression(LRef<SharedPtr<GS_VariableUsingExpression>> variableUsingExpression);

        /**
         * Transform function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Transformed function calling expression
         */
        virtual GSNodePtr TransformFunctionCallingExpression(LRef<SharedPtr<GS_FunctionCallingExpression>> functionCallingExpression);
    };

}

#endif //GSLANGUAGE_GS_VISITOR_H
