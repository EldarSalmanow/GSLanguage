#ifndef GSLANGUAGE_GS_TOOLCHAINS_H
#define GSLANGUAGE_GS_TOOLCHAINS_H

#include <Driver/GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    /**
     *
     */
    class GS_Linker {
    public:

        /**
         *
         * @param units
         * @return
         */
        virtual Bool Link(Vector<GSTranslationUnitPtr> units) = 0;
    };

    /**
     *
     */
    class GS_Toolchain {
    public:

        /**
         *
         * @return
         */
        virtual SharedPtr<GS_Linker> GetLinker() = 0;
    };

    /**
     *
     */
    class GS_MSVCToolchain : public GS_Toolchain {
    public:

        /**
         *
         * @return
         */
        SharedPtr<GS_Linker> GetLinker() override;
    };

}

#endif //GSLANGUAGE_GS_TOOLCHAINS_H
