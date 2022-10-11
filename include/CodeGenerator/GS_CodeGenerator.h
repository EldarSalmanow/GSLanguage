#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <CodeGenerator/GS_CGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeHolder {
    public:

        virtual ~GS_CodeHolder();
    };

    using GSCodeHolderPtr = std::shared_ptr<GS_CodeHolder>;

    class GS_CGBackend {
    public:

        virtual ~GS_CGBackend();

    public:

        virtual GSCodeHolderPtr Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) = 0;
    };

    using GSCGBackendPtr = std::shared_ptr<GS_CGBackend>;

    template<typename T>
    class CGContext {
    public:


    };

    class GS_LLVMCodeHolder : public GS_CodeHolder {
    public:

        GS_LLVMCodeHolder(UString moduleName, LRef<llvm::LLVMContext> moduleContext);

    public:

        static std::shared_ptr<GS_LLVMCodeHolder> Create(UString moduleName, LRef<llvm::LLVMContext> moduleContext);

    public:

        LRef<llvm::Module> GetLLVMModule();

    private:

        std::shared_ptr<llvm::Module> _module;
    };

    using GSLLVMCodeHolderPtr = std::shared_ptr<GS_LLVMCodeHolder>;

    class GS_LLVMCGBackend : public GS_CGBackend {
    public:

        explicit GS_LLVMCGBackend(Driver::GSContextPtr context);

    public:

        static std::shared_ptr<GS_LLVMCGBackend> Create(Driver::GSContextPtr context);

    public:

        GSCodeHolderPtr Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration) override;

    private:

        Driver::GSContextPtr _context;
    };

    template<>
    class CGContext<GS_LLVMCGBackend> {
    public:

        CGContext(std::shared_ptr<llvm::LLVMContext> llvmContext, Driver::GSContextPtr context)
                : _llvmContext(std::move(llvmContext)), _llvmModule(std::shared_ptr<llvm::Module>()), _context(std::move(context)) {}

    public:

        static CGContext<GS_LLVMCGBackend> Create(std::shared_ptr<llvm::LLVMContext> llvmContext, Driver::GSContextPtr context) {
            return CGContext<GS_LLVMCGBackend>(std::move(llvmContext), std::move(context));
        }

        static CGContext<GS_LLVMCGBackend> Create(Driver::GSContextPtr context) {
            return CGContext<GS_LLVMCGBackend>::Create(std::make_shared<llvm::LLVMContext>(), std::move(context));
        }

    public:

        LRef<llvm::LLVMContext> GetLLVMContext();

        LRef<llvm::Module> GetLLVMModule();

        Driver::GSContextPtr GetContext();

    private:

        std::shared_ptr<llvm::LLVMContext> _llvmContext;

        std::shared_ptr<llvm::Module> _llvmModule;

        Driver::GSContextPtr _context;
    };

    /**
     * CLass for generating code from AST
     */
    class GS_CodeGenerator {
    public:

        /**
         * Constructor for code generator
         * @param backend Code generation backend
         */
//        explicit GS_CodeGenerator(CGBackend backend);

        explicit GS_CodeGenerator(Driver::GSContextPtr context);

    public:

        /**
         * Creating code generator
         * @param backend Code generation backend
         * @return Code generator ptr
         */
//        static std::shared_ptr<GS_CodeGenerator> Create(CGBackend backend);

        /**
         * Creating LLVM code generator
         * @return LLVM code generator
         */
//        static std::shared_ptr<GS_CodeGenerator> CreateLLVMCG();

        static std::shared_ptr<GS_CodeGenerator> Create(Driver::GSContextPtr context);

    public:

        /**
         * Generate code from translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
//        Void Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration);

        GSCodeHolderPtr Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration, GSCGBackendPtr backend);

    public:

        /**
         * Getter for context
         * @return Code generation context
         */
//        GSCGContextPtr GetContext();

    private:

        /**
         * Code generation backend
         */
//        CGBackend _backend;

        /**
         * Code generation context
         */
//        GSCGContextPtr _context;

        Driver::GSContextPtr _context;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
