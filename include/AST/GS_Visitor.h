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
#include <AST/Expressions/GS_ArrayExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler {

    namespace Driver {

        class GS_Session;

    }

    namespace AST {

        // TODO update visiting and transforming AST API

        /**
         * Class for visiting AST nodes without result
         */
        class GS_Visitor {
        public:

            /**
             * Default visit node
             * @param session Session
             * @param node Node
             * @return Void return
             */
            Void SuperNode(LRef<Driver::GS_Session> session,
                           LRef<GSNodePtr> node);

            /**
             * Default visit declaration
             * @param session Session
             * @param declaration Declaration
             * @return Void return
             */
            Void SuperDeclaration(LRef<Driver::GS_Session> session,
                                  LRef<GSDeclarationPtr> declaration);

            /**
             * Default visit statement
             * @param session Session
             * @param statement Statement
             * @return Void return
             */
            Void SuperStatement(LRef<Driver::GS_Session> session,
                                LRef<GSStatementPtr> statement);

            /**
             * Default visit expression
             * @param session Session
             * @param expression Expression
             * @return Void return
             */
            Void SuperExpression(LRef<Driver::GS_Session> session,
                                 LRef<GSExpressionPtr> expression);

            /**
             * Default visit translation unit declaration
             * @param session Session
             * @param translationUnitDeclaration Translation unit declaration
             * @return Void return
             */
            Void SuperTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                 NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration);

            /**
             * Default visit function declaration
             * @param session Session
             * @param functionDeclaration Function declaration
             * @return Void return
             */
            Void SuperFunctionDeclaration(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_FunctionDeclaration> functionDeclaration);

            /**
             * Default visit variable declaration statement
             * @param session Session
             * @param variableDeclarationStatement Variable declaration statement
             * @return Void return
             */
            Void SuperVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement);

            /**
             * Default visit assignment statement
             * @param session Session
             * @param assignmentStatement Assignment statement
             * @return Void return
             */
            Void SuperAssignmentStatement(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_AssignmentStatement> assignmentStatement);

            /**
             * Default visit expression statement
             * @param session Session
             * @param expressionStatement Expression statement
             * @return Void return
             */
            Void SuperExpressionStatement(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ExpressionStatement> expressionStatement);

            /**
             * Default visit constant expression
             * @param session Session
             * @param constantExpression Constant expression
             * @return Void return
             */
            Void SuperConstantExpression(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_ConstantExpression> constantExpression);

            /**
             * Default visit unary expression
             * @param session Session
             * @param unaryExpression Unary expression
             * @return Void return
             */
            Void SuperUnaryExpression(LRef<Driver::GS_Session> session,
                                      NodePtrLRef<GS_UnaryExpression> unaryExpression);

            /**
             * Default visit binary expression
             * @param session Session
             * @param binaryExpression Binary expression
             * @return Void return
             */
            Void SuperBinaryExpression(LRef<Driver::GS_Session> session,
                                       NodePtrLRef<GS_BinaryExpression> binaryExpression);

            /**
             * Default visit array expression
             * @param session Session
             * @param arrayExpression Array expression
             * @return Void return
             */
            Void SuperArrayExpression(LRef<Driver::GS_Session> session,
                                      NodePtrLRef<GS_ArrayExpression> arrayExpression);

            /**
             * Default visit variable using expression
             * @param session Session
             * @param variableUsingExpression Variable using expression
             * @return Void return
             */
            Void SuperVariableUsingExpression(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression);

            /**
             * Default visit function calling expression
             * @param session Session
             * @param functionCallingExpression Function calling expression
             * @return Void return
             */
            Void SuperFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression);

        public:

            /**
             * Visit node
             * @param session Session
             * @param node Node
             * @return Void return
             */
            virtual Void VisitNode(LRef<Driver::GS_Session> session,
                                   LRef<GSNodePtr> node);

            /**
             * Visit declaration
             * @param session Session
             * @param declaration Declaration
             * @return Void return
             */
            virtual Void VisitDeclaration(LRef<Driver::GS_Session> session,
                                          LRef<GSDeclarationPtr> declaration);

            /**
             * Visit statement
             * @param session Session
             * @param statement Statement
             * @return Void return
             */
            virtual Void VisitStatement(LRef<Driver::GS_Session> session,
                                        LRef<GSStatementPtr> statement);

            /**
             * Visit expression
             * @param session Session
             * @param expression Expression
             * @return Void return
             */
            virtual Void VisitExpression(LRef<Driver::GS_Session> session,
                                         LRef<GSExpressionPtr> expression);

            /**
             * Visit translation unit declaration
             * @param session Session
             * @param translationUnitDeclaration Translation unit declaration
             * @return Void return
             */
            virtual Void VisitTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                         NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration);

            /**
             * Visit function declaration
             * @param session Session
             * @param functionDeclaration Function declaration
             * @return Void return
             */
            virtual Void VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_FunctionDeclaration> functionDeclaration);

            /**
             * Visit variable declaration statement
             * @param session Session
             * @param variableDeclarationStatement Variable declaration statement
             * @return Void return
             */
            virtual Void VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement);

            /**
             * Visit assignment statement
             * @param session Session
             * @param assignmentStatement Assignment statement
             * @return Void return
             */
            virtual Void VisitAssignmentStatement(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_AssignmentStatement> assignmentStatement);

            /**
             * Visit expression statement
             * @param session Session
             * @param expressionStatement Expression statement
             * @return Void return
             */
            virtual Void VisitExpressionStatement(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_ExpressionStatement> expressionStatement);

            /**
             * Visit constant expression
             * @param session Session
             * @param constantExpression Constant expression
             * @return Void return
             */
            virtual Void VisitConstantExpression(LRef<Driver::GS_Session> session,
                                                 NodePtrLRef<GS_ConstantExpression> constantExpression);

            /**
             * Visit unary expression
             * @param session Session
             * @param unaryExpression Unary expression
             * @return Void return
             */
            virtual Void VisitUnaryExpression(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_UnaryExpression> unaryExpression);

            /**
             * Visit binary expression
             * @param session Session
             * @param binaryExpression Binary expression
             * @return Void return
             */
            virtual Void VisitBinaryExpression(LRef<Driver::GS_Session> session,
                                               NodePtrLRef<GS_BinaryExpression> binaryExpression);

            /**
             * Visit array expression
             * @param session Session
             * @param arrayExpression Array expression
             * @return Void return
             */
            virtual Void VisitArrayExpression(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_ArrayExpression> arrayExpression);

            /**
             * Visit variable using expression
             * @param session Session
             * @param variableUsingExpression Variable using expression
             * @return Void return
             */
            virtual Void VisitVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression);

            /**
             * Visit function calling expression
             * @param session Session
             * @param functionCallingExpression Function calling expression
             * @return Void return
             */
            virtual Void VisitFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                        NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression);
        };

        /**
         * Class for transforming AST nodes with node result
         */
        class GS_Transformer {
        public:

            /**
             * Default transform node
             * @param node Node
             * @param session Session
             * @return Transformed node
             */
            GSNodePtr SuperNode(LRef<GSNodePtr> node,
                                LRef<Driver::GS_Session> session);

            /**
             * Default transform declaration
             * @param declaration Declaration
             * @param session Session
             * @return Transformed declaration
             */
            GSNodePtr SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                       LRef<Driver::GS_Session> session);

            /**
             * Default transform statement
             * @param statement Statement
             * @param session Session
             * @return Transformed statement
             */
            GSNodePtr SuperStatement(LRef<GSStatementPtr> statement,
                                     LRef<Driver::GS_Session> session);

            /**
             * Default transform expression
             * @param expression Expression
             * @param session Session
             * @return Transformed expression
             */
            GSNodePtr SuperExpression(LRef<GSExpressionPtr> expression,
                                      LRef<Driver::GS_Session> session);

            /**
             * Default transform translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param session Session
             * @return Transformed translation unit declaration
             */
            GSNodePtr SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                      LRef<Driver::GS_Session> session);

            /**
             * Default transform function declaration
             * @param functionDeclaration Function declaration
             * @param session Session
             * @return Transformed function declaration
             */
            GSNodePtr SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                               LRef<Driver::GS_Session> session);

            /**
             * Default transform variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param session Session
             * @return Transformed variable declaration statement
             */
            GSNodePtr SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                        LRef<Driver::GS_Session> session);

            /**
             * Default transform assignment statement
             * @param assignmentStatement Assignment statement
             * @param session Session
             * @return Transformed assignment statement
             */
            GSNodePtr SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                               LRef<Driver::GS_Session> session);

            /**
             * Default transform expression statement
             * @param expressionStatement Expression statement
             * @param session Session
             * @return Transformed expression statement
             */
            GSNodePtr SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                               LRef<Driver::GS_Session> session);

            /**
             * Default transform constant expression
             * @param constantExpression Constant expression
             * @param session Session
             * @return Transformed constant expression
             */
            GSNodePtr SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                              LRef<Driver::GS_Session> session);

            /**
             * Default transform unary expression
             * @param unaryExpression Unary expression
             * @param session Session
             * @return Transformed unary expression
             */
            GSNodePtr SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                           LRef<Driver::GS_Session> session);

            /**
             * Default transform binary expression
             * @param binaryExpression Binary expression
             * @param session Session
             * @return Transformed binary expression
             */
            GSNodePtr SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                            LRef<Driver::GS_Session> session);

            /**
             * Default transform array expression
             * @param arrayExpression Array expression
             * @param session Session
             * @return Transformed array expression
             */
            GSNodePtr SuperArrayExpression(NodePtrLRef<GS_ArrayExpression> arrayExpression,
                                            LRef<Driver::GS_Session> session);

            /**
             * Default transform variable using expression
             * @param variableUsingExpression Variable using expression
             * @param session Session
             * @return Transformed variable using expression
             */
            GSNodePtr SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                   LRef<Driver::GS_Session> session);

            /**
             * Default transform function calling expression
             * @param functionCallingExpression Function calling expression
             * @param session Session
             * @return Transformed function calling expression
             */
            GSNodePtr SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                     LRef<Driver::GS_Session> session);

        public:

            /**
             * Transform node
             * @param node Node
             * @param session Session
             * @return Transformed node
             */
            virtual GSNodePtr TransformNode(LRef<GSNodePtr> node,
                                            LRef<Driver::GS_Session> session);

            /**
             * Transform declaration
             * @param declaration Declaration
             * @param session Session
             * @return Transformed declaration
             */
            virtual GSNodePtr TransformDeclaration(LRef<GSDeclarationPtr> declaration,
                                                   LRef<Driver::GS_Session> session);

            /**
             * Transform statement
             * @param statement Statement
             * @param session Session
             * @return Transformed statement
             */
            virtual GSNodePtr TransformStatement(LRef<GSStatementPtr> statement,
                                                 LRef<Driver::GS_Session> session);

            /**
             * Transform expression
             * @param expression Expression
             * @param session Session
             * @return Transformed expression
             */
            virtual GSNodePtr TransformExpression(LRef<GSExpressionPtr> expression,
                                                  LRef<Driver::GS_Session> session);

            /**
             * Transform translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param session Session
             * @return Transformed translation unit declaration
             */
            virtual GSNodePtr TransformTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                                  LRef<Driver::GS_Session> session);

            /**
             * Transform function declaration
             * @param functionDeclaration Function declaration
             * @param session Session
             * @return Transformed function declaration
             */
            virtual GSNodePtr TransformFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                           LRef<Driver::GS_Session> session);

            /**
             * Transform variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param session Session
             * @return Transformed variable declaration statement
             */
            virtual GSNodePtr TransformVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                                    LRef<Driver::GS_Session> session);

            /**
             * Transform assignment statement
             * @param assignmentStatement Assignment statement
             * @param session Session
             * @return Transformed assignment statement
             */
            virtual GSNodePtr TransformAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                           LRef<Driver::GS_Session> session);

            /**
             * Transform expression statement
             * @param expressionStatement Expression statement
             * @param session Session
             * @return Transformed expression statement
             */
            virtual GSNodePtr TransformExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                           LRef<Driver::GS_Session> session);

            /**
             * Transform constant expression
             * @param constantExpression Constant expression
             * @param session Session
             * @return Transformed constant expression
             */
            virtual GSNodePtr TransformConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                          LRef<Driver::GS_Session> session);

            /**
             * Transform unary expression
             * @param unaryExpression Unary expression
             * @param session Session
             * @return Transformed unary expression
             */
            virtual GSNodePtr TransformUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                                       LRef<Driver::GS_Session> session);

            /**
             * Transform binary expression
             * @param binaryExpression Binary expression
             * @param session Session
             * @return Transformed binary expression
             */
            virtual GSNodePtr TransformBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                                        LRef<Driver::GS_Session> session);

            /**
             * Transform array expression
             * @param arrayExpression Array expression
             * @param session Session
             * @return Transformed array expression
             */
            virtual GSNodePtr TransformArrayExpression(NodePtrLRef<GS_ArrayExpression> arrayExpression,
                                                        LRef<Driver::GS_Session> session);

            /**
             * Transform variable using expression
             * @param variableUsingExpression Variable using expression
             * @param session Session
             * @return Transformed variable using expression
             */
            virtual GSNodePtr TransformVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                               LRef<Driver::GS_Session> session);

            /**
             * Transform function calling expression
             * @param functionCallingExpression Function calling expression
             * @param session Session
             * @return Transformed function calling expression
             */
            virtual GSNodePtr TransformFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                                 LRef<Driver::GS_Session> session);
        };

    }

}

#endif //GSLANGUAGE_GS_VISITOR_H
