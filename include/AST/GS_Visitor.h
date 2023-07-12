#ifndef GSLANGUAGE_GS_VISITOR_H
#define GSLANGUAGE_GS_VISITOR_H

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_IfStatement.h>
#include <AST/Statements/GS_ForStatement.h>
#include <AST/Statements/GS_WhileStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_ConstantExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_ArrayExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

namespace GSLanguageCompiler {

    namespace Driver {

        /**
         * Declaring compiler session for AST visitor and transformer
         */
        class GS_Session;

    }

    namespace AST {

        /**
         * Class for visiting AST nodes without result
         */
        class GS_Visitor {
        public:

            /*
             *
             * GS_Visitor PUBLIC DESTRUCTORS
             *
             */

            /**
             * Virtual destructor for supporting inheritance
             */
            virtual ~GS_Visitor();

        public:

            /*
             *
             * GS_Visitor PUBLIC METHODS
             *
             */

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
             * Default visit if statement
             * @param session Session
             * @param ifStatement If statement
             * @return Void return
             */
            Void SuperIfStatement(LRef<Driver::GS_Session> session,
                                  NodePtrLRef<GS_IfStatement> ifStatement);

            /**
             * Default visit for statement
             * @param session Session
             * @param forStatement For statement
             * @return Void return
             */
            Void SuperForStatement(LRef<Driver::GS_Session> session,
                                   NodePtrLRef<GS_ForStatement> forStatement);

            /**
             * Default visit while statement
             * @param session Session
             * @param whileStatement While statement
             * @return Void return
             */
            Void SuperWhileStatement(LRef<Driver::GS_Session> session,
                                     NodePtrLRef<GS_WhileStatement> whileStatement);

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

            /*
             *
             * GS_Visitor PUBLIC VIRTUAL METHODS
             *
             */

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
             * Visit if statement
             * @param session Session
             * @param ifStatement If statement
             * @return Void return
             */
            virtual Void VisitIfStatement(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_IfStatement> ifStatement);

            /**
             * Visit for statement
             * @param session Session
             * @param forStatement For statement
             * @return Void return
             */
            virtual Void VisitForStatement(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_ForStatement> forStatement);

            /**
             * Visit while statement
             * @param session Session
             * @param whileStatement While statement
             * @return Void return
             */
            virtual Void VisitWhileStatement(LRef<Driver::GS_Session> session,
                                             NodePtrLRef<GS_WhileStatement> whileStatement);

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

            /*
             *
             * GS_Transformer PUBLIC DESTRUCTORS
             *
             */

            /**
             * Virtual destructor for supporting inheritance
             */
            virtual ~GS_Transformer();

        public:

            /*
             *
             * GS_Transformer PUBLIC METHODS
             *
             */

            /**
             * Default transform node
             * @param session Session
             * @param node Node
             * @return Transformed node
             */
            GSNodePtr SuperNode(LRef<Driver::GS_Session> session,
                                LRef<GSNodePtr> node);

            /**
             * Default transform declaration
             * @param session Session
             * @param declaration Declaration
             * @return Transformed declaration
             */
            GSNodePtr SuperDeclaration(LRef<Driver::GS_Session> session,
                                       LRef<GSDeclarationPtr> declaration);

            /**
             * Default transform statement
             * @param session Session
             * @param statement Statement
             * @return Transformed statement
             */
            GSNodePtr SuperStatement(LRef<Driver::GS_Session> session,
                                     LRef<GSStatementPtr> statement);

            /**
             * Default transform expression
             * @param session Session
             * @param expression Expression
             * @return Transformed expression
             */
            GSNodePtr SuperExpression(LRef<Driver::GS_Session> session,
                                      LRef<GSExpressionPtr> expression);

            /**
             * Default transform translation unit declaration
             * @param session Session
             * @param translationUnitDeclaration Translation unit declaration
             * @return Transformed translation unit declaration
             */
            GSNodePtr SuperTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration);

