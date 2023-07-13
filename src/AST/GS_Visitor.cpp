#include <GS_Visitor.h>

namespace GSLanguageCompiler::AST {

    GS_Visitor::~GS_Visitor() = default;

    Void GS_Visitor::SuperNode(LRef<Driver::GS_Session> session,
                               LRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return VisitDeclaration(session,
                                    declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return VisitStatement(session,
                                  statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return VisitExpression(session,
                                   expression);
        }
    }

    Void GS_Visitor::SuperDeclaration(LRef<Driver::GS_Session> session,
                                      LRef<GSDeclarationPtr> declaration) {
        auto declarationType = declaration->GetDeclarationType();

        switch (declarationType) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return VisitTranslationUnitDeclaration(session,
                                                       translationUnitDeclaration);
            }
            case DeclarationType::ModuleDeclaration: {
                auto moduleDeclaration = ToDeclaration<GS_ModuleDeclaration>(declaration);

                return VisitModuleDeclaration(session,
                                              moduleDeclaration);
            }
            case DeclarationType::ImportDeclaration: {
                auto importDeclaration = ToDeclaration<GS_ImportDeclaration>(declaration);

                return VisitImportDeclaration(session,
                                              importDeclaration);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return VisitFunctionDeclaration(session,
                                                functionDeclaration);
            }
        }
    }

    Void GS_Visitor::SuperStatement(LRef<Driver::GS_Session> session,
                                    LRef<GSStatementPtr> statement) {
        auto statementType = statement->GetStatementType();

        switch (statementType) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return VisitVariableDeclarationStatement(session,
                                                         variableDeclarationStatement);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return VisitAssignmentStatement(session,
                                                assignmentStatement);
            }
            case StatementType::IfStatement: {
                auto ifStatement = ToStatement<GS_IfStatement>(statement);

                return VisitIfStatement(session,
                                        ifStatement);
            }
            case StatementType::ForStatement: {
                auto forStatement = ToStatement<GS_ForStatement>(statement);

                return VisitForStatement(session,
                                         forStatement);
            }
            case StatementType::WhileStatement: {
                auto whileStatement = ToStatement<GS_WhileStatement>(statement);

                return VisitWhileStatement(session,
                                           whileStatement);
            }
            case StatementType::MatchStatement: {
                auto matchStatement = ToStatement<GS_MatchStatement>(statement);

                return VisitMatchStatement(session,
                                           matchStatement);
            }
            case StatementType::ReturnStatement: {
                auto returnStatement = ToStatement<GS_ReturnStatement>(statement);

                return VisitReturnStatement(session,
                                            returnStatement);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return VisitExpressionStatement(session,
                                                expressionStatement);
            }
        }
    }

    Void GS_Visitor::SuperExpression(LRef<Driver::GS_Session> session,
                                     LRef<GSExpressionPtr> expression) {
        auto expressionType = expression->GetExpressionType();

        switch (expressionType) {
            case ExpressionType::LiteralExpression: {
                auto literalExpression = ToExpression<GS_LiteralExpression>(expression);

                return VisitLiteralExpression(session,
                                              literalExpression);
            }
            case ExpressionType::ArrayExpression: {
                auto arrayExpression = ToExpression<GS_ArrayExpression>(expression);

                return VisitArrayExpression(session,
                                            arrayExpression);
            }
            case ExpressionType::RangeExpression: {
                auto rangeExpression = ToExpression<GS_RangeExpression>(expression);

                return VisitRangeExpression(session,
                                            rangeExpression);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return VisitUnaryExpression(session,
                                            unaryExpression);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return VisitBinaryExpression(session,
                                             binaryExpression);
            }
            case ExpressionType::IndexExpression: {
                auto indexExpression = ToExpression<GS_IndexExpression>(expression);

                return VisitIndexExpression(session,
                                            indexExpression);
            }
            case ExpressionType::CastExpression: {
                auto castExpression = ToExpression<GS_CastExpression>(expression);

                return VisitCastExpression(session,
                                           castExpression);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return VisitVariableUsingExpression(session,
                                                    variableUsingExpression);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return VisitFunctionCallingExpression(session,
                                                      functionCallingExpression);
            }
        }
    }

    Void GS_Visitor::SuperTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto nodes = translationUnitDeclaration->GetNodes();

        for (auto &node : nodes) {
            VisitNode(session,
                      node);
        }
    }

    Void GS_Visitor::SuperModuleDeclaration(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_ModuleDeclaration> moduleDeclaration) {
        auto body = moduleDeclaration->GetBody();

        for (auto &declaration : body) {
            VisitDeclaration(session,
                             declaration);
        }
    }

    Void GS_Visitor::SuperImportDeclaration(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_ImportDeclaration> importDeclaration) {

    }

    Void GS_Visitor::SuperFunctionDeclaration(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        auto body = functionDeclaration->GetBody();

        for (auto &statement : body) {
            VisitStatement(session,
                           statement);
        }
    }

    Void GS_Visitor::SuperVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto expression = variableDeclarationStatement->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperAssignmentStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        VisitExpression(session,
                        lvalueExpression);
        VisitExpression(session,
                        rvalueExpression);
    }

    Void GS_Visitor::SuperIfStatement(LRef<Driver::GS_Session> session,
                                      NodePtrLRef<GS_IfStatement> ifStatement) {
        auto condition = ifStatement->GetCondition();
        auto ifBody = ifStatement->GetIfBody();
        auto elseBody = ifStatement->GetElseBody();

        VisitExpression(session,
                        condition);

        for (auto &statement : ifBody) {
            VisitStatement(session,
                           statement);
        }

        for (auto &statement : elseBody) {
            VisitStatement(session,
                           statement);
        }
    }

    Void GS_Visitor::SuperForStatement(LRef<Driver::GS_Session> session,
                                       NodePtrLRef<GS_ForStatement> forStatement) {
        auto expression = forStatement->GetExpression();
        auto body = forStatement->GetBody();

        VisitExpression(session,
                        expression);

        for (auto &statement : body) {
            VisitStatement(session,
                           statement);
        }
    }

    Void GS_Visitor::SuperWhileStatement(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_WhileStatement> whileStatement) {
        auto condition = whileStatement->GetCondition();
        auto body = whileStatement->GetBody();

        VisitExpression(session,
                        condition);

        for (auto &statement : body) {
            VisitStatement(session,
                           statement);
        }
    }

    Void GS_Visitor::SuperMatchStatement(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_MatchStatement> matchStatement) {
        auto expression = matchStatement->GetExpression();
        auto arms = matchStatement->GetArms();

        VisitExpression(session,
                        expression);

        for (auto &arm : arms) {
            auto pattern = arm.GetPattern();
            auto body = arm.GetBody();

            VisitExpression(session,
                            pattern);

            for (auto &statement : body) {
                VisitStatement(session,
                               statement);
            }
        }
    }

    Void GS_Visitor::SuperReturnStatement(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ReturnStatement> returnStatement) {
        auto expression = returnStatement->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperExpressionStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperLiteralExpression(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_LiteralExpression> literalExpression) {

    }

    Void GS_Visitor::SuperArrayExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        auto expressions = arrayExpression->GetExpressions();

        for (auto &expression : expressions) {
            VisitExpression(session,
                            expression);
        }
    }

    Void GS_Visitor::SuperRangeExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_RangeExpression> rangeExpression) {
        auto startExpression = rangeExpression->GetStartExpression();
        auto endExpression = rangeExpression->GetEndExpression();

        VisitExpression(session,
                        startExpression);
        VisitExpression(session,
                        endExpression);
    }

    Void GS_Visitor::SuperUnaryExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperBinaryExpression(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        VisitExpression(session,
                        firstExpression);
        VisitExpression(session,
                        secondExpression);
    }

    Void GS_Visitor::SuperIndexExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_IndexExpression> indexExpression) {
        auto expression = indexExpression->GetExpression();
        auto index = indexExpression->GetIndex();

        VisitExpression(session,
                        expression);
        VisitExpression(session,
                        index);
    }

    Void GS_Visitor::SuperCastExpression(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_CastExpression> castExpression) {
        auto expression = castExpression->GetExpression();

        VisitExpression(session,
                        expression);
    }

    Void GS_Visitor::SuperVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {

    }

    Void GS_Visitor::SuperFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {

    }

    Void GS_Visitor::VisitNode(LRef<Driver::GS_Session> session,
                               LRef<GSNodePtr> node) {
        SuperNode(session,
                  node);
    }

    Void GS_Visitor::VisitDeclaration(LRef<Driver::GS_Session> session,
                                      LRef<GSDeclarationPtr> declaration) {
        SuperDeclaration(session,
                         declaration);
    }

    Void GS_Visitor::VisitStatement(LRef<Driver::GS_Session> session,
                                    LRef<GSStatementPtr> statement) {
        SuperStatement(session,
                       statement);
    }

    Void GS_Visitor::VisitExpression(LRef<Driver::GS_Session> session,
                                     LRef<GSExpressionPtr> expression) {
        SuperExpression(session,
                        expression);
    }

    Void GS_Visitor::VisitTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        SuperTranslationUnitDeclaration(session,
                                        translationUnitDeclaration);
    }

    Void GS_Visitor::VisitModuleDeclaration(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_ModuleDeclaration> moduleDeclaration) {
        SuperModuleDeclaration(session,
                               moduleDeclaration);
    }

    Void GS_Visitor::VisitImportDeclaration(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_ImportDeclaration> importDeclaration) {
        SuperImportDeclaration(session,
                               importDeclaration);
    }

    Void GS_Visitor::VisitFunctionDeclaration(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        SuperFunctionDeclaration(session,
                                 functionDeclaration);
    }

    Void GS_Visitor::VisitVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        SuperVariableDeclarationStatement(session,
                                          variableDeclarationStatement);
    }

    Void GS_Visitor::VisitAssignmentStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        SuperAssignmentStatement(session,
                                 assignmentStatement);
    }

    Void GS_Visitor::VisitIfStatement(LRef<Driver::GS_Session> session,
                                      NodePtrLRef<GS_IfStatement> ifStatement) {
        SuperIfStatement(session,
                         ifStatement);
    }

    Void GS_Visitor::VisitForStatement(LRef<Driver::GS_Session> session,
                                       NodePtrLRef<GS_ForStatement> forStatement) {
        SuperForStatement(session,
                          forStatement);
    }

    Void GS_Visitor::VisitWhileStatement(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_WhileStatement> whileStatement) {
        SuperWhileStatement(session,
                            whileStatement);
    }

    Void GS_Visitor::VisitMatchStatement(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_MatchStatement> matchStatement) {
        SuperMatchStatement(session,
                            matchStatement);
    }

    Void GS_Visitor::VisitReturnStatement(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ReturnStatement> returnStatement) {
        SuperReturnStatement(session,
                             returnStatement);
    }

    Void GS_Visitor::VisitExpressionStatement(LRef<Driver::GS_Session> session,
                                              NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        SuperExpressionStatement(session,
                                 expressionStatement);
    }

    Void GS_Visitor::VisitLiteralExpression(LRef<Driver::GS_Session> session,
                                            NodePtrLRef<GS_LiteralExpression> literalExpression) {
        SuperLiteralExpression(session,
                               literalExpression);
    }

    Void GS_Visitor::VisitArrayExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        SuperArrayExpression(session,
                             arrayExpression);
    }

    Void GS_Visitor::VisitRangeExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_RangeExpression> rangeExpression) {
        SuperRangeExpression(session,
                             rangeExpression);
    }

    Void GS_Visitor::VisitUnaryExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        SuperUnaryExpression(session,
                             unaryExpression);
    }

    Void GS_Visitor::VisitBinaryExpression(LRef<Driver::GS_Session> session,
                                           NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        SuperBinaryExpression(session,
                              binaryExpression);
    }

    Void GS_Visitor::VisitIndexExpression(LRef<Driver::GS_Session> session,
                                          NodePtrLRef<GS_IndexExpression> indexExpression) {
        SuperIndexExpression(session,
                             indexExpression);
    }

    Void GS_Visitor::VisitCastExpression(LRef<Driver::GS_Session> session,
                                         NodePtrLRef<GS_CastExpression> castExpression) {
        SuperCastExpression(session,
                            castExpression);
    }

    Void GS_Visitor::VisitVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {
        SuperVariableUsingExpression(session,
                                     variableUsingExpression);
    }

    Void GS_Visitor::VisitFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {
        SuperFunctionCallingExpression(session,
                                       functionCallingExpression);
    }

    GS_Transformer::~GS_Transformer() = default;

    GSNodePtr GS_Transformer::SuperNode(LRef<Driver::GS_Session> session,
                                        LRef<GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return TransformDeclaration(session,
                                        declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return TransformStatement(session,
                                      statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return TransformExpression(session,
                                       expression);
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperDeclaration(LRef<Driver::GS_Session> session,
                                               LRef<GSDeclarationPtr> declaration) {
        auto declarationType = declaration->GetDeclarationType();

        switch (declarationType) {
            case DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<GS_TranslationUnitDeclaration>(declaration);

                return TransformTranslationUnitDeclaration(session,
                                                           translationUnitDeclaration);
            }
            case DeclarationType::ModuleDeclaration: {
                auto moduleDeclaration = ToDeclaration<GS_ModuleDeclaration>(declaration);

                return TransformModuleDeclaration(session,
                                                  moduleDeclaration);
            }
            case DeclarationType::ImportDeclaration: {
                auto importDeclaration = ToDeclaration<GS_ImportDeclaration>(declaration);

                return TransformImportDeclaration(session,
                                                  importDeclaration);
            }
            case DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<GS_FunctionDeclaration>(declaration);

                return TransformFunctionDeclaration(session,
                                                    functionDeclaration);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperStatement(LRef<Driver::GS_Session> session,
                                             LRef<GSStatementPtr> statement) {
        auto statementType = statement->GetStatementType();

        switch (statementType) {
            case StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<GS_VariableDeclarationStatement>(statement);

                return TransformVariableDeclarationStatement(session,
                                                             variableDeclarationStatement);
            }
            case StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<GS_AssignmentStatement>(statement);

                return TransformAssignmentStatement(session,
                                                    assignmentStatement);
            }
            case StatementType::IfStatement: {
                auto ifStatement = ToStatement<GS_IfStatement>(statement);

                return TransformIfStatement(session,
                                            ifStatement);
            }
            case StatementType::ForStatement: {
                auto forStatement = ToStatement<GS_ForStatement>(statement);

                return TransformForStatement(session,
                                             forStatement);
            }
            case StatementType::WhileStatement: {
                auto whileStatement = ToStatement<GS_WhileStatement>(statement);

                return TransformWhileStatement(session,
                                               whileStatement);
            }
            case StatementType::MatchStatement: {
                auto matchStatement = ToStatement<GS_MatchStatement>(statement);

                return TransformMatchStatement(session,
                                               matchStatement);
            }
            case StatementType::ReturnStatement: {
                auto returnStatement = ToStatement<GS_ReturnStatement>(statement);

                return TransformReturnStatement(session,
                                                returnStatement);
            }
            case StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<GS_ExpressionStatement>(statement);

                return TransformExpressionStatement(session,
                                                    expressionStatement);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperExpression(LRef<Driver::GS_Session> session,
                                              LRef<GSExpressionPtr> expression) {
        auto expressionType = expression->GetExpressionType();

        switch (expressionType) {
            case ExpressionType::LiteralExpression: {
                auto literalExpression = ToExpression<GS_LiteralExpression>(expression);

                return TransformLiteralExpression(session,
                                                  literalExpression);
            }
            case ExpressionType::ArrayExpression: {
                auto arrayExpression = ToExpression<GS_ArrayExpression>(expression);

                return TransformArrayExpression(session,
                                                arrayExpression);
            }
            case ExpressionType::RangeExpression: {
                auto rangeExpression = ToExpression<GS_RangeExpression>(expression);

                return TransformRangeExpression(session,
                                                rangeExpression);
            }
            case ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<GS_UnaryExpression>(expression);

                return TransformUnaryExpression(session,
                                                unaryExpression);
            }
            case ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<GS_BinaryExpression>(expression);

                return TransformBinaryExpression(session,
                                                 binaryExpression);
            }
            case ExpressionType::IndexExpression: {
                auto indexExpression = ToExpression<GS_IndexExpression>(expression);

                return TransformIndexExpression(session,
                                                indexExpression);
            }
            case ExpressionType::CastExpression: {
                auto castExpression = ToExpression<GS_CastExpression>(expression);

                return TransformCastExpression(session,
                                               castExpression);
            }
            case ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<GS_VariableUsingExpression>(expression);

                return TransformVariableUsingExpression(session,
                                                        variableUsingExpression);
            }
            case ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<GS_FunctionCallingExpression>(expression);

                return TransformFunctionCallingExpression(session,
                                                          functionCallingExpression);
            }
        }

        return nullptr;
    }

    GSNodePtr GS_Transformer::SuperTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                              NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto &nodes = translationUnitDeclaration->GetNodes();

        for (auto &node : nodes) {
            auto transformedNode = TransformNode(session,
                                                 node);

            node.swap(transformedNode);
        }

        return translationUnitDeclaration;
    }

    GSNodePtr GS_Transformer::SuperModuleDeclaration(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_ModuleDeclaration> moduleDeclaration) {
        auto &body = moduleDeclaration->GetBody();

        for (auto &declaration : body) {
            auto transformedDeclaration = ToDeclaration(TransformDeclaration(session,
                                                                             declaration));

            declaration.swap(transformedDeclaration);
        }

        return moduleDeclaration;
    }

    GSNodePtr GS_Transformer::SuperImportDeclaration(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_ImportDeclaration> importDeclaration) {
        return importDeclaration;
    }

    GSNodePtr GS_Transformer::SuperFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        auto &statements = functionDeclaration->GetBody();

        for (auto &statement: statements) {
            auto transformedStatement = ToStatement(TransformStatement(session,
                                                                       statement));

            statement.swap(transformedStatement);
        }

        return functionDeclaration;
    }

    GSNodePtr GS_Transformer::SuperVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto &expression = variableDeclarationStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return variableDeclarationStatement;
    }

    GSNodePtr GS_Transformer::SuperAssignmentStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        auto &lvalueExpression = assignmentStatement->GetLValueExpression();
        auto &rvalueExpression = assignmentStatement->GetRValueExpression();

        auto transformedLvalueExpression = ToExpression(TransformExpression(session,
                                                                            lvalueExpression));
        auto transformedRvalueExpression = ToExpression(TransformExpression(session,
                                                                            rvalueExpression));

        lvalueExpression.swap(transformedLvalueExpression);
        rvalueExpression.swap(transformedRvalueExpression);

        return assignmentStatement;
    }

    GSNodePtr GS_Transformer::SuperIfStatement(LRef<Driver::GS_Session> session,
                                               NodePtrLRef<GS_IfStatement> ifStatement) {
        auto &condition = ifStatement->GetCondition();
        auto &ifBody = ifStatement->GetIfBody();
        auto &elseBody = ifStatement->GetElseBody();

        auto transformedCondition = ToExpression(TransformExpression(session,
                                                                     condition));

        condition.swap(transformedCondition);

        for (auto &statement : ifBody) {
            auto transformedStatement = ToStatement(TransformStatement(session,
                                                                       statement));

            statement.swap(transformedStatement);
        }

        for (auto &statement : elseBody) {
            auto transformedStatement = ToStatement(TransformStatement(session,
                                                                       statement));

            statement.swap(transformedStatement);
        }

        return ifStatement;
    }

    GSNodePtr GS_Transformer::SuperForStatement(LRef<Driver::GS_Session> session,
                                                NodePtrLRef<GS_ForStatement> forStatement) {
        auto &expression = forStatement->GetExpression();
        auto &body = forStatement->GetBody();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        for (auto &statement : body) {
            auto transformedStatement = ToStatement(TransformStatement(session,
                                                                       statement));

            statement.swap(transformedStatement);
        }

        return forStatement;
    }

    GSNodePtr GS_Transformer::SuperWhileStatement(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_WhileStatement> whileStatement) {
        auto &condition = whileStatement->GetCondition();
        auto &body = whileStatement->GetBody();

        auto transformedCondition = ToExpression(TransformExpression(session,
                                                                     condition));

        condition.swap(transformedCondition);

        for (auto &statement : body) {
            auto transformedStatement = ToStatement(TransformStatement(session,
                                                                       statement));

            statement.swap(transformedStatement);
        }

        return whileStatement;
    }

    GSNodePtr GS_Transformer::SuperMatchStatement(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_MatchStatement> matchStatement) {
        auto &expression = matchStatement->GetExpression();
        auto &arms = matchStatement->GetArms();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        for (auto &arm : arms) {
            auto &pattern = arm.GetPattern();
            auto &body = arm.GetBody();

            auto transformedPattern = ToExpression(TransformExpression(session,
                                                                       pattern));

            pattern.swap(transformedPattern);

            for (auto &statement : body) {
                auto transformedStatement = ToStatement(TransformStatement(session,
                                                                           statement));

                statement.swap(transformedStatement);
            }
        }

        return matchStatement;
    }

    GSNodePtr GS_Transformer::SuperReturnStatement(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_ReturnStatement> returnStatement) {
        auto &expression = returnStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return returnStatement;
    }

    GSNodePtr GS_Transformer::SuperExpressionStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        auto &expression = expressionStatement->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return expressionStatement;
    }

    GSNodePtr GS_Transformer::SuperLiteralExpression(LRef<Driver::GS_Session> session,
                                                     NodePtrLRef<GS_LiteralExpression> literalExpression) {
        return literalExpression;
    }

    GSNodePtr GS_Transformer::SuperArrayExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        auto &expressions = arrayExpression->GetExpressions();

        for (auto &expression : expressions) {
            auto transformedExpression = ToExpression(TransformExpression(session,
                                                                          expression));

            expression.swap(transformedExpression);
        }

        return arrayExpression;
    }

    GSNodePtr GS_Transformer::SuperRangeExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_RangeExpression> rangeExpression) {
        auto &startExpression = rangeExpression->GetStartExpression();
        auto &endExpression = rangeExpression->GetEndExpression();

        auto transformedStartExpression = ToExpression(TransformExpression(session,
                                                                           startExpression));
        auto transformedEndExpression = ToExpression(TransformExpression(session,
                                                                         endExpression));

        startExpression.swap(transformedStartExpression);
        endExpression.swap(transformedEndExpression);

        return rangeExpression;
    }

    GSNodePtr GS_Transformer::SuperUnaryExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        auto &expression = unaryExpression->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return unaryExpression;
    }

    GSNodePtr GS_Transformer::SuperBinaryExpression(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        auto &firstExpression = binaryExpression->GetFirstExpression();
        auto &secondExpression = binaryExpression->GetSecondExpression();

        auto transformedFirstExpression = ToExpression(TransformExpression(session,
                                                                           firstExpression));
        auto transformedSecondExpression = ToExpression(TransformExpression(session,
                                                                            secondExpression));

        firstExpression.swap(transformedFirstExpression);
        secondExpression.swap(transformedSecondExpression);

        return binaryExpression;
    }

    GSNodePtr GS_Transformer::SuperIndexExpression(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_IndexExpression> indexExpression) {
        auto &expression = indexExpression->GetExpression();
        auto &index = indexExpression->GetIndex();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));
        auto transformedIndex = ToExpression(TransformExpression(session,
                                                                 index));

        expression.swap(transformedExpression);
        index.swap(transformedIndex);

        return indexExpression;
    }

    GSNodePtr GS_Transformer::SuperCastExpression(LRef<Driver::GS_Session> session,
                                                  NodePtrLRef<GS_CastExpression> castExpression) {
        auto &expression = castExpression->GetExpression();

        auto transformedExpression = ToExpression(TransformExpression(session,
                                                                      expression));

        expression.swap(transformedExpression);

        return castExpression;
    }

    GSNodePtr GS_Transformer::SuperVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {
        return variableUsingExpression;
    }

    GSNodePtr GS_Transformer::SuperFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                             NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {
        return functionCallingExpression;
    }

    GSNodePtr GS_Transformer::TransformNode(LRef<Driver::GS_Session> session,
                                            LRef<GSNodePtr> node) {
        return SuperNode(session,
                         node);
    }

    GSNodePtr GS_Transformer::TransformDeclaration(LRef<Driver::GS_Session> session,
                                                   LRef<GSDeclarationPtr> declaration) {
        return SuperDeclaration(session,
                                declaration);
    }

    GSNodePtr GS_Transformer::TransformStatement(LRef<Driver::GS_Session> session,
                                                 LRef<GSStatementPtr> statement) {
        return SuperStatement(session,
                              statement);
    }

    GSNodePtr GS_Transformer::TransformExpression(LRef<Driver::GS_Session> session,
                                                  LRef<GSExpressionPtr> expression) {
        return SuperExpression(session,
                               expression);
    }

    GSNodePtr GS_Transformer::TransformTranslationUnitDeclaration(LRef<Driver::GS_Session> session,
                                                                  NodePtrLRef<GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        return SuperTranslationUnitDeclaration(session,
                                               translationUnitDeclaration);
    }

    GSNodePtr GS_Transformer::TransformModuleDeclaration(LRef<Driver::GS_Session> session,
                                                         NodePtrLRef<GS_ModuleDeclaration> moduleDeclaration) {
        return SuperModuleDeclaration(session,
                                      moduleDeclaration);
    }

    GSNodePtr GS_Transformer::TransformImportDeclaration(LRef<Driver::GS_Session> session,
                                                         NodePtrLRef<GS_ImportDeclaration> importDeclaration) {
        return SuperImportDeclaration(session,
                                      importDeclaration);
    }

    GSNodePtr GS_Transformer::TransformFunctionDeclaration(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_FunctionDeclaration> functionDeclaration) {
        return SuperFunctionDeclaration(session,
                                        functionDeclaration);
    }

    GSNodePtr GS_Transformer::TransformVariableDeclarationStatement(LRef<Driver::GS_Session> session,
                                                                    NodePtrLRef<GS_VariableDeclarationStatement> variableDeclarationStatement) {
        return SuperVariableDeclarationStatement(session,
                                                 variableDeclarationStatement);
    }

    GSNodePtr GS_Transformer::TransformAssignmentStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_AssignmentStatement> assignmentStatement) {
        return SuperAssignmentStatement(session,
                                        assignmentStatement);
    }

    GSNodePtr GS_Transformer::TransformIfStatement(LRef<Driver::GS_Session> session,
                                                   NodePtrLRef<GS_IfStatement> ifStatement) {
        return SuperIfStatement(session,
                                ifStatement);
    }

    GSNodePtr GS_Transformer::TransformForStatement(LRef<Driver::GS_Session> session,
                                                    NodePtrLRef<GS_ForStatement> forStatement) {
        return SuperForStatement(session,
                                 forStatement);
    }

    GSNodePtr GS_Transformer::TransformWhileStatement(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_WhileStatement> whileStatement) {
        return SuperWhileStatement(session,
                                   whileStatement);
    }

    GSNodePtr GS_Transformer::TransformMatchStatement(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_MatchStatement> matchStatement) {
        return SuperMatchStatement(session,
                                   matchStatement);
    }

    GSNodePtr GS_Transformer::TransformReturnStatement(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_ReturnStatement> returnStatement) {
        return SuperReturnStatement(session,
                                    returnStatement);
    }

    GSNodePtr GS_Transformer::TransformExpressionStatement(LRef<Driver::GS_Session> session,
                                                           NodePtrLRef<GS_ExpressionStatement> expressionStatement) {
        return SuperExpressionStatement(session,
                                        expressionStatement);
    }

    GSNodePtr GS_Transformer::TransformLiteralExpression(LRef<Driver::GS_Session> session,
                                                         NodePtrLRef<GS_LiteralExpression> literalExpression) {
        return SuperLiteralExpression(session,
                                      literalExpression);
    }

    GSNodePtr GS_Transformer::TransformArrayExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_ArrayExpression> arrayExpression) {
        return SuperArrayExpression(session,
                                    arrayExpression);
    }

    GSNodePtr GS_Transformer::TransformRangeExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_RangeExpression> rangeExpression) {
        return SuperRangeExpression(session,
                                    rangeExpression);
    }

    GSNodePtr GS_Transformer::TransformUnaryExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_UnaryExpression> unaryExpression) {
        return SuperUnaryExpression(session,
                                    unaryExpression);
    }

    GSNodePtr GS_Transformer::TransformBinaryExpression(LRef<Driver::GS_Session> session,
                                                        NodePtrLRef<GS_BinaryExpression> binaryExpression) {
        return SuperBinaryExpression(session,
                                     binaryExpression);
    }

    GSNodePtr GS_Transformer::TransformIndexExpression(LRef<Driver::GS_Session> session,
                                                       NodePtrLRef<GS_IndexExpression> indexExpression) {
        return SuperIndexExpression(session,
                                    indexExpression);
    }

    GSNodePtr GS_Transformer::TransformCastExpression(LRef<Driver::GS_Session> session,
                                                      NodePtrLRef<GS_CastExpression> castExpression) {
        return SuperCastExpression(session,
                                   castExpression);
    }

    GSNodePtr GS_Transformer::TransformVariableUsingExpression(LRef<Driver::GS_Session> session,
                                                               NodePtrLRef<GS_VariableUsingExpression> variableUsingExpression) {
        return SuperVariableUsingExpression(session,
                                            variableUsingExpression);
    }

    GSNodePtr GS_Transformer::TransformFunctionCallingExpression(LRef<Driver::GS_Session> session,
                                                                 NodePtrLRef<GS_FunctionCallingExpression> functionCallingExpression) {
        return SuperFunctionCallingExpression(session,
                                              functionCallingExpression);
    }

}
