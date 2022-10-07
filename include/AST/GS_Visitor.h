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

namespace GSLanguageCompiler {

    namespace Driver {

        class GS_Context;

        using GSContextPtr = std::shared_ptr<GS_Context>;

    }

    namespace AST {

        /**
         * Class for visiting AST nodes without result
         */
        class GS_Visitor {
        public:

            /**
             * Default visit node
             * @param node Node
             * @param context Context
             * @return
             */
            Void SuperNode(LRef<GSNodePtr> node,
                           LRef<Driver::GSContextPtr> context);

            /**
             * Default visit declaration
             * @param declaration Declaration
             * @param context Context
             * @return
             */
            Void SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                  LRef<Driver::GSContextPtr> context);

            /**
             * Default visit statement
             * @param statement Statement
             * @param context Context
             * @return
             */
            Void SuperStatement(LRef<GSStatementPtr> statement,
                                LRef<Driver::GSContextPtr> context);

            /**
             * Default visit expression
             * @param expression Expression
             * @param context Context
             * @return
             */
            Void SuperExpression(LRef<GSExpressionPtr> expression,
                                 LRef<Driver::GSContextPtr> context);

            /**
             * Default visit translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param context Context
             * @return
             */
            Void SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                 LRef<Driver::GSContextPtr> context);

