#include <LLVM/GS_LLVMCodeHolder.h>
#include <LLVM/GS_LLVMCGVisitor.h>

#include <GS_CGPass.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CGPass::GS_CGPass(CGBackend backend, LRef<GSCodeHolderPtr> codeHolder)
            : _backend(backend), _codeHolder(codeHolder) {}

    Void GS_CGPass::Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        switch (_backend) {
            case CGBackend::LLVM:
                auto llvmCodeHolder = std::reinterpret_pointer_cast<GS_LLVMCodeHolder>(_codeHolder);

                GS_LLVMCGVisitor visitor(llvmCodeHolder);

                visitor.GenerateTranslationUnitDeclaration(translationUnitDeclaration);

                // TODO remove

                llvmCodeHolder->GetModule().print(llvm::errs(), nullptr);

                break;
        }
    }

}
