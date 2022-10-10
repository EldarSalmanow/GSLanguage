#include <LLVM/GS_LLVMCGPass.h>

#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeHolder::~GS_CodeHolder() = default;

    GS_CGBackend::~GS_CGBackend() = default;

    GS_LLVMCodeHolder::GS_LLVMCodeHolder(UString moduleName, LRef<llvm::LLVMContext> moduleContext)
            : _module(std::make_shared<llvm::Module>(moduleName.AsUTF8(), moduleContext)) {}

    std::shared_ptr<GS_LLVMCodeHolder> GS_LLVMCodeHolder::Create(UString moduleName, LRef<llvm::LLVMContext> moduleContext) {
        return std::make_shared<GS_LLVMCodeHolder>(std::move(moduleName), moduleContext);
    }

    LRef<llvm::Module> GS_LLVMCodeHolder::GetModule() {
        return *_module;
    }

    GS_LLVMCGBackend::GS_LLVMCGBackend(Driver::GSContextPtr context)
            : _context(std::move(context)) {}

    std::shared_ptr<GS_LLVMCGBackend> GS_LLVMCGBackend::Create(Driver::GSContextPtr context) {
        return std::make_shared<GS_LLVMCGBackend>(std::move(context));
    }

    GSCodeHolderPtr GS_LLVMCGBackend::Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        return nullptr;
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
