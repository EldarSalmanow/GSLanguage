#ifndef GSLANGUAGE_GS_TOOLCHAINS_H
#define GSLANGUAGE_GS_TOOLCHAINS_H

#include <Driver/GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for linking translation units with external tools
     */
    class GS_Linker {
    public:

        /**
         * Linking translation units to executable file
         * @param units Units for linking
         * @param outputName Output file name
         * @return Is successfully linking
         */
        virtual Bool Link(std::vector<GSTranslationUnitPtr> units, UString outputName) = 0;
    };

    /**
     * Linker ptr type
     */
    using GSLinkerPtr = std::shared_ptr<GS_Linker>;

    /**
     * Class for getting any group tools
     */
    class GS_Toolchain {
    public:

        /**
         * Getter for linker tool
         * @return Linker tool
         */
        virtual GSLinkerPtr GetLinker() = 0;
    };

    /**
     * Toolchain ptr type
     */
    using GSToolchainPtr = std::shared_ptr<GS_Toolchain>;

    /**
     * Class for getting MSVC group tools
     */
    class GS_MSVCToolchain : public GS_Toolchain {
    public:

        /**
         * Getting MSVC linker tool
         * @return MSVC linker tool
         */
        GSLinkerPtr GetLinker() override;
    };

}

#endif //GSLANGUAGE_GS_TOOLCHAINS_H
