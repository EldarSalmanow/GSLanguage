#ifndef GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_CODEGENERATIONVISITOR_H

#include <AST/GS_Visitor.h>

#include <CodeGenerator/GS_CompilerUnit.h>

namespace GSLanguageCompiler::CodeGenerator {

    template<typename T>
    class GS_CodeGenerationVisitor : public AST::GS_BaseVisitor<T> {
    public:

        /**
         *
         * @return
         */
        virtual GSCompilerUnitPtr getCompilerUnit() = 0;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
