#include <GS_CodeGenerationPass.h>

namespace GSLanguageCompiler::CodeGenerator {

    template<typename T>
    GS_CodeGenerationPass<T>::GS_CodeGenerationPass(SharedPtr<GS_CodeGenerationVisitor<T>> visitor)
            : AST::GS_Pass(visitor) {}

}
