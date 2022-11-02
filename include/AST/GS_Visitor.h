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

        /**
         * Class for visiting AST nodes without result
         */
        class GS_Visitor {
        public:

            /**
             * Default visit node
             * @param node Node
             * @param session Session
             * @return
             */
            Void SuperNode(LRef<GSNodePtr> node,
                           LRef<Driver::GS_Session> session);

            /**
             * Default visit declaration
             * @param declaration Declaration
             * @param session Session
             * @return
             */
            Void SuperDeclaration(LRef<GSDeclarationPtr> declaration,
                                  LRef<Driver::GS_Session> session);

            /**
             * Default visit statement
             * @param statement Statement
             * @param session Session
             * @return
             */
            Void SuperStatement(LRef<GSStatementPtr> statement,
                                LRef<Driver::GS_Session> session);

            /**
             * Default visit expression
             * @param expression Expression
             * @param session Session
             * @return
             */
            Void SuperExpression(LRef<GSExpressionPtr> expression,
                                 LRef<Driver::GS_Session> session);

            /**
             * Default visit translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param session Session
             * @return
             */
            Void SuperTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                 LRef<Driver::GS_Session> session);

            /**
             * Default visit function declaration
             * @param functionDeclaration Function declaration
             * @param session Session
             * @return
             */
            Void SuperFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                          LRef<Driver::GS_Session> session);

            /**
             * Default visit variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param session Session
             * @return
             */
            Void SuperVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                   LRef<Driver::GS_Session> session);

            /**
             * Default visit assignment statement
             * @param assignmentStatement Assignment statement
             * @param session Session
             * @return
             */
            Void SuperAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                          LRef<Driver::GS_Session> session);

            /**
             * Default visit expression statement
             * @param expressionStatement Expression statement
             * @param session Session
             * @return
             */
            Void SuperExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                          LRef<Driver::GS_Session> session);

            /**
             * Default visit constant expression
             * @param constantExpression Constant expression
             * @param session Session
             * @return
             */
            Void SuperConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                         LRef<Driver::GS_Session> session);

            /**
             * Default visit unary expression
             * @param unaryExpression Unary expression
             * @param session Session
             * @return
             */
            Void SuperUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                      LRef<Driver::GS_Session> session);

            /**
             * Default visit binary expression
             * @param binaryExpression Binary expression
             * @param session Session
             * @return
             */
            Void SuperBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                       LRef<Driver::GS_Session> session);

            /**
             * Default visit array expression
             * @param arrayExpression Array expression
             * @param session Session
             * @return
             */
            Void SuperArrayExpression(NodePtrLRef<GS_ArrayExpression> arrayExpression,
                                      LRef<Driver::GS_Session> session);

            /**
             * Default visit variable using expression
             * @param variableUsingExpression Variable using expression
             * @param session Session
             * @return
             */
            Void SuperVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                              LRef<Driver::GS_Session> session);

            /**
             * Default visit function calling expression
             * @param functionCallingExpression Function calling expression
             * @param session Session
             * @return
             */
            Void SuperFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                LRef<Driver::GS_Session> session);

        public:

            /**
             * Visit node
             * @param node Node
             * @param session Session
             * @return
             */
            virtual Void VisitNode(LRef<GSNodePtr> node,
                                   LRef<Driver::GS_Session> session);

            /**
             * Visit declaration
             * @param declaration Declaration
             * @param session Session
             * @return
             */
            virtual Void VisitDeclaration(LRef<GSDeclarationPtr> declaration,
                                          LRef<Driver::GS_Session> session);

            /**
             * Visit statement
             * @param statement Statement
             * @param session Session
             * @return
             */
            virtual Void VisitStatement(LRef<GSStatementPtr> statement,
                                        LRef<Driver::GS_Session> session);

            /**
             * Visit expression
             * @param expression Expression
             * @param session Session
             * @return
             */
            virtual Void VisitExpression(LRef<GSExpressionPtr> expression,
                                         LRef<Driver::GS_Session> session);

            /**
             * Visit translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @param session Session
             * @return
             */
            virtual Void VisitTranslationUnitDeclaration(NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                         LRef<Driver::GS_Session> session);

            /**
             * Visit function declaration
             * @param functionDeclaration Function declaration
             * @param session Session
             * @return
             */
            virtual Void VisitFunctionDeclaration(NodePtrLRef<GS_FunctionDeclaration> functionDeclaration,
                                                  LRef<Driver::GS_Session> session);

            /**
             * Visit variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @param session Session
             * @return
             */
            virtual Void VisitVariableDeclarationStatement(NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                           LRef<Driver::GS_Session> session);

            /**
             * Visit assignment statement
             * @param assignmentStatement Assignment statement
             * @param session Session
             * @return
             */
            virtual Void VisitAssignmentStatement(NodePtrLRef<GS_AssignmentStatement> assignmentStatement,
                                                  LRef<Driver::GS_Session> session);

            /**
             * Visit expression statement
             * @param expressionStatement Expression statement
             * @param session Session
             * @return
             */
            virtual Void VisitExpressionStatement(NodePtrLRef<GS_ExpressionStatement> expressionStatement,
                                                  LRef<Driver::GS_Session> session);

            /**
             * Visit constant expression
             * @param constantExpression Constant expression
             * @param session Session
             * @return
             */
            virtual Void VisitConstantExpression(NodePtrLRef<GS_ConstantExpression> constantExpression,
                                                 LRef<Driver::GS_Session> session);

            /**
             * Visit unary expression
             * @param unaryExpression Unary expression
             * @param session Session
             * @return
             */
            virtual Void VisitUnaryExpression(NodePtrLRef<GS_UnaryExpression> unaryExpression,
                                              LRef<Driver::GS_Session> session);

            /**
             * Visit binary expression
             * @param binaryExpression Binary expression
             * @param session Session
             * @return
             */
            virtual Void VisitBinaryExpression(NodePtrLRef<GS_BinaryExpression> binaryExpression,
                                               LRef<Driver::GS_Session> session);

            /**
             * Visit array expression
             * @param arrayExpression Array expression
             * @param session Session
             * @return
             */
            virtual Void VisitArrayExpression(NodePtrLRef<GS_ArrayExpression> arrayExpression,
                                               LRef<Driver::GS_Session> session);

            /**
             * Visit variable using expression
             * @param variableUsingExpression Variable using expression
             * @param session Session
             * @return
             */
            virtual Void VisitVariableUsingExpression(NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression,
                                                      LRef<Driver::GS_Session> session);

            /**
             * Visit function calling expression
             * @param functionCallingExpression Function calling expression
             * @param session Session
             * @return
             */
            virtual Void VisitFunctionCallingExpression(NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression,
                                                        LRef<Driver::GS_Session> session);
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
