#ifndef GSLANGUAGE_GS_LLVMCGBACKEND_H
#define GSLANGUAGE_GS_LLVMCGBACKEND_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGenerator/GS_CGBackend.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * LLVM backend code holder
     */
    class GS_LLVMCodeHolder : public GS_CodeHolder {
    public:

        /*
         *
         * GS_LLVMCodeHolder PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for LLVM code holder
         */
        GS_LLVMCodeHolder();

    public:

        /*
         *
         * GS_LLVMCodeHolder PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating LLVM code holder
         * @return LLVM code holder
         */
        static std::shared_ptr<GS_LLVMCodeHolder> Create();

    public:

        /*
         *
         * GS_LLVMCodeHolder PUBLIC METHODS
         *
         */

        /**
         * Creating LLVM module
         * @param moduleName Module name
         * @return LLVM module
         */
        LRef<llvm::Module> CreateModule(UString moduleName);

        /**
         * Destroying LLVM module
         * @return Void return
         */
        Void DestroyModule();

    public:

        /*
         *
         * GS_LLVMCodeHolder PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for LLVM context
         * @return LLVM context
         */
        LRef<llvm::LLVMContext> GetContext();

        /**
         * Getter for LLVM module
         * @return LLVM module
         */
        LRef<llvm::Module> GetModule();

    public:

        /*
         *
         * GS_LLVMCodeHolder PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for code holder backend type
         * @return Code holder backend type
         */
        CGBackendType GetBackendType() const override;

    private:

        /*
         *
         * GS_LLVMCodeHolder PRIVATE FIELDS
         *
         */

        /**
         * LLVM context
         */
        std::unique_ptr<llvm::LLVMContext> _context;

        /**
         * LLVM module
         */
        std::unique_ptr<llvm::Module> _module;
    };

    /**
     * LLVM code generation backend
     */
    class GS_LLVMCGBackend : public GS_CGBackend {
    public:

        /*
         *
         * GS_LLVMCGBackend PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for LLVM code generation backend
         */
        GS_LLVMCGBackend();

    public:

        /*
         *
         * GS_LLVMCGBackend PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating LLVM code generation backend
         * @return LLVM code generation backend
         */
        static std::shared_ptr<GS_LLVMCGBackend> Create();

    public:

        /*
         *
         * GS_LLVMCGBackend PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Translating translation unit declaration to LLVM IR code
         * @param session Session
         * @param unit Translation unit declaration
         * @return LLVM code holder
         */
        GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                 AST::GSTranslationUnitDeclarationPtr unit) override;

        /**
         * Writing LLVM code holder to file
         * @param session Session
         * @param fileName File name
         * @param codeHolder Code holder
         * @return Void return
         */
        Void Write(LRef<Driver::GS_Session> session,
                   UString fileName,
                   GSCodeHolderPtr codeHolder) override;

    public:

        /*
         *
         * GS_LLVMCGBackend PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for code generation backend type
         * @return Code generation backend type
         */
        CGBackendType GetBackendType() const override;
    };

}

#endif //GSLANGUAGE_GS_LLVMCGBACKEND_H
