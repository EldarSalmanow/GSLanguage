#ifndef GSLANGUAGE_GS_COMPILERUNIT_H
#define GSLANGUAGE_GS_COMPILERUNIT_H

#include <CodeGenerator/GS_LLVMIncluding.h>

#include <GSCrossPlatform/GS_CrossPlatformTypes.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CompilerUnit {
    public:

        explicit GS_CompilerUnit(const String& name);

    public:

        LLVM::Context &getContext();

        LLVM::Module &getModule();

        LLVM::IRBuilder &getBuilder();

    private:

        LLVM::Context _context;

        LLVM::Module _module;

        LLVM::IRBuilder _builder;
    };

}

#endif //GSLANGUAGE_GS_COMPILERUNIT_H
