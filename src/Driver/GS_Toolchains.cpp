#include <Driver/GS_Toolchains.h>

namespace GSLanguageCompiler::Driver {

    /**
     *
     */
    class GS_MSVCLinker : public GS_Linker {
    public:

        /**
         *
         * @return
         */
        Bool FindLinker() {
            return true;
        }

    public:

        /**
         *
         * @param units
         * @return
         */
        Bool Link(Vector<GSTranslationUnitPtr> units) override {
            if (!FindLinker()) {
                return false;
            }

            return true;
        }

    private:

        /**
         *
         */
        UString _linkerPath;
    };

    SharedPtr<GS_Linker> GS_MSVCToolchain::GetLinker() {
        return std::make_shared<GS_MSVCLinker>();
    }

}
