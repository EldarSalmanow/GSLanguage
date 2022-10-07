#include <Debug/Debug.h>

#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

class Trans : public AST::GS_Transformer {
public:

    /*
     *
     * - ( - expression ) -> expression
     *
     */
    AST::GSNodePtr TransformUnaryExpression(AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression,
                                            LRef<Driver::GSContextPtr> context) override {
        auto &expression = unaryExpression->GetExpression();

        auto transformedExpression = AST::ToExpression(TransformExpression(expression, context));

        if (auto transformedUnaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(transformedExpression)) {
            auto unaryExpressionOperation = unaryExpression->GetUnaryOperation();
            auto transformedUnaryExpressionOperation = transformedUnaryExpression->GetUnaryOperation();

            AST::GSExpressionPtr resultExpression;

            switch (unaryExpressionOperation) {
                case AST::UnaryOperation::Minus:
                    switch (transformedUnaryExpressionOperation) {
                        case AST::UnaryOperation::Minus:
                            resultExpression = transformedUnaryExpression->GetExpression();

                            break;
                    }

                    break;
            }

            return resultExpression;
        }

        expression.swap(transformedExpression);

        return unaryExpression;
    }
};

class TransPass : public AST::GS_TransformPass<Trans> {};

AST::GSPassPtr CreateTransPass() {
    return std::make_shared<TransPass>();
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    auto PM = AST::GS_PassManager::Create();

    PM->AddPass(CreateTransPass());

    auto Builder = AST::GS_ASTBuilder::Create();

    auto number_1 = Builder->CreateConstantExpression(1);

    auto unaryExpression_1 = Builder->CreateUnaryExpression(AST::UnaryOperation::Minus, number_1);

    AST::GSNodePtr unaryExpression_2 = Builder->CreateUnaryExpression(AST::UnaryOperation::Minus, unaryExpression_1);

    Debug::DumpAST(unaryExpression_2);

    Driver::GSContextPtr ctx = nullptr;

    Trans t;
    unaryExpression_2 = t.TransformNode(unaryExpression_2, ctx);

    Debug::DumpAST(unaryExpression_2);

    return 0;
//    auto globalContextInitializingResult = Driver::GS_GlobalContext::Initialize();
//
//    if (globalContextInitializingResult) {
//        return 1;
//    }
//
//    auto compilingResult = Driver::GS_Compiler::Start(argc, argv);
//
//    auto programResult = StaticCast<I32>(compilingResult);
//
//    return programResult;
}
