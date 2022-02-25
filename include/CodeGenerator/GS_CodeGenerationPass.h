#ifndef GSLANGUAGE_GS_CODEGENERATIONPASS_H
#define GSLANGUAGE_GS_CODEGENERATIONPASS_H

#include <AST/GS_Pass.h>

#include <CodeGenerator/GS_CodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     * @tparam T
     */
    template<typename T>
    class GS_CodeGenerationPass : public AST::GS_Pass {
    public:

        /**
         *
         * @param visitor
         */
        explicit GS_CodeGenerationPass(SharedPtr<GS_CodeGenerationVisitor<T>> visitor);
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONPASS_H
