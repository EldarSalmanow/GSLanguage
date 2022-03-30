#ifndef GSLANGUAGE_GS_COMPILERSESSION_H
#define GSLANGUAGE_GS_COMPILERSESSION_H

#include <Driver/GS_CompilerSessionConfig.h>

#include <Driver/GS_TranslationUnitsManager.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation compiler sessions
     */
    class GS_CompilerSession {
    public:

        /**
         * Constructor for compiler session
         * @param compilerSessionConfig Compiler session config
         */
        explicit GS_CompilerSession(GSCompilerSessionConfigPtr compilerSessionConfig);

    public:

        /**
         * Creating compiler session
         * @param compilerSessionConfig Compiler session config
         * @return Compiler session ptr
         */
        static SharedPtr<GS_CompilerSession> Create(GSCompilerSessionConfigPtr compilerSessionConfig);

    public:

        /**
         * Compiler session entry point for create and startup session
         * @param argc Arguments counter
         * @param argv Arguments value
         * @return Compiler result
         */
        static CompilingResult Start(I32 argc, Ptr<Ptr<C8>> argv);

    public:

        /**
         * Run compiler session
         * @return Compiling result
         */
        CompilingResult Run();

    public:

        /**
         * Getter for compiler session config
         * @return Compiler session config
         */
        GSCompilerSessionConfigPtr GetConfig() const;

    private:

        /**
         * Compiler session config
         */
        GSCompilerSessionConfigPtr _config;
    };

    /**
     *
     */
    using GSCompilerSessionPtr = SharedPtr<GS_CompilerSession>;

    /**
     *
     */
    using GSCompilerSessionPtrArray = Vector<GSCompilerSessionPtr>;

}

#endif //GSLANGUAGE_GS_COMPILERSESSION_H
