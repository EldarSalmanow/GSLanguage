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
     * Base class for AST visitor contexts
     */
    class GS_VisitorContext {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_VisitorContext() = default;
    };

    /**
     * Visitor context ptr type
     */
    using GSVisitorContextPtr = SharedPtr<GS_VisitorContext>;

    /**
     * Interface class for all AST visitors
     * @tparam ResultT
     */
    template<typename ResultT>
    class GS_BaseVisitor {
    public:

        /**
         * Result type
         */
        using Result = ResultT;

    public:

        GS_BaseVisitor()
                : _context(nullptr) {}

        /**
         * Constructor for base visitor
         * @param context Visitor context
         */
        explicit GS_BaseVisitor(GSVisitorContextPtr context)
                : _context(std::move(context)) {}

    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_BaseVisitor() = default;

    public:

        /**
         * Getter for visitor context
         * @return Visitor context
         */
        LRef<GSVisitorContextPtr> getContext() {
            return _context;
        }

    public:

        /**
         * Visit node
         * @param node Node
         * @return Data
         */
        virtual Result visitNode(ConstLRef<GSNodePtr> node) {
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
         * @return Data
         */
        virtual Result visitDeclaration(ConstLRef<GSDeclarationPtr> declaration) {
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
         * @return Data
         */
        virtual Result visitStatement(ConstLRef<GSStatementPtr> statement) {
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
         * @return Data
         */
        virtual Result visitExpression(ConstLRef<GSExpressionPtr> expression) {
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
         * @return Data
         */
        virtual Result visitTranslationUnitDeclaration(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) = 0;

        /**
         * Visit function declaration
         * @param functionDeclaration Function declaration
         * @return Data
         */
        virtual Result visitFunctionDeclaration(SharedPtr<GS_FunctionDeclaration> functionDeclaration) = 0;

        /**
         * Visit variable declaration statement
         * @param variableDeclarationStatement Variable declaration statement
         * @return Data
         */
        virtual Result visitVariableDeclarationStatement(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) = 0;

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return Data
         */
        virtual Result visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) = 0;

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return Data
         */
        virtual Result visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) = 0;

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return Data
         */
        virtual Result visitConstantExpression(SharedPtr<GS_ConstantExpression> constantExpression) = 0;

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return Data
         */
        virtual Result visitUnaryExpression(SharedPtr<GS_UnaryExpression> unaryExpression) = 0;

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return Data
         */
        virtual Result visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) = 0;

        /**
         * Visit variable using expression
         * @param variableUsingExpression Variable using expression
         * @return Data
         */
        virtual Result visitVariableUsingExpression(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) = 0;

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Data
         */
        virtual Result visitFunctionCallingExpression(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) = 0;

    private:

        /**
         * Visitor context
         */
        GSVisitorContextPtr _context;
    };

    /**
     * Base class for AST visitors
     * @tparam ResultT Result type of visiting AST
     */
    template<typename ResultT>
    class GS_Visitor : public GS_BaseVisitor<ResultT> {
    public:

        /**
         * Result type
         */
        using Result = typename GS_BaseVisitor<ResultT>::Result;

    public:

        /**
         * Constructor for visitor
         * @param context Visitor context
         */
        explicit GS_Visitor(GSVisitorContextPtr context)
                : GS_BaseVisitor<ResultT>(std::move(context)) {}
    };

    /**
     * Template specialisation for AST visitors with void result
     */
    template<>
    class GS_Visitor<Void> : public GS_BaseVisitor<Void> {
    public:

        /**
         * Result type
         */
        using Result = typename GS_BaseVisitor<Void>::Result;

    public:

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        Result visitTranslationUnitDeclaration(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) override {
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
        Result visitFunctionDeclaration(SharedPtr<GS_FunctionDeclaration> functionDeclaration) override {
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
        Result visitVariableDeclarationStatement(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) override {
            auto expression = variableDeclarationStatement->getExpression();

            visitNode(expression);
        }

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return
         */
        Result visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) override {
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
        Result visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) override {
            auto expression = expressionStatement->getExpression();

            visitNode(expression);
        }

        /**
         * Visit constant expression
         * @param constantExpression Constant expression
         * @return
         */
        Result visitConstantExpression(SharedPtr<GS_ConstantExpression> constantExpression) override {

        }

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return
         */
        Result visitUnaryExpression(SharedPtr<GS_UnaryExpression> unaryExpression) override {
            auto expression = unaryExpression->getExpression();

            visitNode(expression);
        }

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return
         */
        Result visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) override {
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
        Result visitVariableUsingExpression(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) override {

        }

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return
         */
        Result visitFunctionCallingExpression(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) override {
            auto params = functionCallingExpression->getParams();

            for (auto &expression : params) {
                visitNode(expression);
            }
        }
    };

    /**
     * Template specialisation for AST visitors with node result
     */
    template<>
    class GS_Visitor<GSNodePtr> : public GS_BaseVisitor<GSNodePtr> {
    public:

        /**
         * Result type
         */
        using Result = typename GS_BaseVisitor<GSNodePtr>::Result;

    public:

        /**
         * Visit translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return Transformed node
         */
        Result visitTranslationUnitDeclaration(SharedPtr<GS_TranslationUnitDeclaration> translationUnitDeclaration) override {
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
        Result visitFunctionDeclaration(SharedPtr<GS_FunctionDeclaration> functionDeclaration) override {
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
        Result visitVariableDeclarationStatement(SharedPtr<GS_VariableDeclarationStatement> variableDeclarationStatement) override {
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
        Result visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) override {
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
        Result visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) override {
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
        Result visitConstantExpression(SharedPtr<GS_ConstantExpression> constantExpression) override {
            return constantExpression;
        }

        /**
         * Visit unary expression
         * @param unaryExpression Unary expression
         * @return Transformed node
         */
        Result visitUnaryExpression(SharedPtr<GS_UnaryExpression> unaryExpression) override {
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
        Result visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) override {
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
        Result visitVariableUsingExpression(SharedPtr<GS_VariableUsingExpression> variableUsingExpression) override {
            return variableUsingExpression;
        }

        /**
         * Visit function calling expression
         * @param functionCallingExpression Function calling expression
         * @return Transformed node
         */
        Result visitFunctionCallingExpression(SharedPtr<GS_FunctionCallingExpression> functionCallingExpression) override {
            auto &params = functionCallingExpression->getParams();

            for (auto &expression : params) {
                auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(expression));

                expression.swap(transformedExpression);
            }

            return functionCallingExpression;
        }
    };

}

#endif //GSLANGUAGE_GS_VISITOR_H
