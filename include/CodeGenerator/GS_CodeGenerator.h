#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <Starter/GS_Runnable.h>

#include <CodeGenerator/GS_CodeGenVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     *
     */
    class GS_CodeGenerator : public Starter::GS_Runnable {
    public:

        GS_CodeGenerator();

    public:

        GSVoid run(Starter::GSContextPtr &context) override;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
