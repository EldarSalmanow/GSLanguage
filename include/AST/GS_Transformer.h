#ifndef GSLANGUAGE_GS_TRANSFORMER_H
#define GSLANGUAGE_GS_TRANSFORMER_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    class GS_Node;

    using GSNodePtr = SharedPtr<GS_Node>;

    class GS_Transformer : public GS_Visitor<GSNodePtr> {
    public:

        GSNodePtr visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) override;

        GSNodePtr visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        GSNodePtr visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) override;

        GSNodePtr visit(SharedPtr<GS_ExpressionStatement> expressionStatement) override;

        GSNodePtr visit(SharedPtr<GS_ConstantExpression> constantExpression) override;

        GSNodePtr visit(SharedPtr<GS_UnaryExpression> unaryExpression) override;

        GSNodePtr visit(SharedPtr<GS_BinaryExpression> binaryExpression) override;

        GSNodePtr visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) override;

        GSNodePtr visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) override;
    };

}

#endif //GSLANGUAGE_GS_TRANSFORMER_H