            /**
             * Default transform function declaration
             * @param session Session
             * @param functionDeclaration Function declaration
             * @return Transformed function declaration
             */
            GSNodePtr SuperFunctionDeclaration(LRef<Driver::GS_Session> session,
                                               NodePtrLRef<GS_FunctionDeclaration> functionDeclaration);

            /**
             * Default transform variable declaration statement
             * @param session Session
             * @param variableDeclarationStatement Variable declaration statement
             * @return Transformed variable declaration statement
             */
            GSNodePtr SuperVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                        NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement);

            /**
             * Default transform assignment statement
             * @param session Session
             * @param assignmentStatement Assignment statement
             * @return Transformed assignment statement
             */
            GSNodePtr SuperAssignmentStatement(LRef<Driver::GS_Session> session,
                                               NodePtrLRef<GS_AssignmentStatement> assignmentStatement);

            /**
             * Default transform if statement
             * @param session Session
             * @param ifStatement If statement
             * @return Transformed if statement
             */
            GSNodePtr SuperIfStatement(LRef<Driver::GS_Session> session,
                                       NodePtrLRef<GS_IfStatement> ifStatement);

            /**
             * Default transform for statement
             * @param session Session
             * @param forStatement For statement
             * @return Transformed for statement
             */
            GSNodePtr SuperForStatement(LRef<Driver::GS_Session> session,
                                        NodePtrLRef<GS_ForStatement> forStatement);

            /**
             * Default transform while statement
             * @param session Session
             * @param whileStatement While statement
             * @return Transformed while statement
             */
            GSNodePtr SuperWhileStatement(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_WhileStatement> whileStatement);

            /**
             * Default transform expression statement
             * @param session Session
             * @param expressionStatement Expression statement
             * @return Transformed expression statement
             */
            GSNodePtr SuperExpressionStatement(LRef<Driver::GS_Session> session,
                                               NodePtrLRef<GS_ExpressionStatement> expressionStatement);

            /**
             * Default transform constant expression
             * @param session Session
             * @param constantExpression Constant expression
             * @return Transformed constant expression
             */
            GSNodePtr SuperConstantExpression(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_ConstantExpression> constantExpression);

            /**
             * Default transform unary expression
             * @param session Session
             * @param unaryExpression Unary expression
             * @return Transformed unary expression
             */
            GSNodePtr SuperUnaryExpression(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_UnaryExpression> unaryExpression);

            /**
             * Default transform binary expression
             * @param session Session
             * @param binaryExpression Binary expression
             * @return Transformed binary expression
             */
            GSNodePtr SuperBinaryExpression(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_BinaryExpression> binaryExpression);

            /**
             * Default transform array expression
             * @param session Session
             * @param arrayExpression Array expression
             * @return Transformed array expression
             */
            GSNodePtr SuperArrayExpression(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_ArrayExpression> arrayExpression);

