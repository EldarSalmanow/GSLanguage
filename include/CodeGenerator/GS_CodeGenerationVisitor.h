#ifndef GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_CODEGENERATIONVISITOR_H

#include <AST/GS_Visitor.h>

#include <CodeGenerator/GS_CodeGenerationVisitorContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    template<typename T>
    class GS_CodeGenerationVisitor : public AST::GS_Visitor<T> {
    public:

        explicit GS_CodeGenerationVisitor(GSCodeGenerationVisitorContextPtr context)
                : AST::GS_Visitor<T>(context) {}
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
