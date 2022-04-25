#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <CodeGenerator/GS_CGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

    /**
     * Code generation backend
     */
    enum class CGBackend {
        LLVM
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
        explicit GS_CodeGenerator(CGBackend backend);

    public:

        /**
         * Create code generator
         * @param backend Code generation backend
         * @return Code generator ptr
         */
        static SharedPtr<GS_CodeGenerator> Create(CGBackend backend);

        /**
         * Create LLVM code generator
         * @return LLVM code generator
         */
        static SharedPtr<GS_CodeGenerator> CreateLLVMCG();

    public:

        /**
         * Generate code from translation unit declaration
         * @param translationUnitDeclaration Translation unit declaration
         * @return
         */
        Void Generate(LRef<AST::GSTranslationUnitDeclarationPtr> translationUnitDeclaration);

    public:

        /**
         * Getter for context
         * @return Code generation context
         */
        GSCGContextPtr GetContext();

    private:

        /**
         * Code generation backend
         */
        CGBackend _backend;

        /**
         * Code generation context
         */
        GSCGContextPtr _context;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATOR_H
