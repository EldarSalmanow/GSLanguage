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
                                            LRef<Driver::GS_Session> session) override {
        unaryExpression = AST::ToExpression<AST::GS_UnaryExpression>(SuperUnaryExpression(unaryExpression, session));

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
    auto Session = Driver::GS_Session::Create();

    auto Builder = AST::GS_ASTBuilder::Create();

    auto Expression = Builder->CreateUnaryExpression(AST::UnaryOperation::Minus,
                                                     Builder->CreateUnaryExpression(AST::UnaryOperation::Minus,
                                                                                    Builder->CreateConstantExpression(1)));

    AST::GSExpressionPtrArray Expressions = { Expression };

    auto PM = AST::GS_PassManager::Create();

    PM->AddPass(CreateArithmeticOptimizingPass());

    Debug::DumpAST(Expressions[0], *Session);

    PM->Run(Expressions, *Session);

    Debug::DumpAST(Expressions[0], *Session);

    return 0;
}

//class Scope;
//
//using ScopePtr = std::shared_ptr<Scope>;
//
//using ScopePtrArray = std::vector<ScopePtr>;
//
//class Scope {
//public:
//
//    Scope(AST::GSNodePtrArray nodes, ScopePtr parent, ScopePtrArray childrens);
//
//public:
//
//    static std::shared_ptr<Scope> Create(AST::GSNodePtrArray nodes, ScopePtr parent, ScopePtrArray childrens);
//
//    static std::shared_ptr<Scope> Create(AST::GSNodePtrArray nodes, ScopePtr parent);
//
//    static std::shared_ptr<Scope> Create(ScopePtr parent, ScopePtrArray childrens);
//
//    static std::shared_ptr<Scope> Create(ScopePtr parent);
//
//    static std::shared_ptr<Scope> Create();
//
//public:
//
//    static std::shared_ptr<Scope> CreateGlobal(AST::GSNodePtrArray nodes, ScopePtrArray childrens);
//
//    static std::shared_ptr<Scope> CreateGlobal(AST::GSNodePtrArray nodes);
//
//    static std::shared_ptr<Scope> CreateGlobal(ScopePtrArray childrens);
//
//    static std::shared_ptr<Scope> CreateGlobal();
//
//public:
//
//    Void AddNode(AST::GSNodePtr node);
//
//    Void EraseFromParent();
//
//    Void AddChildren(ScopePtr children);
//
//    Void RemoveChildren(ScopePtr children);
//
//public:
//
//    AST::GSNodePtrArray GetNodes() const;
//
//    ScopePtr GetParent() const;
//
//    ScopePtrArray GetChildrens() const;
//
//public:
//
//    Void SetParent(ScopePtr scope);
//
//private:
//
//    AST::GSNodePtrArray _nodes;
//
//    ScopePtr _parent;
//
//    ScopePtrArray _childrens;
//};
//
//ScopePtr AddFunction(AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration, LRef<ScopePtr> scope) {
//    auto functionScope = Scope::Create(scope);
//
//    scope->AddNode(functionDeclaration);
//
//    return functionScope;
//}

void g() {
    /*
     *
     * main.gs
     *
     * using sum
     *
     * func main() {
     *     var summa = sum::sum(1, 2)
     *
     *     print(summa)
     * }
     *
     * sum.gs
     *
     * func sum(num_1: I32, num_2: I32) -> I32 {
     *     return num_1 + num_2
     * }
     *
     */

//    auto module_scope = Scope::CreateGlobal();
//
//    auto compilation_unit_scope_1 = Scope::Create(module_scope);
//
//    auto main_func = AST::GS_FunctionDeclaration::Create("main",
//                                                         AST::GS_FunctionSignature::Create(Semantic::GS_I32Type::Create()));
//
//    auto main_func_scope = AddFunction(main_func, compilation_unit_scope_1);

//    compilation_unit_scope_1->AddNode(main_func);
//
//    auto main_func_scope = Scope::Create(compilation_unit_scope_1);

//    auto compilation_unit_scope_2 = Scope::Create(module_scope);
//
//    auto sum_func = AST::GS_FunctionDeclaration::Create("sum",
//                                                        AST::GS_FunctionSignature::Create({Semantic::GS_I32Type::Create(), Semantic::GS_I32Type::Create()},
//                                                                                          Semantic::GS_I32Type::Create()));
//
//    compilation_unit_scope_2->AddNode(sum_func);
//
//    auto sum_func_scope = Scope::Create(compilation_unit_scope_2);
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
