#ifndef GSLANGUAGE_GS_CODEGENERATOR_H
#define GSLANGUAGE_GS_CODEGENERATOR_H

#include <CodeGenerator/GS_CGContext.h>

namespace GSLanguageCompiler::CodeGenerator {

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
         * Creating code generator
         * @param backend Code generation backend
         * @return Code generator ptr
         */
        static std::shared_ptr<GS_CodeGenerator> Create(CGBackend backend);

        /**
         * Creating LLVM code generator
         * @return LLVM code generator
         */
        static std::shared_ptr<GS_CodeGenerator> CreateLLVMCG();

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
