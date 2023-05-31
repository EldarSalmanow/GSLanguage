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
     * Class for translating AST to LLVM IR code
     */
    class GS_LLVMCodeGenerator : public GS_CodeGenerator {
    public:

        /*
         *
         * GS_LLVMCodeGenerator PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for LLVM code generator
         */
        GS_LLVMCodeGenerator();

    public:

        /*
         *
         * GS_LLVMCodeGenerator PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating LLVM code generator
         * @return LLVM code generator ptr
         */
        static std::shared_ptr<GS_LLVMCodeGenerator> Create();

    public:

        /*
         *
         * GS_LLVMCodeGenerator PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Translating translation unit declaration to LLVM IR code and returning it in code holder
         * @param session Session
         * @param unit Translation unit declaration
         * @return LLVM code holder
         */
        GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                 AST::GSTranslationUnitDeclarationPtr unit) override;

    public:

        /*
         *
         * GS_LLVMCodeGenerator PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for code generator backend type
         * @return Code generator backend type
         */
        CGBackendType GetBackendType() const override;
    };

    /**
     * Class for writing LLVM code holder to file
     */
    class GS_LLVMCodeWriter : public GS_CodeWriter {
    public:

        /*
         *
         * GS_LLVMCodeWriter PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for LLVM code writer
         */
        GS_LLVMCodeWriter();

    public:

        /*
         *
         * GS_LLVMCodeWriter PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating LLVM code writer
         * @return LLVM code writer ptr
         */
        static std::shared_ptr<GS_LLVMCodeWriter> Create();

    public:

        /*
         *
         * GS_LLVMCodeWriter PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Writing LLVM code holder to file
         * @param session Session
         * @param fileName File name
         * @param codeHolder LLVM code holder
         * @return Void return
         */
        Void Write(LRef<Driver::GS_Session> session,
                   UString fileName,
                   GSCodeHolderPtr codeHolder) override;

    public:

        /*
         *
         * GS_LLVMCodeWriter PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for code writer backend type
         * @return Code writer backend type
         */
        CGBackendType GetBackendType() const override;
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
         * Getter for code generator
         * @return Code generator
         */
        GSCodeGeneratorPtr GetCodeGenerator() override;

        /**
         * Getter for code writer
         * @return Code writer
         */
        GSCodeWriterPtr GetCodeWriter() override;

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
