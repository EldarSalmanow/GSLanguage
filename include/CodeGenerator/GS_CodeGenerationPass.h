#ifndef GSLANGUAGE_GS_CODEGENERATIONPASS_H
#define GSLANGUAGE_GS_CODEGENERATIONPASS_H

#include <AST/GS_Pass.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CompilerUnit;

    class GS_CodeGenerationPass : public AST::GS_Pass {
    public:

        explicit GS_CodeGenerationPass(GS_CompilerUnit *compilerUnit);

    public:

        GS_CompilerUnit *getCompilerUnit();

    public:

        Void runForDeclarations(AST::GSDeclarationPtrArray &declarations) override;

    private:

        GS_CompilerUnit *_compilerUnit;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONPASS_H
