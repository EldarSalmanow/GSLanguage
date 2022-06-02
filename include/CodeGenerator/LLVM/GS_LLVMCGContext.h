#ifndef GSLANGUAGE_GS_LLVMCGCONTEXT_H
#define GSLANGUAGE_GS_LLVMCGCONTEXT_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_CGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Class for containing information about LLVM code generation
     */
    class GS_LLVMCGContext : public GS_CGContext {
    public:

        /**
         * Constructor for LLVM code generation context
         */
        GS_LLVMCGContext();

    public:

        /**
         * Destructor for LLVM code generation context
         */
        ~GS_LLVMCGContext() override;

    public:

        /**
         * Creating LLVM code generation context
         * @return LLVM code generation context ptr
         */
        static std::shared_ptr<GS_LLVMCGContext> Create();

    public:

        /**
         * Create LLVM IR module
         * @param name Name
         * @return
         */
        Void CreateModule(UString name);

        /**
         * Destroy LLVM IR module
         * @return
         */
        Void DestroyModule();

    public:

        /**
         * Getter for LLVM context
         * @return LLVM context
         */
        LRef<llvm::LLVMContext> GetContext();

        /**
         * Getter for LLVM IR module
         * @return LLVM IR module
         */
        LRef<llvm::Module> GetModule();

    public:

        /**
         * Getter for code generation backend
         * @return Code generation backend
         */
        CGBackend GetBackend() override;

    private:

        /**
         * LLVM context
         */
        std::unique_ptr<llvm::LLVMContext> _context;

        /**
         * LLVM IR module
         */
        std::unique_ptr<llvm::Module> _module;
    };

    /**
     * LLVM code generation context ptr type
     */
    using GSLLVMCGContextPtr = std::shared_ptr<GS_LLVMCGContext>;

}

#endif //GSLANGUAGE_GS_LLVMCGCONTEXT_H
