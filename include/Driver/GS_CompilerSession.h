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
     * Compiler session ptr type
     */
    using GSCompilerSessionPtr = SharedPtr<GS_CompilerSession>;

    /**
     * Compiler session ptr array type
     */
    using GSCompilerSessionPtrArray = Vector<GSCompilerSessionPtr>;

}

#endif //GSLANGUAGE_GS_COMPILERSESSION_H
