#ifndef GSLANGUAGE_GS_COMPILER_H
#define GSLANGUAGE_GS_COMPILER_H

#include <Driver/GS_TranslationUnitsManager.h>

#include <Driver/GS_CompilerConfig.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for startup and manage GSLanguageCompiler
     */
    class GS_Compiler {
    public:

        /**
         * Constructor for compiler
         * @param config Compiler config
         */
        explicit GS_Compiler(GSCompilerConfigPtr config);

    public:

        /**
         * Creating compiler
         * @param config Compiler config
         * @return Compiler ptr
         */
        static SharedPtr<GS_Compiler> Create(GSCompilerConfigPtr config);

    public:

        /**
         * Compiler entry point for create and startup compiler
         * @param argc Arguments counter
         * @param argv Arguments value
         * @return Compiler result. 0 - success, any results - failure
         */
        static I32 Start(I32 argc, Ptr<Ptr<C8>> argv);

    public:

        /**
         * Run compiling process
         * @return Compiling result. 0 - success, any results - failure
         */
        I32 Run();

    public:

        /**
         * Getter for compiler config
         * @return Compiler config
         */
        GSCompilerConfigPtr GetConfig() const;

    private:

        /**
         * Compiler config
         */
        GSCompilerConfigPtr _config;
    };

}

#endif //GSLANGUAGE_GS_COMPILER_H
