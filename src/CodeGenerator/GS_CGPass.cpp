#include <LLVM/GS_LLVMCGVisitor.h>

#include <GS_CGPass.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CGPass::GS_CGPass(CGBackend backend, LRef<GSCGContextPtr> context)
            : _backend(backend), _context(context) {}

    Void GS_CGPass::Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        switch (_backend) {
            case CGBackend::LLVM:
                auto llvmContext = std::reinterpret_pointer_cast<GS_LLVMCGContext>(_context);

                GS_LLVMCGVisitor visitor(llvmContext);

                visitor.GenerateTranslationUnitDeclaration(translationUnitDeclaration);

                break;
        }
    }

    AST::GSPassPtr CreateCGPass(CGBackend backend, LRef<GSCGContextPtr> context) {
        return std::make_shared<GS_CGPass>(backend, context);
    }

}
