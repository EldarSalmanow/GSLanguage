#ifndef GSLANGUAGE_GS_LLVMCODEGENERATIONPASS_H
#define GSLANGUAGE_GS_LLVMCODEGENERATIONPASS_H

#include <AST/GS_Pass.h>

#include <CodeGenerator/LLVM/GS_LLVMCodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    // TODO reorganise

    class GS_LLVMCodeGenerationPass : public AST::GS_Pass {
    public:

        Void Run(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override {
            GS_LLVMCodeGenerationVisitor visitor;

            visitor.GenerateTranslationUnitDeclaration(translationUnitDeclaration);
        }
    };

}

#endif //GSLANGUAGE_GS_LLVMCODEGENERATIONPASS_H
