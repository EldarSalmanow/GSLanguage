#include <LLVM/GS_LLVMCGVisitor.h>

#include <LLVM/GS_LLVMCGPass.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCGPass::GS_LLVMCGPass(LRef<GSLLVMCGContextPtr> context)
            : _context(context) {}

    Void GS_LLVMCGPass::Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) {
        GS_LLVMCGVisitor visitor(_context);

        visitor.GenerateTranslationUnitDeclaration(translationUnitDeclaration);
    }

    GSCGPassPtr CreateLLVMCGPass(LRef<GSLLVMCGContextPtr> context) {
        return std::make_shared<GS_LLVMCGPass>(context);
    }

}
