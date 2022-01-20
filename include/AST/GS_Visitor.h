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
     * Base class for all AST visitors
     */
    class GS_Visitor {
    public:

        virtual ~GS_Visitor();

    public:

        virtual Void visit(Ptr<GS_FunctionDeclaration> functionDeclaration);

        virtual Void visit(Ptr<GS_VariableDeclarationStatement> variableDeclarationStatement);

        virtual Void visit(Ptr<GS_AssignmentStatement> assignmentStatement);

        virtual Void visit(Ptr<GS_ExpressionStatement> expressionStatement);

        virtual Void visit(Ptr<GS_ConstantExpression> constantExpression);

        virtual Void visit(Ptr<GS_UnaryExpression> unaryExpression);

        virtual Void visit(Ptr<GS_BinaryExpression> binaryExpression);

        virtual Void visit(Ptr<GS_VariableUsingExpression> variableUsingExpression);

        virtual Void visit(Ptr<GS_FunctionCallingExpression> functionCallingExpression);
    };

    /**
     * Visitor ptr type
     */
    using GSVisitorPtr = SharedPtr<GS_Visitor>;

}

#endif //GSLANGUAGE_GS_VISITOR_H
