#include <Driver/GS_Session.h>

#include <AST/GS_ASTBuilder.h>

#include <Passes/GS_ConstantFoldingPass.h>

namespace GSLanguageCompiler::Optimizer {

    // TODO: add folding values with non I32 type

    AST::GSValuePtr FoldConstants(LRef<Driver::GS_Session> session,
                                  AST::UnaryOperation operation,
                                  ConstLRef<AST::GSValuePtr> value) {
        if (auto i8Value = AST::ToValue<AST::GS_I8Value>(value)) {
            auto number = i8Value->GetI8Value();

            I8 result;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    result = -number;

                    break;
            }

            return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateI8Value(result);
        } else if (auto i16Value = AST::ToValue<AST::GS_I16Value>(value)) {
            auto number = i16Value->GetI16Value();

            I16 result;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    result = -number;

                    break;
            }

            return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateI16Value(result);
        } else if (auto i32Value = AST::ToValue<AST::GS_I32Value>(value)) {
            auto number = i32Value->GetI32Value();

            I32 result;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    result = -number;

                    break;
            }

            return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateI32Value(result);
        } else if (auto i64Value = AST::ToValue<AST::GS_I64Value>(value)) {
            auto number = i64Value->GetI64Value();

            I64 result;

            switch (operation) {
                case AST::UnaryOperation::Minus:
                    result = -number;

                    break;
            }

            return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateI64Value(result);
        }

        return nullptr;
    }

    AST::GSValuePtr FoldConstants(LRef<Driver::GS_Session> session,
                                  AST::BinaryOperation operation,
                                  ConstLRef<AST::GSValuePtr> firstValue,
                                  ConstLRef<AST::GSValuePtr> secondValue) {
        if (auto firstI32Value = AST::ToValue<AST::GS_I32Value>(firstValue)) {
            if (auto secondI32Value = AST::ToValue<AST::GS_I32Value>(secondValue)) {
                auto firstNumber  = firstI32Value->GetI32Value();
                auto secondNumber = secondI32Value->GetI32Value();

                I32 result;

                switch (operation) {
                    case AST::BinaryOperation::Plus:
                        result = firstNumber + secondNumber;

                        break;
                    case AST::BinaryOperation::Minus:
                        result = firstNumber - secondNumber;

                        break;
                    case AST::BinaryOperation::Star:
                        result = firstNumber * secondNumber;

                        break;
                    case AST::BinaryOperation::Slash:
                        result = firstNumber / secondNumber;

                        break;
                }

                return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateI32Value(result);
            }
        }

        return nullptr;
    }

    GS_ConstantFoldingTransformer::GS_ConstantFoldingTransformer() = default;

    AST::GSNodePtr GS_ConstantFoldingTransformer::TransformUnaryExpression(LRef<Driver::GS_Session> session,
                                                                           AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression) {
        unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(GS_Transformer::TransformUnaryExpression(session,
                                                                                                              unaryExpression));

        auto expression = unaryExpression->GetExpression();
        auto operation  = unaryExpression->GetUnaryOperation();

        if (auto constantExpression = AST::ToExpression<AST::GS_ConstantExpression>(expression)) {
            auto value = constantExpression->GetValue();

            if (auto result = FoldConstants(session,
                                            operation,
                                            value)) {
                return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateConstantExpression(result);
            }
        }

        return unaryExpression;
    }

    AST::GSNodePtr GS_ConstantFoldingTransformer::TransformBinaryExpression(LRef<Driver::GS_Session> session,
                                                                            AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression) {
        binaryExpression = AST::ToExpression<AST::GS_BinaryExpression>(GS_Transformer::TransformBinaryExpression(session,
                                                                                                                 binaryExpression));

        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();
        auto operation = binaryExpression->GetBinaryOperation();

        if (auto firstConstantExpression = AST::ToExpression<AST::GS_ConstantExpression>(firstExpression)) {
            if (auto secondConstantExpression = AST::ToExpression<AST::GS_ConstantExpression>(secondExpression)) {
                auto firstValue = firstConstantExpression->GetValue();
                auto secondValue = secondConstantExpression->GetValue();

                if (auto result = FoldConstants(session,
                                                operation,
                                                firstValue,
                                                secondValue)) {
                    return AST::GS_ASTBuilder::Create(session.GetASTContext())->CreateConstantExpression(result);
                }
            }
        }

        return binaryExpression;
    }

    AST::GSPassPtr CreateConstantFoldingPass() {
        return std::make_shared<GS_ConstantFoldingPass>();
    }

}
