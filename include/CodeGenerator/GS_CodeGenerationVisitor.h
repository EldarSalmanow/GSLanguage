#ifndef GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_CODEGENERATIONVISITOR_H

#include <CodeGenerator/GS_CompilerUnit.h>

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeGenerationVisitor : public AST::GS_Visitor {
    public:

        virtual GSCompilerUnitPtr getCompilerUnit() = 0;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
