#ifndef GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
#define GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H

#include <Driver/GS_TranslationUnitConfig.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for representation all session configs of compiler
     */
    class GS_CompilerSessionConfig {
    public:

        /**
         * Constructor for compiler session config
         * @param unitConfigs Unit configs
         * @param outputName Output name
         */
        GS_CompilerSessionConfig(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName);

    public:

        /**
         * Creating compiler config
         * @param unitConfigs Unit configs
         * @param outputName Output name
         * @return Compiler config ptr
         */
        static SharedPtr<GS_CompilerSessionConfig> Create(GSTranslationUnitConfigPtrArray unitConfigs, UString outputName);

        /**
         * Creating compiler config with parsing command line arguments
         * @param argc Arguments counter
         * @param argv Arguments value
         * @return Compiler config ptr
         */
        static SharedPtr<GS_CompilerSessionConfig> Create(I32 argc, Ptr<Ptr<C8>> argv);

    public:

        /**
         * Getter for unit configs
         * @return Unit configs
         */
        GSTranslationUnitConfigPtrArray GetUnitConfigs() const;

        /**
         * Getter for output name
         * @return Output name
         */
        UString GetOutputName() const;

    private:

        /**
         * Unit configs
         */
        GSTranslationUnitConfigPtrArray _unitConfigs;

        /**
         * Output name
         */
        UString _outputName;
    };

    /**
     * Compiler session config ptr type
     */
    using GSCompilerSessionConfigPtr = SharedPtr<GS_CompilerSessionConfig>;

    /**
     * Compiler session config ptr array type
     */
    using GSCompilerSessionConfigPtrArray = Vector<GSCompilerSessionConfigPtr>;

}

#endif //GSLANGUAGE_GS_COMPILERSESSIONCONFIG_H
