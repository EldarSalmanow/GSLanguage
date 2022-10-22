#include <IO/IO.h>

#include <Debug/Debug.h>

#include <Driver/Driver.h>

namespace GSLanguageCompiler::CodeGenerator {

    class CGBackend {

    };

    using GSCGBackendPtr = std::shared_ptr<CGBackend>;

}

using namespace GSLanguageCompiler;

class Context {
public:

    void g(IO::GSMessageHandlerPtr MH) {
        auto Message = IO::Message::Create("Hello, World!",
                                           IO::MessageLevel::Note);

        MH->Write(Message);
    }

    void f() {
        auto StdStreams = IO::GS_StdIOStreamsManager::Create();

        auto SM = IO::GS_SourceManager::Create();

        auto MH = IO::GS_MessageHandler::Create(StdStreams->GetStdOutStream(), SM);

        g(MH);
    }

    Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
            IO::GSMessageHandlerPtr messageHandler,
            IO::GSSourceManagerPtr sourceManager,
            IO::GSOutStreamPtr outputStream,
            AST::GSASTContextPtr context);

private:


};

void f() {
    auto StdStreams = IO::GS_StdIOStreamsManager::Create();
    auto SM = IO::GS_SourceManager::Create();
    auto MH = IO::GS_MessageHandler::Create(StdStreams->GetStdOutStream(), SM);
    auto OutStream = IO::GS_OutFileStream::CreateOutFile("main.exe");
    auto AstContext = AST::GS_ASTContext::Create();

    auto Context_ = std::make_shared<Context>(StdStreams, MH, SM, OutStream, AstContext);
}

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
 * High level entry point for GSLanguageCompiler
 * @param argc Arguments counter
 * @param argv Arguments values
 * @return Compiler result
 */
I32 GSMain(I32 argc, Ptr<Ptr<C>> argv) {
    auto globalContextInitializingResult = Driver::GS_GlobalContext::Initialize();

    if (globalContextInitializingResult) {
        return 1;
    }

    auto compilingResult = Driver::GS_Compiler::Start(argc, argv);

    auto programResult = StaticCast<I32>(compilingResult);

    return programResult;
}

/**
 * Low level entry point for GSLanguageCompiler
 * @param argc Arguments counter
 * @param argv Arguments values
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
//    return Test();

    return GSMain(argc, argv);
}
