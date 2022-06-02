#ifndef GSLANGUAGE_GS_CGPASS_H
#define GSLANGUAGE_GS_CGPASS_H

#include <AST/GS_Pass.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation pass
     */
    class GS_CGPass : public AST::GS_Pass {};

    /**
     * Code generation pass ptr
     */
    using GSCGPassPtr = std::shared_ptr<GS_CGPass>;

}

#endif //GSLANGUAGE_GS_CGPASS_H
