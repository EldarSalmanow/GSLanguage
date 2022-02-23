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

namespace GSLanguageCompiler::AST {

    /**
     * Interface class for all AST visitors
     */
    template<typename T>
    class GS_BaseVisitor {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_BaseVisitor() = default;

    public:

        /**
         * Visit node
         * @param node Node
         * @return Data
         */
        virtual T visitNode(ConstLRef<GSNodePtr> node) = 0;

        /**
         * Visit declaration
         * @param declaration Declaration
         * @return Data
         */
        virtual T visitDeclaration(ConstLRef<GSDeclarationPtr> declaration) = 0;

        /**
         * Visit statement
         * @param statement Statement
         * @return Data
         */
        virtual T visitStatement(ConstLRef<GSStatementPtr> statement) = 0;

        /**
         * Visit expression
         * @param expression Expression
         * @return Data
         */
        virtual T visitExpression(ConstLRef<GSExpressionPtr> expression) = 0;

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return Data
         */
        virtual T visitTranslationUnitDeclaration(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) = 0;

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return Data
         */
        virtual T visitFunctionDeclaration(SharedPtr<GS_FunctionDeclaration> functionDeclaration) = 0;

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return Data
         */
        virtual T visitVariableDeclarationStatement(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) = 0;

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return Data
         */
        virtual T visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) = 0;

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return Data
         */
        virtual T visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) = 0;

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return Data
         */
        virtual T visitConstantExpression(SharedPtr<GS_ConstantExpression> constantExpression) = 0;

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return Data
         */
        virtual T visitUnaryExpression(SharedPtr<GS_UnaryExpression> unaryExpression) = 0;

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return Data
         */
        virtual T visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) = 0;

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return Data
         */
        virtual T visitVariableUsingExpression(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) = 0;

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Data
         */
        virtual T visitFunctionCallingExpression(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) = 0;
    };

    /**
     * Template specialisation for all AST visitors
     */
    template<>
    class GS_BaseVisitor<Void> {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_BaseVisitor() = default;

    public:

        /**
         * Visit node
         * @param node Node
         * @return
         */
        virtual Void visitNode(ConstLRef<GSNodePtr> node) {
            if (node->isDeclaration()) {
                auto declaration = std::reinterpret_pointer_cast<GS_Declaration>(node);

                return visitDeclaration(declaration);
            }

            if (node->isStatement()) {
                auto statement = std::reinterpret_pointer_cast<GS_Statement>(node);

                return visitStatement(statement);
            }

            if (node->isExpression()) {
                auto expression = std::reinterpret_pointer_cast<GS_Expression>(node);

                return visitExpression(expression);
            }
        }

        /**
         * Visit declaration
         * @param declaration Declaration
         * @return
         */
        virtual Void visitDeclaration(ConstLRef<GSDeclarationPtr> declaration) {
            switch (declaration->getDeclarationType()) {
                case DeclarationType::TranslationUnitDeclaration:
                    return visitTranslationUnitDeclaration(std::reinterpret_pointer_cast<GS_TranslationUnitDeclaration>(declaration));
                case DeclarationType::FunctionDeclaration:
                    return visitFunctionDeclaration(std::reinterpret_pointer_cast<GS_FunctionDeclaration>(declaration));
            }
        }

        /**
         * Visit statement
         * @param statement Statement
         * @return
         */
        virtual Void visitStatement(ConstLRef<GSStatementPtr> statement) {
            switch (statement->getStatementType()) {
                case StatementType::VariableDeclarationStatement:
                    return visitVariableDeclarationStatement(std::reinterpret_pointer_cast<GS_VariableDeclarationStatement>(statement));
                case StatementType::AssignmentStatement:
                    return visitAssignmentStatement(std::reinterpret_pointer_cast<GS_AssignmentStatement>(statement));
                case StatementType::ExpressionStatement:
                    return visitExpressionStatement(std::reinterpret_pointer_cast<GS_ExpressionStatement>(statement));
            }
        }

        /**
         * Visit expression
         * @param expression Expression
         * @return
         */
        virtual Void visitExpression(ConstLRef<GSExpressionPtr> expression) {
            switch (expression->getExpressionType()) {
                case ExpressionType::ConstantExpression:
                    return visitConstantExpression(std::reinterpret_pointer_cast<GS_ConstantExpression>(expression));
                case ExpressionType::UnaryExpression:
                    return visitUnaryExpression(std::reinterpret_pointer_cast<GS_UnaryExpression>(expression));
                case ExpressionType::BinaryExpression:
                    return visitBinaryExpression(std::reinterpret_pointer_cast<GS_BinaryExpression>(expression));
                case ExpressionType::VariableUsingExpression:
                    return visitVariableUsingExpression(std::reinterpret_pointer_cast<GS_VariableUsingExpression>(expression));
                case ExpressionType::FunctionCallingExpression:
                    return visitFunctionCallingExpression(std::reinterpret_pointer_cast<GS_FunctionCallingExpression>(expression));
            }
        }

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        virtual Void visitTranslationUnitDeclaration(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
            auto nodes = translationUnitDeclaration->getNodes();

            for (auto &node : nodes) {
                visitNode(node);
            }
        }

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return
         */
        virtual Void visitFunctionDeclaration(SharedPtr<GS_FunctionDeclaration> functionDeclaration) {
            auto body = functionDeclaration->getBody();

            for (auto &statement : body) {
                visitNode(statement);
            }
        }

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return
         */
        virtual Void visitVariableDeclarationStatement(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
            auto expression = variableDeclarationStatement->getExpression();

            visitNode(expression);
        }

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return
         */
        virtual Void visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) {
            auto lvalueExpression = assignmentStatement->getLValueExpression();
            auto rvalueExpression = assignmentStatement->getRValueExpression();

            visitNode(lvalueExpression);
            visitNode(rvalueExpression);
        }

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return
         */
        virtual Void visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) {
            auto expression = expressionStatement->getExpression();

            visitNode(expression);
        }

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return
         */
        virtual Void visitConstantExpression(SharedPtr<GS_ConstantExpression> constantExpression) {

        }

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return
         */
        virtual Void visitUnaryExpression(SharedPtr<GS_UnaryExpression> unaryExpression) {
            auto expression = unaryExpression->getExpression();

            visitNode(expression);
        }

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return
         */
        virtual Void visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) {
            auto firstExpression = binaryExpression->getFirstExpression();
            auto secondExpression = binaryExpression->getSecondExpression();

            visitNode(firstExpression);
            visitNode(secondExpression);
        }

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return
         */
        virtual Void visitVariableUsingExpression(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) {

        }

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return
         */
        virtual Void visitFunctionCallingExpression(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) {
            auto params = functionCallingExpression->getParams();

            for (auto &expression : params) {
                visitNode(expression);
            }
        }
    };

    /**
     * Template specialisation for all AST visitors
     */
    template<>
    class GS_BaseVisitor<GSNodePtr> {
    public:

        virtual ~GS_BaseVisitor() = default;

    public:

        /**
         * Visit node
         * @param node Node
         * @return Transformed node
         */
        virtual GSNodePtr visitNode(ConstLRef<GSNodePtr> node) {
            if (node->isDeclaration()) {
                auto declaration = std::reinterpret_pointer_cast<GS_Declaration>(node);

                return visitDeclaration(declaration);
            }

            if (node->isStatement()) {
                auto statement = std::reinterpret_pointer_cast<GS_Statement>(node);

                return visitStatement(statement);
            }

            if (node->isExpression()) {
                auto expression = std::reinterpret_pointer_cast<GS_Expression>(node);

                return visitExpression(expression);
            }
        }

        /**
         * Visit declaration
         * @param declaration Declaration
         * @return Transformed node
         */
        virtual GSNodePtr visitDeclaration(ConstLRef<GSDeclarationPtr> declaration) {
            switch (declaration->getDeclarationType()) {
                case DeclarationType::TranslationUnitDeclaration:
                    return visitTranslationUnitDeclaration(std::reinterpret_pointer_cast<GS_TranslationUnitDeclaration>(declaration));
                case DeclarationType::FunctionDeclaration:
                    return visitFunctionDeclaration(std::reinterpret_pointer_cast<GS_FunctionDeclaration>(declaration));
            }
        }

        /**
         * Visit statement
         * @param statement Statement
         * @return Transformed node
         */
        virtual GSNodePtr visitStatement(ConstLRef<GSStatementPtr> statement) {
            switch (statement->getStatementType()) {
                case StatementType::VariableDeclarationStatement:
                    return visitVariableDeclarationStatement(std::reinterpret_pointer_cast<GS_VariableDeclarationStatement>(statement));
                case StatementType::AssignmentStatement:
                    return visitAssignmentStatement(std::reinterpret_pointer_cast<GS_AssignmentStatement>(statement));
                case StatementType::ExpressionStatement:
                    return visitExpressionStatement(std::reinterpret_pointer_cast<GS_ExpressionStatement>(statement));
            }
        }

        /**
         * Visit expression
         * @param expression Expression
         * @return Transformed node
         */
        virtual GSNodePtr visitExpression(ConstLRef<GSExpressionPtr> expression) {
            switch (expression->getExpressionType()) {
                case ExpressionType::ConstantExpression:
                    return visitConstantExpression(std::reinterpret_pointer_cast<GS_ConstantExpression>(expression));
                case ExpressionType::UnaryExpression:
                    return visitUnaryExpression(std::reinterpret_pointer_cast<GS_UnaryExpression>(expression));
                case ExpressionType::BinaryExpression:
                    return visitBinaryExpression(std::reinterpret_pointer_cast<GS_BinaryExpression>(expression));
                case ExpressionType::VariableUsingExpression:
                    return visitVariableUsingExpression(std::reinterpret_pointer_cast<GS_VariableUsingExpression>(expression));
                case ExpressionType::FunctionCallingExpression:
                    return visitFunctionCallingExpression(std::reinterpret_pointer_cast<GS_FunctionCallingExpression>(expression));
            }
        }

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return Transformed node
         */
        virtual GSNodePtr visitTranslationUnitDeclaration(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
            auto &nodes = translationUnitDeclaration->getNodes();

            for (auto &node : nodes) {
                auto transformedNode = visitNode(node);

                node.swap(transformedNode);
            }

            return translationUnitDeclaration;
        }

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return Transformed node
         */
        virtual GSNodePtr visitFunctionDeclaration(SharedPtr<GS_FunctionDeclaration> functionDeclaration) {
            auto &body = functionDeclaration->getBody();

            for (auto &statement : body) {
                auto transformedStatement = std::reinterpret_pointer_cast<GS_Statement>(visitNode(statement));

                statement.swap(transformedStatement);
            }

            return functionDeclaration;
        }

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return Transformed node
         */
        virtual GSNodePtr visitVariableDeclarationStatement(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) {
            auto &expression = variableDeclarationStatement->getExpression();

            auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(expression));

            expression.swap(transformedExpression);

            return variableDeclarationStatement;
        }

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return Transformed node
         */
        virtual GSNodePtr visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) {
            auto &lvalueExpression = assignmentStatement->getLValueExpression();
            auto &rvalueExpression = assignmentStatement->getRValueExpression();

            auto lvalueTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(lvalueExpression));
            auto rvalueTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(rvalueExpression));

            lvalueExpression.swap(lvalueTransformedExpression);
            rvalueExpression.swap(rvalueTransformedExpression);

            return assignmentStatement;
        }

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return Transformed node
         */
        virtual GSNodePtr visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) {
            auto &expression = expressionStatement->getExpression();

            auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(expression));

            expression.swap(transformedExpression);

            return expressionStatement;
        }

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return Transformed node
         */
        virtual GSNodePtr visitConstantExpression(SharedPtr<GS_ConstantExpression> constantExpression) {
            return constantExpression;
        }

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return Transformed node
         */
        virtual GSNodePtr visitUnaryExpression(SharedPtr<GS_UnaryExpression> unaryExpression) {
            auto &expression = unaryExpression->getExpression();

            auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(expression));

            expression.swap(transformedExpression);

            return unaryExpression;
        }

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return Transformed node
         */
        virtual GSNodePtr visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) {
            auto &firstExpression = binaryExpression->getFirstExpression();
            auto &secondExpression = binaryExpression->getSecondExpression();

            auto firstTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(firstExpression));
            auto secondTransformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(secondExpression));

            firstExpression.swap(firstTransformedExpression);
            secondExpression.swap(secondTransformedExpression);

            return binaryExpression;
        }

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return Transformed node
         */
        virtual GSNodePtr visitVariableUsingExpression(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) {
            return variableUsingExpression;
        }

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Transformed node
         */
        virtual GSNodePtr visitFunctionCallingExpression(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) {
            auto &params = functionCallingExpression->getParams();

            for (auto &expression : params) {
                auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(expression));

                expression.swap(transformedExpression);
            }

            return functionCallingExpression;
        }
    };

    /**
     * Visitor type
     */
    using GS_Visitor = GS_BaseVisitor<Void>;

    /**
     * Visitor ptr type
     */
    using GSVisitorPtr = SharedPtr<GS_Visitor>;

    /**
     * Transformer type
     */
    using GS_Transformer = GS_BaseVisitor<GSNodePtr>;

    /**
     * Transformer ptr type
     */
    using GSTransformerPtr = SharedPtr<GS_Transformer>;

}

#endif //GSLANGUAGE_GS_VISITOR_H
