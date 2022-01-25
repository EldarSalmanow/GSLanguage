#ifndef GSLANGUAGE_GS_VISITOR_H
#define GSLANGUAGE_GS_VISITOR_H

#include <GSCrossPlatform/GS_CrossPlatform.h>

namespace GSLanguageCompiler::AST {

    class GS_FunctionDeclaration;

    class GS_VariableDeclarationStatement;
    class GS_AssignmentStatement;
    class GS_ExpressionStatement;

    class GS_ConstantExpression;
    class GS_UnaryExpression;
    class GS_BinaryExpression;
    class GS_VariableUsingExpression;
    class GS_FunctionCallingExpression;

    /**
     * Interface class for all AST visitors
     */
    class GS_Visitor {
    public:

        virtual ~GS_Visitor();

    public:

        virtual Any visit(Ptr<GS_FunctionDeclaration> functionDeclaration) = 0;

        virtual Any visit(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) = 0;

        virtual Any visit(Ptr<GS_AssignmentStatement> assignmentStatement) = 0;

        virtual Any visit(Ptr<GS_ExpressionStatement> expressionStatement) = 0;

        virtual Any visit(Ptr<GS_ConstantExpression> constantExpression) = 0;

        virtual Any visit(Ptr<GS_UnaryExpression> unaryExpression) = 0;

        virtual Any visit(Ptr<GS_BinaryExpression> binaryExpression) = 0;

        virtual Any visit(Ptr<GS_VariableUsingExpression> variableUsingExpression) = 0;

        virtual Any visit(Ptr<GS_FunctionCallingExpression> functionCallingExpression) = 0;
    };

    /**
     * Visitor ptr type
     */
    using GSVisitorPtr = SharedPtr<GS_Visitor>;

    /**
     * Base class for all AST visitors
     */
    class GS_BaseVisitor : public GS_Visitor {
    public:

        /**
         *
         */
        ~GS_BaseVisitor() override;

    public:

        Any visit(Ptr<GS_FunctionDeclaration> functionDeclaration) override;

        Any visit(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        Any visit(Ptr<GS_AssignmentStatement> assignmentStatement) override;

        Any visit(Ptr<GS_ExpressionStatement> expressionStatement) override;

        Any visit(Ptr<GS_ConstantExpression> constantExpression) override;

        Any visit(Ptr<GS_UnaryExpression> unaryExpression) override;

        Any visit(Ptr<GS_BinaryExpression> binaryExpression) override;

        Any visit(Ptr<GS_VariableUsingExpression> variableUsingExpression) override;

        Any visit(Ptr<GS_FunctionCallingExpression> functionCallingExpression) override;
    };

}

#endif //GSLANGUAGE_GS_VISITOR_H
