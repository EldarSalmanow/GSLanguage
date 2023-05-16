#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Driver/GS_Session.h>

#include <CodeGenerator/GS_CGBackend.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeGenerator {
    public:

        GS_CodeGenerator(LRef<Driver::GS_Session> session,
                         AST::GSTranslationUnitDeclarationPtr unit);

    public:

        static GS_CodeGenerator Create(LRef<Driver::GS_Session> session,
                                       AST::GSTranslationUnitDeclarationPtr unit);

    public:

        GSCodeHolderPtr Generate(GSCGBackendPtr backend);

    private:

        LRef<Driver::GS_Session> _session;

        AST::GSTranslationUnitDeclarationPtr _unit;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
