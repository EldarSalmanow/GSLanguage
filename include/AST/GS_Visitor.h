#ifndef GSLANGUAGE_GS_VISITOR_H
#define GSLANGUAGE_GS_VISITOR_H

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
     * Interface class for all AST visitors
     */
    template<typename T>
    class GS_Visitor {
    public:

        virtual ~GS_Visitor() = default;

    public:

        virtual T visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) = 0;

        virtual T visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) = 0;

        virtual T visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) = 0;

        virtual T visit(SharedPtr<GS_ExpressionStatement> expressionStatement) = 0;

        virtual T visit(SharedPtr<GS_ConstantExpression> constantExpression) = 0;

        virtual T visit(SharedPtr<GS_UnaryExpression> unaryExpression) = 0;

        virtual T visit(SharedPtr<GS_BinaryExpression> binaryExpression) = 0;

        virtual T visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) = 0;

        virtual T visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) = 0;
    };

    /**
     *
     */
    template<typename T>
    using GSVisitorPtr = SharedPtr<GS_Visitor<T>>;

    /**
     * Base class for all AST visitors
     */
    class GS_BaseVisitor : public GS_Visitor<Void> {
    public:

        /**
         *
         */
        ~GS_BaseVisitor() override;

    public:

        Void visit(SharedPtr<GS_FunctionDeclaration> functionDeclaration) override;

        Void visit(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) override;

        Void visit(SharedPtr<GS_AssignmentStatement> assignmentStatement) override;

        Void visit(SharedPtr<GS_ExpressionStatement> expressionStatement) override;

        Void visit(SharedPtr<GS_ConstantExpression> constantExpression) override;

        Void visit(SharedPtr<GS_UnaryExpression> unaryExpression) override;

        Void visit(SharedPtr<GS_BinaryExpression> binaryExpression) override;

        Void visit(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) override;

        Void visit(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) override;
    };

    /**
     *
     * @tparam T
     * @param visitor
     * @param node
     * @return
     */
    template<typename T>
    T Accept(Ptr<GS_Visitor<T>> visitor, ConstLRef<GSNodePtr> node) {
        if (node->isDeclaration()) {
            auto declaration = std::reinterpret_pointer_cast<GS_Declaration>(node);

            switch (declaration->getDeclarationType()) {
                case DeclarationType::FunctionDeclaration:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_FunctionDeclaration>(declaration));
            }
        }

        if (node->isStatement()) {
            auto statement = std::reinterpret_pointer_cast<GS_Statement>(node);

            switch (statement->getStatementType()) {
                case StatementType::VariableDeclarationStatement:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_VariableDeclarationStatement>(statement));
                case StatementType::AssignmentStatement:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_AssignmentStatement>(statement));
                case StatementType::ExpressionStatement:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_ExpressionStatement>(statement));
            }
        }

        if (node->isExpression()) {
            auto expression = std::reinterpret_pointer_cast<GS_Expression>(node);

            switch (expression->getExpressionType()) {
                case ExpressionType::ConstantExpression:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_ConstantExpression>(expression));
                case ExpressionType::UnaryExpression:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_UnaryExpression>(expression));
                case ExpressionType::BinaryExpression:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_BinaryExpression>(expression));
                case ExpressionType::VariableUsingExpression:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_VariableUsingExpression>(expression));
                case ExpressionType::FunctionCallingExpression:
                    return visitor->visit(std::reinterpret_pointer_cast<GS_FunctionCallingExpression>(expression));
            }
        }
    }

}

#endif //GSLANGUAGE_GS_VISITOR_H