            /**
             * Default visit function declaration
             * @param functionDeclaration Function declaration
             * @param context Context
             * @return
             */
            Void SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                          LRef<Driver::GSContextPtr> context);

            /**
             * Default visit variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param context Context
             * @return
             */
            Void SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                   LRef<Driver::GSContextPtr> context);

            /**
             * Default visit assignment statement
             * @param assignmentStatement Assignment statement
             * @param context Context
             * @return
             */
            Void SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                          LRef<Driver::GSContextPtr> context);

            /**
             * Default visit expression statement
             * @param expressionStatement Expression statement
             * @param context Context
             * @return
             */
            Void SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                          LRef<Driver::GSContextPtr> context);

            /**
             * Default visit constant expression
             * @param constantExpression Constant expression
             * @param context Context
             * @return
             */
            Void SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                         LRef<Driver::GSContextPtr> context);

            /**
             * Default visit unary expression
             * @param unaryExpression Unary expression
             * @param context Context
             * @return
             */
            Void SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                      LRef<Driver::GSContextPtr> context);

            /**
             * Default visit binary expression
             * @param binaryExpression Binary expression
             * @param context Context
             * @return
             */
            Void SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                       LRef<Driver::GSContextPtr> context);

            /**
             * Default visit variable using expression
             * @param variableUsingExpression Variable using expression
             * @param context Context
             * @return
             */
            Void SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                              LRef<Driver::GSContextPtr> context);

            /**
             * Default visit function calling expression
             * @param functionCallingExpression Function calling expression
             * @param context Context
             * @return
             */
            Void SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                LRef<Driver::GSContextPtr> context);

        public:

            /**
             * Visit node
             * @param node Node
             * @param context Context
             * @return
             */
            virtual Void VisitNode(LRef<GSNodePtr> node,
                                   LRef<Driver::GSContextPtr> context);

            /**
             * Visit declaration
             * @param declaration Declaration
             * @param context Context
             * @return
             */
            virtual Void VisitDeclaration(LRef<GSDeclarationPtr> declaration,
                                          LRef<Driver::GSContextPtr> context);

            /**
             * Visit statement
             * @param statement Statement
             * @param context Context
             * @return
             */
            virtual Void VisitStatement(LRef<GSStatementPtr> statement,
                                        LRef<Driver::GSContextPtr> context);

            /**
             * Visit expression
             * @param expression Expression
             * @param context Context
             * @return
             */
            virtual Void VisitExpression(LRef<GSExpressionPtr> expression,
                                         LRef<Driver::GSContextPtr> context);

            /**
             * Visit translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param context Context
             * @return
             */
            virtual Void VisitTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                         LRef<Driver::GSContextPtr> context);

            /**
             * Visit function declaration
             * @param functionDeclaration Function declaration
             * @param context Context
             * @return
             */
            virtual Void VisitFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                  LRef<Driver::GSContextPtr> context);

            /**
             * Visit variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param context Context
             * @return
             */
            virtual Void VisitVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                           LRef<Driver::GSContextPtr> context);

            /**
             * Visit assignment statement
             * @param assignmentStatement Assignment statement
             * @param context Context
             * @return
             */
            virtual Void VisitAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                  LRef<Driver::GSContextPtr> context);

            /**
             * Visit expression statement
             * @param expressionStatement Expression statement
             * @param context Context
             * @return
             */
            virtual Void VisitExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                  LRef<Driver::GSContextPtr> context);

            /**
             * Visit constant expression
             * @param constantExpression Constant expression
             * @param context Context
             * @return
             */
            virtual Void VisitConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                 LRef<Driver::GSContextPtr> context);

            /**
             * Visit unary expression
             * @param unaryExpression Unary expression
             * @param context Context
             * @return
             */
            virtual Void VisitUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                              LRef<Driver::GSContextPtr> context);

            /**
             * Visit binary expression
             * @param binaryExpression Binary expression
             * @param context Context
             * @return
             */
            virtual Void VisitBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                               LRef<Driver::GSContextPtr> context);

            /**
             * Visit variable using expression
             * @param variableUsingExpression Variable using expression
             * @param context Context
             * @return
             */
            virtual Void VisitVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                      LRef<Driver::GSContextPtr> context);

            /**
             * Visit function calling expression
             * @param functionCallingExpression Function calling expression
             * @param context Context
             * @return
             */
            virtual Void VisitFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                        LRef<Driver::GSContextPtr> context);
        };

        /**
         * Class for transforming AST nodes with node result
         */
        class GS_Transformer {
        public:

            /**
             * Default transform node
             * @param node Node
             * @param context Context
             * @return Transformed node
             */
            GSNodePtr SuperNode(LRef<GSNodePtr> node,
                                LRef<Driver::GSContextPtr> context);

            /**
             * Default transform declaration
             * @param declaration Declaration
             * @param context Context
             * @return Transformed declaration
             */
            GSNodePtr SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                       LRef<Driver::GSContextPtr> context);

            /**
             * Default transform statement
             * @param statement Statement
             * @param context Context
             * @return Transformed statement
             */
            GSNodePtr SuperStatement(LRef<GSStatementPtr> statement,
                                     LRef<Driver::GSContextPtr> context);

            /**
             * Default transform expression
             * @param expression Expression
             * @param context Context
             * @return Transformed expression
             */
            GSNodePtr SuperExpression(LRef<GSExpressionPtr> expression,
                                      LRef<Driver::GSContextPtr> context);

            /**
             * Default transform translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param context Context
             * @return Transformed translation unit declaration
             */
            GSNodePtr SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                      LRef<Driver::GSContextPtr> context);

            /**
             * Default transform function declaration
             * @param functionDeclaration Function declaration
             * @param context Context
             * @return Transformed function declaration
             */
            GSNodePtr SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                               LRef<Driver::GSContextPtr> context);

            /**
             * Default transform variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param context Context
             * @return Transformed variable declaration statement
             */
            GSNodePtr SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                        LRef<Driver::GSContextPtr> context);

            /**
             * Default transform assignment statement
             * @param assignmentStatement Assignment statement
             * @param context Context
             * @return Transformed assignment statement
             */
            GSNodePtr SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                               LRef<Driver::GSContextPtr> context);

            /**
             * Default transform expression statement
             * @param expressionStatement Expression statement
             * @param context Context
             * @return Transformed expression statement
             */
            GSNodePtr SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                               LRef<Driver::GSContextPtr> context);

            /**
             * Default transform constant expression
             * @param constantExpression Constant expression
             * @param context Context
             * @return Transformed constant expression
             */
            GSNodePtr SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                              LRef<Driver::GSContextPtr> context);

            /**
             * Default transform unary expression
             * @param unaryExpression Unary expression
             * @param context Context
             * @return Transformed unary expression
             */
            GSNodePtr SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                           LRef<Driver::GSContextPtr> context);

            /**
             * Default transform binary expression
             * @param binaryExpression Binary expression
             * @param context Context
             * @return Transformed binary expression
             */
            GSNodePtr SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                            LRef<Driver::GSContextPtr> context);

            /**
             * Default transform variable using expression
             * @param variableUsingExpression Variable using expression
             * @param context Context
             * @return Transformed variable using expression
             */
            GSNodePtr SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                   LRef<Driver::GSContextPtr> context);

            /**
             * Default transform function calling expression
             * @param functionCallingExpression Function calling expression
             * @param context Context
             * @return Transformed function calling expression
             */
            GSNodePtr SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                     LRef<Driver::GSContextPtr> context);

        public:

            /**
             * Transform node
             * @param node Node
             * @param context Context
             * @return Transformed node
             */
            virtual GSNodePtr TransformNode(LRef<GSNodePtr> node,
                                            LRef<Driver::GSContextPtr> context);

            /**
             * Transform declaration
             * @param declaration Declaration
             * @param context Context
             * @return Transformed declaration
             */
            virtual GSNodePtr TransformDeclaration(LRef<GSDeclarationPtr> declaration,
                                                   LRef<Driver::GSContextPtr> context);

            /**
             * Transform statement
             * @param statement Statement
             * @param context Context
             * @return Transformed statement
             */
            virtual GSNodePtr TransformStatement(LRef<GSStatementPtr> statement,
                                                 LRef<Driver::GSContextPtr> context);

            /**
             * Transform expression
             * @param expression Expression
             * @param context Context
             * @return Transformed expression
             */
            virtual GSNodePtr TransformExpression(LRef<GSExpressionPtr> expression,
                                                  LRef<Driver::GSContextPtr> context);

            /**
             * Transform translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param context Context
             * @return Transformed translation unit declaration
             */
            virtual GSNodePtr TransformTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                                  LRef<Driver::GSContextPtr> context);

            /**
             * Transform function declaration
             * @param functionDeclaration Function declaration
             * @param context Context
             * @return Transformed function declaration
             */
            virtual GSNodePtr TransformFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                           LRef<Driver::GSContextPtr> context);

            /**
             * Transform variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param context Context
             * @return Transformed variable declaration statement
             */
            virtual GSNodePtr TransformVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                                    LRef<Driver::GSContextPtr> context);

            /**
             * Transform assignment statement
             * @param assignmentStatement Assignment statement
             * @param context Context
             * @return Transformed assignment statement
             */
            virtual GSNodePtr TransformAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                           LRef<Driver::GSContextPtr> context);

            /**
             * Transform expression statement
             * @param expressionStatement Expression statement
             * @param context Context
             * @return Transformed expression statement
             */
            virtual GSNodePtr TransformExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                           LRef<Driver::GSContextPtr> context);

            /**
             * Transform constant expression
             * @param constantExpression Constant expression
             * @param context Context
             * @return Transformed constant expression
             */
            virtual GSNodePtr TransformConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                          LRef<Driver::GSContextPtr> context);

            /**
             * Transform unary expression
             * @param unaryExpression Unary expression
             * @param context Context
             * @return Transformed unary expression
             */
            virtual GSNodePtr TransformUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                                       LRef<Driver::GSContextPtr> context);

            /**
             * Transform binary expression
             * @param binaryExpression Binary expression
             * @param context Context
             * @return Transformed binary expression
             */
            virtual GSNodePtr TransformBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                                        LRef<Driver::GSContextPtr> context);

            /**
             * Transform variable using expression
             * @param variableUsingExpression Variable using expression
             * @param context Context
             * @return Transformed variable using expression
             */
            virtual GSNodePtr TransformVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                               LRef<Driver::GSContextPtr> context);

            /**
             * Transform function calling expression
             * @param functionCallingExpression Function calling expression
             * @param context Context
             * @return Transformed function calling expression
             */
            virtual GSNodePtr TransformFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                                 LRef<Driver::GSContextPtr> context);
        };

    }

}

#endif //GSLANGUAGE_GS_VISITOR_H
