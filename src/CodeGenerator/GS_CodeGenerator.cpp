//#include <LLVM/GS_LLVMCGPass.h>

#include <llvm/IR/IRBuilder.h>

#include <AST/AST.h>

#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    class LLVMCGContext {
    public:

        LLVMCGContext(std::shared_ptr<llvm::LLVMContext> llvmContext, Driver::GSContextPtr context)
                : _llvmContext(std::move(llvmContext)), _context(std::move(context)) {}

    public:

        static std::shared_ptr<LLVMCGContext> Create(std::shared_ptr<llvm::LLVMContext> llvmContext, Driver::GSContextPtr context) {
            return std::make_shared<LLVMCGContext>(std::move(llvmContext), std::move(context));
        }

        static std::shared_ptr<LLVMCGContext> Create(Driver::GSContextPtr context) {
            return LLVMCGContext::Create(std::make_shared<llvm::LLVMContext>(), std::move(context));
        }

    public:

        LRef<llvm::LLVMContext> GetLLVMContext() {
            return *_llvmContext;
        }

        Driver::GSContextPtr GetContext() {
            return _context;
        }

    private:

        std::shared_ptr<llvm::LLVMContext> _llvmContext;

        Driver::GSContextPtr _context;
    };

    using LLVMCGContextPtr = std::shared_ptr<LLVMCGContext>;

    Ptr<llvm::Type> ToLLVMType(Semantic::GSTypePtr type, LRef<llvm::LLVMContext> context) {
        auto typeName = type->GetName();

        if (typeName == "Void"_us) {
            return llvm::Type::getVoidTy(context);
        } else if (typeName == "I32"_us) {
            return llvm::Type::getInt32Ty(context);
        } else if (typeName == "String"_us) {
            return llvm::Type::getInt8PtrTy(context);
        }

        return nullptr;
    }

    Ptr<llvm::Constant> ToLLVMConstant(AST::GSValuePtr value, LRef<llvm::LLVMContext> context, LRef<llvm::IRBuilder<>> builder) {
        auto literalValue = AST::GSValueCast<AST::GS_LiteralValue>(std::move(value));

        auto type = literalValue->GetType();

        auto typeName = type->GetName();

        Ptr<llvm::Type> llvmType;

        if (typeName == "I32"_us) {
            auto number = literalValue->GetValueWithCast<I32>();

            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), number);
        } else if (typeName == "String"_us) {
            auto string = literalValue->GetValueWithCast<UString>();

            return builder.CreateGlobalStringPtr(string.AsUTF8());
        }

        return nullptr;
    }

    class LLVMCGVisitor {
    public:

        LLVMCGVisitor()
                : _codeHolder(GSLLVMCodeHolderPtr()), _builder(std::shared_ptr<llvm::IRBuilder<>>()) {}

//        explicit LLVMCGVisitor(LRef<GSLLVMCGContextPtr> context);

    public:

        Ptr<llvm::Value> GenerateNode(LRef<AST::GSNodePtr> node,
                                      LRef<LLVMCGContextPtr> context) {
            if (node->IsDeclaration()) {
                auto declaration = ToDeclaration(node);

                return GenerateDeclaration(declaration, context);
            }

            if (node->IsStatement()) {
                auto statement = ToStatement(node);

                return GenerateStatement(statement, context);
            }

            if (node->IsExpression()) {
                auto expression = ToExpression(node);

                return GenerateExpression(expression, context);
            }

            return nullptr;
        }

        Ptr<llvm::Value> GenerateDeclaration(LRef<AST::GSDeclarationPtr> declaration,
                                             LRef<LLVMCGContextPtr> context) {
            switch (declaration->GetDeclarationType()) {
                case AST::DeclarationType::TranslationUnitDeclaration: {
                    auto translationUnitDeclaration = ToDeclaration<AST::GS_TranslationUnitDeclaration>(declaration);

                    return GenerateTranslationUnitDeclaration(translationUnitDeclaration, context);
                }
                case AST::DeclarationType::FunctionDeclaration: {
                    auto functionDeclaration = ToDeclaration<AST::GS_FunctionDeclaration>(declaration);

                    return GenerateFunctionDeclaration(functionDeclaration, context);
                }
            }

            return nullptr;
        }

        Ptr<llvm::Value> GenerateStatement(LRef<AST::GSStatementPtr> statement,
                                           LRef<LLVMCGContextPtr> context) {
            switch (statement->GetStatementType()) {
                case AST::StatementType::VariableDeclarationStatement: {
                    auto variableDeclarationStatement = ToStatement<AST::GS_VariableDeclarationStatement>(statement);

                    return GenerateVariableDeclarationStatement(variableDeclarationStatement, context);
                }
                case AST::StatementType::AssignmentStatement: {
                    auto assignmentStatement = ToStatement<AST::GS_AssignmentStatement>(statement);

                    return GenerateAssignmentStatement(assignmentStatement, context);
                }
                case AST::StatementType::ExpressionStatement: {
                    auto expressionStatement = ToStatement<AST::GS_ExpressionStatement>(statement);

                    return GenerateExpressionStatement(expressionStatement, context);
                }
            }

            return nullptr;
        }

        Ptr<llvm::Value> GenerateExpression(LRef<AST::GSExpressionPtr> expression,
                                            LRef<LLVMCGContextPtr> context) {
            switch (expression->GetExpressionType()) {
                case AST::ExpressionType::ConstantExpression: {
                    auto constantExpression = ToExpression<AST::GS_ConstantExpression>(expression);

                    return GenerateConstantExpression(constantExpression, context);
                }
                case AST::ExpressionType::UnaryExpression: {
                    auto unaryExpression = ToExpression<AST::GS_UnaryExpression>(expression);

                    return GenerateUnaryExpression(unaryExpression, context);
                }
                case AST::ExpressionType::BinaryExpression: {
                    auto binaryExpression = ToExpression<AST::GS_BinaryExpression>(expression);

                    return GenerateBinaryExpression(binaryExpression, context);
                }
                case AST::ExpressionType::VariableUsingExpression: {
                    auto variableUsingExpression = ToExpression<AST::GS_VariableUsingExpression>(expression);

                    return GenerateVariableUsingExpression(variableUsingExpression, context);
                }
                case AST::ExpressionType::FunctionCallingExpression: {
                    auto functionCallingExpression = ToExpression<AST::GS_FunctionCallingExpression>(expression);

                    return GenerateFunctionCallingExpression(functionCallingExpression, context);
                }
            }

            return nullptr;
        }

        Ptr<llvm::Value> GenerateTranslationUnitDeclaration(AST::NodePtrLRef<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration,
                                                            LRef<LLVMCGContextPtr> context) {
            auto name = translationUnitDeclaration->GetName();
            auto nodes = translationUnitDeclaration->GetNodes();

            _codeHolder = GS_LLVMCodeHolder::Create(name, context->GetLLVMContext());

            for (auto &node : nodes) {
                GenerateNode(node, context);
            }

            return nullptr;
        }

        Ptr<llvm::Value> GenerateFunctionDeclaration(AST::NodePtrLRef<AST::GS_FunctionDeclaration> functionDeclaration,
                                                     LRef<LLVMCGContextPtr> context) {
            auto name = functionDeclaration->GetName();
            auto signature = functionDeclaration->GetSignature();
            auto body = functionDeclaration->GetBody();

            auto paramTypes = signature.GetParamTypes();
            auto returnType = signature.GetReturnType();

            std::vector<Ptr<llvm::Type>> llvmParamTypes;

            for (auto &paramType : paramTypes) {
                llvmParamTypes.emplace_back(ToLLVMType(paramType, context->GetLLVMContext()));
            }

            auto llvmReturnType = ToLLVMType(returnType, context->GetLLVMContext());

            auto llvmFunctionType = llvm::FunctionType::get(llvmReturnType, llvmParamTypes, false);

            auto llvmFunction = llvm::Function::Create(llvmFunctionType, llvm::Function::LinkageTypes::ExternalLinkage, name.AsUTF8(), _codeHolder->GetLLVMModule());

            auto block = llvm::BasicBlock::Create(context->GetLLVMContext(), "entry", llvmFunction);

            _builder->SetInsertPoint(block);

            for (auto &statement : body) {
                GenerateStatement(statement);
            }

            _builder.CreateRetVoid();

            return llvmFunction;
        }

        Ptr<llvm::Value> GenerateVariableDeclarationStatement(AST::NodePtrLRef<AST::GS_VariableDeclarationStatement> variableDeclarationStatement,
                                                              LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateAssignmentStatement(AST::NodePtrLRef<AST::GS_AssignmentStatement> assignmentStatement,
                                                     LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateExpressionStatement(AST::NodePtrLRef<AST::GS_ExpressionStatement> expressionStatement,
                                                     LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateConstantExpression(AST::NodePtrLRef<AST::GS_ConstantExpression> constantExpression,
                                                    LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateUnaryExpression(AST::NodePtrLRef<AST::GS_UnaryExpression> unaryExpression,
                                                 LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateBinaryExpression(AST::NodePtrLRef<AST::GS_BinaryExpression> binaryExpression,
                                                  LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateVariableUsingExpression(AST::NodePtrLRef<AST::GS_VariableUsingExpression> variableUsingExpression,
                                                         LRef<LLVMCGContextPtr> context);

        Ptr<llvm::Value> GenerateFunctionCallingExpression(AST::NodePtrLRef<AST::GS_FunctionCallingExpression> functionCallingExpression,
                                                           LRef<LLVMCGContextPtr> context);

    public:

        GSLLVMCodeHolderPtr GetCodeHolder();

    private:

//        LRef<llvm::LLVMContext> GetLLVMContext();
//
//        LRef<llvm::Module> GetLLVMModule();

    private:

//        LRef<GSLLVMCGContextPtr> _context;

        GSLLVMCodeHolderPtr _codeHolder;

        std::shared_ptr<llvm::IRBuilder<>> _builder;
    };

    GS_CodeHolder::~GS_CodeHolder() = default;

    GS_CGBackend::~GS_CGBackend() = default;

    GS_LLVMCodeHolder::GS_LLVMCodeHolder(UString moduleName, LRef<llvm::LLVMContext> moduleContext)
            : _module(std::make_shared<llvm::Module>(moduleName.AsUTF8(), moduleContext)) {}

    std::shared_ptr<GS_LLVMCodeHolder> GS_LLVMCodeHolder::Create(UString moduleName, LRef<llvm::LLVMContext> moduleContext) {
        return std::make_shared<GS_LLVMCodeHolder>(std::move(moduleName), moduleContext);
    }

    LRef<llvm::Module> GS_LLVMCodeHolder::GetLLVMModule() {
        return *_module;
    }

    GS_LLVMCGBackend::GS_LLVMCGBackend(Driver::GSContextPtr context)
            : _context(std::move(context)) {}

    std::shared_ptr<GS_LLVMCGBackend> GS_LLVMCGBackend::Create(Driver::GSContextPtr context) {
        return std::make_shared<GS_LLVMCGBackend>(std::move(context));
    }

    GSCodeHolderPtr GS_LLVMCGBackend::Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        llvm::LLVMContext llvmContext;

        auto codeHolder = GS_LLVMCodeHolder::Create(translationUnitDeclaration->GetName(), llvmContext);

        return codeHolder;
    }

    GS_CodeGenerator::GS_CodeGenerator(Driver::GSContextPtr context)
            : _context(std::move(context)) {}

//    GS_CodeGenerator::GS_CodeGenerator(CGBackend backend)
//            : _backend(backend), _context(nullptr) {}
//
//    std::shared_ptr<GS_CodeGenerator> GS_CodeGenerator::Create(CGBackend backend) {
//        return std::make_shared<GS_CodeGenerator>(backend);
//    }
//
//    std::shared_ptr<GS_CodeGenerator> GS_CodeGenerator::CreateLLVMCG() {
//        return GS_CodeGenerator::Create(CGBackend::LLVM);
//    }

    std::shared_ptr<GS_CodeGenerator> GS_CodeGenerator::Create(Driver::GSContextPtr context) {
        return std::make_shared<GS_CodeGenerator>(std::move(context));
    }

//    Void GS_CodeGenerator::Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
//        if (_context != nullptr) {
//            _context.reset();
//        }
//
//        auto passManager = AST::GS_PassManager::Create();
//
//        switch (_backend) {
//            case CGBackend::LLVM:
//                _context = std::make_shared<GS_LLVMCGContext>();
//
//                auto llvmContext = std::reinterpret_pointer_cast<GS_LLVMCGContext>(_context);
//
//                passManager->AddPass(CreateLLVMCGPass(llvmContext));
//
//                break;
//        }
//
//        passManager->Run(translationUnitDeclaration);
//    }

    GSCodeHolderPtr GS_CodeGenerator::Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration, GSCGBackendPtr backend) {
        return backend->Generate(translationUnitDeclaration);
    }

//    GSCGContextPtr GS_CodeGenerator::GetContext() {
//        return _context;
//    }

}
