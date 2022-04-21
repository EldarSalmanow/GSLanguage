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

    // TODO update and simplify visiting AST process

    namespace New {

        class Visitor {
        public:

            /**
             * Visit node
             * @param node Node
             * @return
             */
            virtual Void VisitNode(LRef<GSNodePtr> node) {
                if (node->IsDeclaration()) {
                    auto declaration = ToDeclaration(node);

                    return VisitDeclaration(declaration);
                }

                if (node->IsStatement()) {
                    auto statement = ToStatement(node);

                    return VisitStatement(statement);
                }

                if (node->IsExpression()) {
                    auto expression = ToExpression(node);

                    return VisitExpression(expression);
                }
            }

            /**
             * Visit declaration
             * @param declaration Declaration
             * @return
             */
            virtual Void VisitDeclaration(LRef<GSDeclarationPtr> declaration) {
                switch (declaration->GetDeclarationType()) {
                    case DeclarationType::TranslationUnitDeclaration: {
                        auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                        return VisitTranslationUnitDeclaration(translationUnitDeclaration);
                    }
                    case DeclarationType::FunctionDeclaration: {
                        auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);
                        
                        return VisitFunctionDeclaration(functionDeclaration);
                    }
                }
            }

            /**
             * Visit statement
             * @param statement Statement
             * @return
             */
            virtual Void VisitStatement(LRef<GSStatementPtr> statement) {
                switch (statement->GetStatementType()) {
                    case StatementType::VariableDeclarationStatement: {
                        auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);
                        
                        return VisitVariableDeclarationStatement(variableDeclarationStatement);
                    }
                    case StatementType::AssignmentStatement: {
                        auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);
                        
                        return VisitAssignmentStatement(assignmentStatement);
                    }
                    case StatementType::ExpressionStatement: {
                        auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);
                        
                        return VisitExpressionStatement(expressionStatement);
                    }
                }
            }

            /**
             * Visit expression
             * @param expression Expression
             * @return
             */
            virtual Void VisitExpression(LRef<GSExpressionPtr> expression) {
                switch (expression->GetExpressionType()) {
                    case ExpressionType::ConstantExpression: {
                        auto constantExpression = ToExpression<GS_ConstantExpression>(expression);
                        
                        return VisitConstantExpression(constantExpression);
                    }
                    case ExpressionType::UnaryExpression: {
                        auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);
                        
                        return VisitUnaryExpression(unaryExpression);
                    }
                    case ExpressionType::BinaryExpression: {
                        auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);
                        
                        return VisitBinaryExpression(binaryExpression);
                    }
                    case ExpressionType::VariableUsingExpression: {
                        auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);
                        
                        return VisitVariableUsingExpression(variableUsingExpression);
                    }
                    case ExpressionType::FunctionCallingExpression: {
                        auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                        return VisitFunctionCallingExpression(functionCallingExpression);
                    }
                }
            }

            /**
             * Visit translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @return
             */
            virtual Void VisitTranslationUnitDeclaration(LRef<SharedPtr<GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
                auto nodes = translationUnitDeclaration->GetNodes();

                for (auto &node : nodes) {
                    VisitNode(node);
                }
            }

            /**
             * Visit function declaration
             * @param functionDeclaration Function declaration
             * @return
             */
            virtual Void VisitFunctionDeclaration(LRef<SharedPtr<GS_FunctionDeclaration>> functionDeclaration) {
                auto statements = functionDeclaration->GetBody();

                for (auto &statement : statements) {
                    VisitStatement(statement);
                }
            }

            /**
             * Visit variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @return
             */
            virtual Void VisitVariableDeclarationStatement(LRef<SharedPtr<GS_VariableDeclarationStatement>> variableDeclarationStatement) {
                auto expression = variableDeclarationStatement->GetExpression();

                VisitExpression(expression);
            }

            /**
             * Visit assignment statement
             * @param assignmentStatement Assignment statement
             * @return
             */
            virtual Void VisitAssignmentStatement(LRef<SharedPtr<GS_AssignmentStatement>> assignmentStatement) {
                auto lvalueExpression = assignmentStatement->GetLValueExpression();
                auto rvalueExpression = assignmentStatement->GetRValueExpression();

                VisitExpression(lvalueExpression);
                VisitExpression(rvalueExpression);
            }

            /**
             * Visit expression statement
             * @param expressionStatement Expression statement
             * @return
             */
            virtual Void VisitExpressionStatement(LRef<SharedPtr<GS_ExpressionStatement>> expressionStatement) {
                auto expression = expressionStatement->GetExpression();

                VisitExpression(expression);
            }

            /**
             * Visit constant expression
             * @param constantExpression Constant expression
             * @return
             */
            virtual Void VisitConstantExpression(LRef<SharedPtr<GS_ConstantExpression>> constantExpression) {

            }

            /**
             * Visit unary expression
             * @param unaryExpression Unary expression
             * @return
             */
            virtual Void VisitUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression) {
                auto expression = unaryExpression->GetExpression();

                VisitExpression(expression);
            }

            /**
             * Visit binary expression
             * @param binaryExpression Binary expression
             * @return
             */
            virtual Void VisitBinaryExpression(LRef<SharedPtr<GS_BinaryExpression>> binaryExpression) {
                auto firstExpression = binaryExpression->GetFirstExpression();
                auto secondExpression = binaryExpression->GetSecondExpression();

                VisitExpression(firstExpression);
                VisitExpression(secondExpression);
            }

            /**
             * Visit variable using expression
             * @param variableUsingExpression Variable using expression
             * @return
             */
            virtual Void VisitVariableUsingExpression(LRef<SharedPtr<GS_VariableUsingExpression>> variableUsingExpression) {

            }

            /**
             * Visit function calling expression
             * @param functionCallingExpression Function calling expression
             * @return
             */
            virtual Void VisitFunctionCallingExpression(LRef<SharedPtr<GS_FunctionCallingExpression>> functionCallingExpression) {

            }
        };
        
        class Transformer {
        public:

            /**
             * Visit node
             * @param node Node
             * @return Transformed node
             */
            virtual GSNodePtr TransformNode(LRef<GSNodePtr> node) {
                if (node->IsDeclaration()) {
                    auto declaration = ToDeclaration(node);

                    return TransformDeclaration(declaration);
                }

                if (node->IsStatement()) {
                    auto statement = ToStatement(node);

                    return TransformStatement(statement);
                }

                if (node->IsExpression()) {
                    auto expression = ToExpression(node);

                    return TransformExpression(expression);
                }

                return nullptr;
            }

            /**
             * Visit declaration
             * @param declaration Declaration
             * @return Transformed declaration
             */
            virtual GSNodePtr TransformDeclaration(LRef<GSDeclarationPtr> declaration) {
                switch (declaration->GetDeclarationType()) {
                    case DeclarationType::TranslationUnitDeclaration: {
                        auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                        return TransformTranslationUnitDeclaration(translationUnitDeclaration);
                    }
                    case DeclarationType::FunctionDeclaration: {
                        auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                        return TransformFunctionDeclaration(functionDeclaration);
                    }
                }

                return nullptr;
            }

            /**
             * Visit statement
             * @param statement Statement
             * @return Transformed statement
             */
            virtual GSNodePtr TransformStatement(LRef<GSStatementPtr> statement) {
                switch (statement->GetStatementType()) {
                    case StatementType::VariableDeclarationStatement: {
                        auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                        return TransformVariableDeclarationStatement(variableDeclarationStatement);
                    }
                    case StatementType::AssignmentStatement: {
                        auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                        return TransformAssignmentStatement(assignmentStatement);
                    }
                    case StatementType::ExpressionStatement: {
                        auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                        return TransformExpressionStatement(expressionStatement);
                    }
                }

                return nullptr;
            }

            /**
             * Visit expression
             * @param expression Expression
             * @return Transformed expression
             */
            virtual GSNodePtr TransformExpression(LRef<GSExpressionPtr> expression) {
                switch (expression->GetExpressionType()) {
                    case ExpressionType::ConstantExpression: {
                        auto constantExpression = ToExpression<GS_ConstantExpression>(expression);

                        return TransformConstantExpression(constantExpression);
                    }
                    case ExpressionType::UnaryExpression: {
                        auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                        return TransformUnaryExpression(unaryExpression);
                    }
                    case ExpressionType::BinaryExpression: {
                        auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                        return TransformBinaryExpression(binaryExpression);
                    }
                    case ExpressionType::VariableUsingExpression: {
                        auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                        return TransformVariableUsingExpression(variableUsingExpression);
                    }
                    case ExpressionType::FunctionCallingExpression: {
                        auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                        return TransformFunctionCallingExpression(functionCallingExpression);
                    }
                }

                return nullptr;
            }

            /**
             * Visit translation unit declaration
             * @param translationUnitDeclaration Translation unit declaration
             * @return Transformed translation unit declaration
             */
            virtual GSNodePtr TransformTranslationUnitDeclaration(LRef<SharedPtr<GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
                auto &nodes = translationUnitDeclaration->GetNodes();

                for (auto &node : nodes) {
                    auto transformedNode = TransformNode(node);

                    node.swap(transformedNode);
                }

                return translationUnitDeclaration;
            }

            /**
             * Visit function declaration
             * @param functionDeclaration Function declaration
             * @return Transformed function declaration
             */
            virtual GSNodePtr TransformFunctionDeclaration(LRef<SharedPtr<GS_FunctionDeclaration>> functionDeclaration) {
                auto statements = functionDeclaration->GetBody();

                for (auto &statement : statements) {
                    auto transformedStatement = ToStatement(TransformStatement(statement));

                    statement.swap(transformedStatement);
                }

                return functionDeclaration;
            }

            /**
             * Visit variable declaration statement
             * @param variableDeclarationStatement Variable declaration statement
             * @return Transformed variable declaration statement
             */
            virtual GSNodePtr TransformVariableDeclarationStatement(LRef<SharedPtr<GS_VariableDeclarationStatement>> variableDeclarationStatement) {
                auto expression = variableDeclarationStatement->GetExpression();

                auto transformedExpression = ToExpression(expression);

                expression.swap(transformedExpression);

                return variableDeclarationStatement;
            }

            /**
             * Visit assignment statement
             * @param assignmentStatement Assignment statement
             * @return Transformed assignment statement
             */
            virtual GSNodePtr TransformAssignmentStatement(LRef<SharedPtr<GS_AssignmentStatement>> assignmentStatement) {
                auto lvalueExpression = assignmentStatement->GetLValueExpression();
                auto rvalueExpression = assignmentStatement->GetRValueExpression();

                auto transformedLvalueExpression = ToExpression(TransformExpression(lvalueExpression));
                auto transformedRvalueExpression = ToExpression(TransformExpression(rvalueExpression));

                lvalueExpression.swap(transformedLvalueExpression);
                rvalueExpression.swap(transformedRvalueExpression);

                return assignmentStatement;
            }

            /**
             * Visit expression statement
             * @param expressionStatement Expression statement
             * @return Transformed expression statement
             */
            virtual GSNodePtr TransformExpressionStatement(LRef<SharedPtr<GS_ExpressionStatement>> expressionStatement) {
                auto expression = expressionStatement->GetExpression();

                auto transformedExpression = ToExpression(expression);

                expression.swap(transformedExpression);

                return expressionStatement;
            }

            /**
             * Visit constant expression
             * @param constantExpression Constant expression
             * @return Transformed constant expression
             */
            virtual GSNodePtr TransformConstantExpression(LRef<SharedPtr<GS_ConstantExpression>> constantExpression) {
                return constantExpression;
            }

            /**
             * Visit unary expression
             * @param unaryExpression Unary expression
             * @return Transformed unary expression
             */
            virtual GSNodePtr TransformUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression) {
                auto expression = unaryExpression->GetExpression();

                auto transformedExpression = ToExpression(expression);

                expression.swap(transformedExpression);

                return unaryExpression;
            }

            /**
             * Visit binary expression
             * @param binaryExpression Binary expression
             * @return Transformed binary expression
             */
            virtual GSNodePtr TransformBinaryExpression(LRef<SharedPtr<GS_BinaryExpression>> binaryExpression) {
                auto firstExpression = binaryExpression->GetFirstExpression();
                auto secondExpression = binaryExpression->GetSecondExpression();

                auto transformedFirstExpression = ToExpression(TransformExpression(firstExpression));
                auto transformedSecondExpression = ToExpression(TransformExpression(secondExpression));

                firstExpression.swap(transformedFirstExpression);
                secondExpression.swap(transformedSecondExpression);

                return binaryExpression;
            }

            /**
             * Visit variable using expression
             * @param variableUsingExpression Variable using expression
             * @return Transformed variable using expression
             */
            virtual GSNodePtr TransformVariableUsingExpression(LRef<SharedPtr<GS_VariableUsingExpression>> variableUsingExpression) {
                return variableUsingExpression;
            }

            /**
             * Transform function calling expression
             * @param functionCallingExpression Function calling expression
             * @return Transformed function calling expression
             */
            virtual GSNodePtr TransformFunctionCallingExpression(LRef<SharedPtr<GS_FunctionCallingExpression>> functionCallingExpression) {
                return functionCallingExpression;
            }
        };

        class ConstantFoldingTransformer : public Transformer {
        public:

            GSNodePtr TransformUnaryExpression(LRef<SharedPtr<GS_UnaryExpression>> unaryExpression) override {
                unaryExpression = Transformer::TransformUnaryExpression(unaryExpression);

                auto expression = unaryExpression->GetExpression();
                auto operation = unaryExpression->GetUnaryOperation();

                if (auto constantExpression = ToExpression<GS_ConstantExpression>(expression)) {
                    auto value = constantExpression->GetValue();

                    if (auto i32Value = GSValueCast<GS_I32Value>(value)) {
                        auto number = i32Value->GetI32Value();

                        switch (operation) {
                            case UnaryOperation::Minus:
                                number = -number;

                                break;
                        }

                        return GS_ConstantExpression::Create(GS_I32Value::Create(number));
                    }
                }

                return unaryExpression;
            }
        };

        class GS_Pass {
        public:

            virtual Void Run()
        };

    }
    
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
            if (node->IsDeclaration()) {
                auto declaration = std::reinterpret_pointer_cast<GS_Declaration>(node);

                return visitDeclaration(declaration);
            }

            if (node->IsStatement()) {
                auto statement = std::reinterpret_pointer_cast<GS_Statement>(node);

                return visitStatement(statement);
            }

            if (node->IsExpression()) {
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
            switch (declaration->GetDeclarationType()) {
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
            switch (statement->GetStatementType()) {
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
            switch (expression->GetExpressionType()) {
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
            auto nodes = translationUnitDeclaration->GetNodes();

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
            auto body = functionDeclaration->GetBody();

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
            auto expression = variableDeclarationStatement->GetExpression();

            visitNode(expression);
        }

        /**
         * Visit assignment statement
         * @param assignmentStatement Assignment statement
         * @return
         */
        Result visitAssignmentStatement(SharedPtr<GS_AssignmentStatement> assignmentStatement) override {
            auto lvalueExpression = assignmentStatement->GetLValueExpression();
            auto rvalueExpression = assignmentStatement->GetRValueExpression();

            visitNode(lvalueExpression);
            visitNode(rvalueExpression);
        }

        /**
         * Visit expression statement
         * @param expressionStatement Expression statement
         * @return
         */
        Result visitExpressionStatement(SharedPtr<GS_ExpressionStatement> expressionStatement) override {
            auto expression = expressionStatement->GetExpression();

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
            auto expression = unaryExpression->GetExpression();

            visitNode(expression);
        }

        /**
         * Visit binary expression
         * @param binaryExpression Binary expression
         * @return
         */
        Result visitBinaryExpression(SharedPtr<GS_BinaryExpression> binaryExpression) override {
            auto firstExpression = binaryExpression->GetFirstExpression();
            auto secondExpression = binaryExpression->GetSecondExpression();

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
            auto params = functionCallingExpression->GetParams();

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
            auto &nodes = translationUnitDeclaration->GetNodes();

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
            auto &body = functionDeclaration->GetBody();

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
            auto &expression = variableDeclarationStatement->GetExpression();

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
            auto &lvalueExpression = assignmentStatement->GetLValueExpression();
            auto &rvalueExpression = assignmentStatement->GetRValueExpression();

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
            auto &expression = expressionStatement->GetExpression();

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
            auto &expression = unaryExpression->GetExpression();

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
            auto &firstExpression = binaryExpression->GetFirstExpression();
            auto &secondExpression = binaryExpression->GetSecondExpression();

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
            auto &params = functionCallingExpression->GetParams();

            for (auto &expression : params) {
                auto transformedExpression = std::reinterpret_pointer_cast<GS_Expression>(visitNode(expression));

                expression.swap(transformedExpression);
            }

            return functionCallingExpression;
        }
    };

}

#endif //GSLANGUAGE_GS_VISITOR_H
