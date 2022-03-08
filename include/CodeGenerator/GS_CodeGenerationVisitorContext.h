#ifndef GSLANGUAGE_GS_CODEGENERATIONVISITORCONTEXT_H
#define GSLANGUAGE_GS_CODEGENERATIONVISITORCONTEXT_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_CodeGenerationVisitorContext : public AST::GS_VisitorContext {
    public:


    };

    /**
     *
     */
    using GSCodeGenerationVisitorContextPtr = SharedPtr<GS_CodeGenerationVisitorContext>;

}

#endif //GSLANGUAGE_GS_CODEGENERATIONVISITORCONTEXT_H
