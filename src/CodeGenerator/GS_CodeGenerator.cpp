#include <LLVM/GS_LLVMCGPass.h>

#include <GS_CodeGenerator.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerator::GS_CodeGenerator(CGBackend backend)
            : _backend(backend), _context(nullptr) {}

    std::shared_ptr<GS_CodeGenerator> GS_CodeGenerator::Create(CGBackend backend) {
        return std::make_shared<GS_CodeGenerator>(backend);
    }

    std::shared_ptr<GS_CodeGenerator> GS_CodeGenerator::CreateLLVMCG() {
        return GS_CodeGenerator::Create(CGBackend::LLVM);
    }

    Void GS_CodeGenerator::Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        if (_context != nullptr) {
            _context.reset();
        }

        auto passManager = AST::GS_PassManager::Create();

        switch (_backend) {
            case CGBackend::LLVM:
                _context = std::make_shared<GS_LLVMCGContext>();

                auto llvmContext = std::reinterpret_pointer_cast<GS_LLVMCGContext>(_context);

                passManager->AddPass(CreateLLVMCGPass(llvmContext));

                break;
        }

        passManager->Run(translationUnitDeclaration);
    }

    GSCGContextPtr GS_CodeGenerator::GetContext() {
        return _context;
    }

}
