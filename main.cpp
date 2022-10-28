#include <Driver/GS_CompilationUnit.h>

void f() {
    auto CU = GSLanguageCompiler::Driver::GS_CompilationUnit::Create(nullptr, nullptr);

    CU.G
}

#include <Debug/Debug.h>

#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

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

class CompilationUnit {
public:

    CompilationUnit(IO::GSSourcePtr source, Driver::GSContextPtr context);

public:

    static std::shared_ptr<CompilationUnit> Create(IO::GSSourcePtr source, Driver::GSContextPtr context);

public:

    Driver::CompilingResult Compile();

public:

    IO::GSSourcePtr GetSource() const;

    Lexer::GSTokenArray GetTokens() const;

    AST::GSNodePtr GetNode() const;

    Semantic::GSTableOfSymbolsPtr GetTableOfSymbols() const;

    Driver::GSContextPtr GetContext() const;

    U64 GetId() const;

private:

    IO::GSSourcePtr _source;

    Lexer::GSTokenArray _tokens;

    AST::GSNodePtr _node;

    Semantic::GSTableOfSymbolsPtr _tableOfSymbols;

    Driver::GSContextPtr _context;

    U64 _id;
};

using CompilationUnitPtr = std::shared_ptr<CompilationUnit>;

using CompilationUnitPtrArray = std::vector<CompilationUnitPtr>;

class CompilationUnitManager {
public:

    explicit CompilationUnitManager(CompilationUnitPtrArray compilationUnits);

public:

    static std::shared_ptr<CompilationUnitManager> Create(CompilationUnitPtrArray compilationUnits);

    static std::shared_ptr<CompilationUnitManager> Create();

public:

    U64 AddCompilationUnit(CompilationUnitPtr compilationUnit);

    CompilationUnitPtr GetCompiltionUnit(U64 compilationUnitId);

public:

    CompilationUnitPtrArray GetCompilationUnits() const;

private:

    CompilationUnitPtrArray _compilationUnits;
};

#include <Semantic/Semantic.h>

void f() {
    auto Context = Driver::GS_Context::Create();

    auto CUM = CompilationUnitManager::Create();

    auto CompilationUnitId = CUM->AddCompilationUnit(CompilationUnit::Create(IO::GS_Source::CreateString("func main() {}"), Context));

    auto CU = CUM->GetCompiltionUnit(CompilationUnitId);

    auto Func = AST::GS_FunctionDeclaration::Create("main", AST::GS_FunctionSignature::Create(Semantic::GS_I32Type::Create()));

    auto TOS = CU->GetTableOfSymbols();

    Semantic::AddFunction(Func, TOS);
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
    return GSMain(argc, argv);
}
