#ifndef GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_CODEGENERATIONVISITOR_H

#include <AST/GS_Visitor.h>

#include <CodeGenerator/GS_TranslationModule.h>

namespace GSLanguageCompiler::CodeGenerator {

    template<typename T>
    class GS_CodeGenerationVisitor : public AST::GS_Visitor<T> {
    public:

        /**
         *
         * @return
         */
        virtual GSTranlsationModulePtr getTranslationModule() = 0;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
