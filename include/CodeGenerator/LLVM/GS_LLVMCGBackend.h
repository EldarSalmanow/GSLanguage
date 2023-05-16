#ifndef GSLANGUAGE_GS_LLVMCGBACKEND_H
#define GSLANGUAGE_GS_LLVMCGBACKEND_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_CGBackend.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_LLVMCodeHolder : public GS_CodeHolder {
    public:

        GS_LLVMCodeHolder();

    public:

        static std::shared_ptr<GS_LLVMCodeHolder> Create();

    public:

        LRef<llvm::Module> CreateModule(UString moduleName);

        Void DestroyModule();

    public:

        LRef<llvm::LLVMContext> GetContext();

        LRef<llvm::Module> GetModule();

    public:

        CGBackendType GetBackendType() const override;

    private:

        std::unique_ptr<llvm::LLVMContext> _context;

        std::unique_ptr<llvm::Module> _module;
    };

    class GS_LLVMCGBackend : public GS_CGBackend {
    public:

        GS_LLVMCGBackend();

    public:

        static std::shared_ptr<GS_LLVMCGBackend> Create();

    public:

        GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                 AST::GSTranslationUnitDeclarationPtr unit) override;

        Void Write(LRef<Driver::GS_Session> session,
                   UString fileName,
                   GSCodeHolderPtr codeHolder) override;

    public:

        CGBackendType GetBackendType() const override;
    };

}

#endif //GSLANGUAGE_GS_LLVMCGBACKEND_H