            /**
             * Default transform variable using expression
             * @param session Session
             * @param variableUsingExpression Variable using expression
             * @return Transformed variable using expression
             */
            GSNodePtr SuperVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression);

            /**
             * Default transform function calling expression
             * @param session Session
             * @param functionCallingExpression Function calling expression
             * @return Transformed function calling expression
             */
            GSNodePtr SuperFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression);

        public:

            /*
             *
             * GS_Transformer PUBLIC VIRTUAL METHODS
             *
             */

            /**
             * Transform node
             * @param session Session
             * @param node Node
             * @return Transformed node
             */
            virtual GSNodePtr TransformNode(LRef<Driver::GS_Session> session,
                                            LRef<GSNodePtr> node);

            /**
             * Transform declaration
             * @param session Session
             * @param declaration Declaration
             * @return Transformed declaration
             */
            virtual GSNodePtr TransformDeclaration(LRef<Driver::GS_Session> session,
                                                   LRef<GSDeclarationPtr> declaration);

            /**
             * Transform statement
             * @param session Session
             * @param statement Statement
             * @return Transformed statement
             */
            virtual GSNodePtr TransformStatement(LRef<Driver::GS_Session> session,
                                                 LRef<GSStatementPtr> statement);

            /**
             * Transform expression
             * @param session Session
             * @param expression Expression
             * @return Transformed expression
             */
            virtual GSNodePtr TransformExpression(LRef<Driver::GS_Session> session,
                                                  LRef<GSExpressionPtr> expression);

            /**
             * Transform translation unit declaration
             * @param session Session
             * @param translationUnitDeclaration Translation unit declaration
             * @return Transformed translation unit declaration
             */
            virtual GSNodePtr TransformTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                                  NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration);

            /**
             * Transform function declaration
             * @param session Session
             * @param functionDeclaration Function declaration
             * @return Transformed function declaration
             */
            virtual GSNodePtr TransformFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_FunctionDeclaration> functionDeclaration);

            /**
             * Transform variable declaration statement
             * @param session Session
             * @param variableDeclarationStatement Variable declaration statement
             * @return Transformed variable declaration statement
             */
            virtual GSNodePtr TransformVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                    NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement);

            /**
             * Transform assignment statement
             * @param session Session
             * @param assignmentStatement Assignment statement
             * @return Transformed assignment statement
             */
            virtual GSNodePtr TransformAssignmentStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_AssignmentStatement> assignmentStatement);

            /**
             * Transform if statement
             * @param session Session
             * @param ifStatement If statement
             * @return Transformed if statement
             */
            virtual GSNodePtr TransformIfStatement(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_IfStatement> ifStatement);

            /**
             * Transform for statement
             * @param session Session
             * @param forStatement For statement
             * @return Transformed for statement
             */
            virtual GSNodePtr TransformForStatement(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_ForStatement> forStatement);

            /**
             * Transform while statement
             * @param session Session
             * @param whileStatement While statement
             * @return Transformed while statement
             */
            virtual GSNodePtr TransformWhileStatement(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_WhileStatement> whileStatement);

            /**
             * Transform expression statement
             * @param session Session
             * @param expressionStatement Expression statement
             * @return Transformed expression statement
             */
            virtual GSNodePtr TransformExpressionStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_ExpressionStatement> expressionStatement);

            /**
             * Transform constant expression
             * @param session Session
             * @param constantExpression Constant expression
             * @return Transformed constant expression
             */
            virtual GSNodePtr TransformConstantExpression(LRef<Driver::GS_Session> session,
                                                          NodePtrLRef<GS_ConstantExpression> constantExpression);

            /**
             * Transform unary expression
             * @param session Session
             * @param unaryExpression Unary expression
             * @return Transformed unary expression
             */
            virtual GSNodePtr TransformUnaryExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_UnaryExpression> unaryExpression);

            /**
             * Transform binary expression
             * @param session Session
             * @param binaryExpression Binary expression
             * @return Transformed binary expression
             */
            virtual GSNodePtr TransformBinaryExpression(LRef<Driver::GS_Session> session,
                                                        NodePtrLRef<GS_BinaryExpression> binaryExpression);

            /**
             * Transform array expression
             * @param session Session
             * @param arrayExpression Array expression
             * @return Transformed array expression
             */
            virtual GSNodePtr TransformArrayExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_ArrayExpression> arrayExpression);

            /**
             * Transform variable using expression
             * @param session Session
             * @param variableUsingExpression Variable using expression
             * @return Transformed variable using expression
             */
            virtual GSNodePtr TransformVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                               NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression);

            /**
             * Transform function calling expression
             * @param session Session
             * @param functionCallingExpression Function calling expression
             * @return Transformed function calling expression
             */
            virtual GSNodePtr TransformFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                                 NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression);
        };

    }

}

#endif //GSLANGUAGE_GS_VISITOR_H
