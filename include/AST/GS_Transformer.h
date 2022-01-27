#ifndef GSLANGUAGE_GS_TRANSFORMER_H
#define GSLANGUAGE_GS_TRANSFORMER_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    class GS_Node;

    using GSNodePtr = SharedPtr<GS_Node>;

    /**
     * Base class for all AST transformers
     */
    class GS_Transformer : public GS_Visitor<GSNodePtr> {
    public:

        ~GS_Transformer() override;

    public:

        /**
         * Visit node
         * @param node Node
         * @return Transformed node
         */
        GSNodePtr visit(ConstLRef<GSNodePtr> node) override;

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) override;

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) override;

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_ExpressionStatement> expressionStatement) override;

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_ConstantExpression> constantExpression) override;

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_UnaryExpression> unaryExpression) override;

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_BinaryExpression> binaryExpression) override;

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) override;

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Transformed node
         */
        GSNodePtr visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) override;
    };

}

#endif //GSLANGUAGE_GS_TRANSFORMER_H
