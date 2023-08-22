#ifndef GSLANGUAGE_GS_LLVMBACKEND_H
#define GSLANGUAGE_GS_LLVMBACKEND_H

#pragma warning(push)
#pragma warning(disable : 4624)
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#pragma warning(pop)

#include <CodeGenerator/GS_Backend.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * LLVM code holder
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
         * Getter for backend type
         * @return Backend type
         */
        BackendType GetBackendType() const override;

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
     * LLVM backend
     */
    class GS_LLVMBackend : public GS_Backend {
    public:

        /*
         *
         * GS_LLVMBackend PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for LLVM backend
         */
        GS_LLVMBackend();

    public:

        /*
         *
         * GS_LLVMBackend PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating LLVM backend
         * @return LLVM backend
         */
        static std::shared_ptr<GS_LLVMBackend> Create();

    public:

        /*
         *
         * GS_LLVMBackend PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Translating node to LLVM IR code and returning it in LLVM code holder
         * @param session Session
         * @param node Node
         * @return LLVM code holder
         */
        GSCodeHolderPtr Generate(LRef<Driver::GS_Session> session,
                                 AST::GSNodePtr node) override;

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

        /**
         * Linking files
         * @param session Session
         * @param inputFileNames Input filenames
         * @param outputFileName Output filename
         * @return Void return
         */
        Void Link(LRef<Driver::GS_Session> session,
                  std::vector<UString> inputFileNames,
                  UString outputFileName) override;

    public:

        /*
         *
         * GS_LLVMBackend PUBLIC OVERRIDE METHODS
         *
         */

        /**
         * Getter for backend type
         * @return Backend type
         */
        BackendType GetBackendType() const override;
    };

}

#endif //GSLANGUAGE_GS_LLVMBACKEND_H
