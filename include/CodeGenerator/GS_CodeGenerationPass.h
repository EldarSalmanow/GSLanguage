#ifndef GSLANGUAGE_GS_CODEGENERATIONPASS_H
#define GSLANGUAGE_GS_CODEGENERATIONPASS_H

#include <AST/GS_Pass.h>

#include <CodeGenerator/GS_CodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeGenerationVisitor;

    class GS_CodeGenerationPass : public AST::GS_Pass {
    public:

        explicit GS_CodeGenerationPass(SharedPtr<GS_CodeGenerationVisitor> visitor);
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONPASS_H
