#include <GS_CodeGenerationPass.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_CodeGenerationPass::GS_CodeGenerationPass(SharedPtr<GS_CodeGenerationVisitor> visitor)
            : AST::GS_Pass(visitor) {}

}
