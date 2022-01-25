#ifndef GSLANGUAGE_GS_TRANSFORMER_H
#define GSLANGUAGE_GS_TRANSFORMER_H

#include <GSCrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler::AST {

    class GS_Node;

    using GSNodePtr = SharedPtr<GS_Node>;

    class GS_FunctionDeclaration;

    class GS_VariableDeclarationStatement;
    class GS_AssignmentStatement;
    class GS_ExpressionStatement;

    class GS_ConstantExpression;
    class GS_UnaryExpression;
    class GS_BinaryExpression;
    class GS_VariableUsingExpression;
    class GS_FunctionCallingExpression;

    class GS_Transformer {
    public:

        virtual ~GS_Transformer();

    public:

        virtual GSNodePtr transform(Ptr<GS_FunctionDeclaration> functionDeclaration) = 0;

        virtual GSNodePtr transform(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) = 0;

        virtual GSNodePtr transform(Ptr<GS_AssignmentStatement> assignmentStatement) = 0;

        virtual GSNodePtr transform(Ptr<GS_ExpressionStatement> expressionStatement) = 0;

        virtual GSNodePtr transform(Ptr<GS_ConstantExpression> constantExpression) = 0;

        virtual GSNodePtr transform(Ptr<GS_UnaryExpression> unaryExpression) = 0;

        virtual GSNodePtr transform(Ptr<GS_BinaryExpression> binaryExpression) = 0;

        virtual GSNodePtr transform(Ptr<GS_VariableUsingExpression> variableUsingExpression) = 0;

        virtual GSNodePtr transform(Ptr<GS_FunctionCallingExpression> functionCallingExpression) = 0;
    };

    class GS_BaseVisitor;

    class GS_BaseTransformer : public GS_Transformer, public GS_BaseVisitor {
    public:

        ~GS_BaseTransformer() override;

    public:

        GSNodePtr transform(Ptr<GS_FunctionDeclaration> functionDeclaration) override;

        GSNodePtr transform(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        GSNodePtr transform(Ptr<GS_AssignmentStatement> assignmentStatement) override;

        GSNodePtr transform(Ptr<GS_ExpressionStatement> expressionStatement) override;

        GSNodePtr transform(Ptr<GS_ConstantExpression> constantExpression) override;

        GSNodePtr transform(Ptr<GS_UnaryExpression> unaryExpression) override;

        GSNodePtr transform(Ptr<GS_BinaryExpression> binaryExpression) override;

        GSNodePtr transform(Ptr<GS_VariableUsingExpression> variableUsingExpression) override;

        GSNodePtr transform(Ptr<GS_FunctionCallingExpression> functionCallingExpression) override;
    };

}

#endif //GSLANGUAGE_GS_TRANSFORMER_H
