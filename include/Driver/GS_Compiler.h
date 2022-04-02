#ifndef GSLANGUAGE_GS_COMPILER_H
#define GSLANGUAGE_GS_COMPILER_H

#include <Driver/GS_CompilerSessionsManager.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for startup and manage GSLanguageCompiler
     */
    class GS_Compiler {
    public:

        /**
         * Constructor for compiler
         * @param sessionConfigs Compiler session configs
         */
        explicit GS_Compiler(GSCompilerSessionConfigPtrArray sessionConfigs);

    public:

        /**
         * Creating compiler
         * @param sessionConfigs Compiler session configs
         * @return Compiler ptr
         */
        static SharedPtr<GS_Compiler> Create(GSCompilerSessionConfigPtrArray sessionConfigs);

        /**
         * Creating compiler
         * @return Compiler ptr
         */
        static SharedPtr<GS_Compiler> Create();

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
         * Adding session config
         * @param sessionConfig Session config
         * @return
         */
        Void AddSessionConfig(GSCompilerSessionConfigPtr sessionConfig);

    public:

        /**
         * Getter for compiler session configs
         * @return Compiler session configs
         */
        GSCompilerSessionConfigPtrArray GetSessionConfigs() const;

    private:

        /**
         * Compiler session configs
         */
        GSCompilerSessionConfigPtrArray _sessionConfigs;
    };

}

#endif //GSLANGUAGE_GS_COMPILER_H
