#include <GS_CodeGenerationVisitor.h>

#include <GS_CodeGenerationPass.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerationPass::GS_CodeGenerationPass(GS_CompilerUnit *compilerUnit)
            : AST::GS_Pass(std::make_shared<GS_CodeGenerationVisitor>(this)), _compilerUnit(compilerUnit) {}

    GS_CompilerUnit *GS_CodeGenerationPass::getCompilerUnit() {
        return _compilerUnit;
    }

    Void GS_CodeGenerationPass::runForDeclarations(AST::GSDeclarationPtrArray &declarations) {
        for (auto &declaration: declarations) {
            declaration->accept(getVisitor().get());
        }
    }
}
