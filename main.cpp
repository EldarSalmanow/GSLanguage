#include <Debug/Debug.h>

//#include <Lexer/Lexer.h>
//
#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

//class Lexer_ {
//public:
//
//    Lexer_(Driver::GSContextPtr context);
//
//public:
//
//    Lexer::GSTokenArray Lex(IO::GSSourcePtr source);
//};
//
//class Parser {
//public:
//
//    Parser(Driver::GSContextPtr context);
//
//public:
//
//    AST::GSTranslationUnitDeclarationPtr Parse(Lexer::GSTokenArray tokens);
//};
//
//class CodeHolder {
//
//};
//
//using CodeHolderPtr = std::shared_ptr<CodeHolder>;
//
//class CodeGenerator {
//public:
//
//    CodeGenerator(Driver::GSContextPtr context);
//
//public:
//
//    CodeHolderPtr CodeGen(AST::GSTranslationUnitDeclarationPtr translationUnitDeclaration);
//};
//
//void f() {
//    auto ctx = Driver::GS_Context::Create();
//
//    auto src = IO::GS_Source::CreateString("func main() {}");
//
//    Lexer_ l(ctx);
//
//    auto tokens = l.Lex(src);
//
//    Parser p(ctx);
//
//    auto tu = p.Parse(tokens);
//
//    CodeGenerator cg(ctx);
//
//    auto ch = cg.CodeGen(tu);
//}

class ArithmeticOptimizingVisitor : public AST::GS_Transformer {
public:

    /*
     *
     * + ( expression )   -> expression
     *
     * - ( - expression ) -> expression
     *
     */
    AST::GSNodePtr TransformUnaryExpression(AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression,
                                            LRef<Driver::GSContextPtr> context) override {
        unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(SuperUnaryExpression(unaryExpression, context));

        auto &secondExpression = unaryExpression->GetExpression();

        if (auto secondUnaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(secondExpression)) {
            auto firstOperation = unaryExpression->GetUnaryOperation();
            auto secondOperation = secondUnaryExpression->GetUnaryOperation();

            AST::GSExpressionPtr resultExpression;

            switch (firstOperation) {

                // - ( secondUnaryExpression )
                case AST::UnaryOperation::Minus:
                    switch (secondOperation) {

                        // - ( - expression ) -> expression
                        case AST::UnaryOperation::Minus:
                            resultExpression = secondUnaryExpression->GetExpression();

                            break;
                    }

                    break;
            }

            return resultExpression;
        }

        return unaryExpression;
    }
};

class ArithmeticOptimizingPass : public AST::GS_TransformPass<ArithmeticOptimizingVisitor> {};

AST::GSPassPtr CreateArithmeticOptimizingPass() {
    return std::make_shared<ArithmeticOptimizingPass>();
}

I32 Test() {
    auto Context = Driver::GS_Context::Create();

    auto Builder = AST::GS_ASTBuilder::Create();

    auto Expression = Builder->CreateUnaryExpression(AST::UnaryOperation::Minus,
                                                     Builder->CreateUnaryExpression(AST::UnaryOperation::Minus,
                                                                                    Builder->CreateConstantExpression(1)));

    AST::GSExpressionPtrArray Expressions = { Expression };

    auto PM = AST::GS_PassManager::Create();

    PM->AddPass(CreateArithmeticOptimizingPass());

    Debug::DumpAST(Expressions[0], Context);

    PM->Run(Expressions, Context);

    Debug::DumpAST(Expressions[0], Context);

    return 0;
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
//    return Test();

    auto globalContextInitializingResult = Driver::GS_GlobalContext::Initialize();

    if (globalContextInitializingResult) {
        return 1;
    }

    auto compilingResult = Driver::GS_Compiler::Start(argc, argv);

    auto programResult = StaticCast<I32>(compilingResult);

    return programResult;
}
