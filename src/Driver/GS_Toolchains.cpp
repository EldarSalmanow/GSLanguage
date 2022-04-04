#include <lld/Common/Driver.h>

#include <Driver/GS_Toolchains.h>

namespace GSLanguageCompiler::Driver {

    /**
     *
     */
    class GS_MSVCLinker : public GS_Linker {
    public:

        /**
         *
         * @param units
         * @param librariesPaths
         * @param outputName
         * @return
         */
        Bool Link(Vector<GSTranslationUnitPtr> units, Vector<UString> librariesPaths, UString outputName) override {
            Vector<String> command;

            Vector<ConstPtr<C8>> stringCommand;

            command.emplace_back("GSLanguage.exe");

            for (auto &unit : units) {
                command.emplace_back(unit->GetConfig()->GetInputName().AsString() + ".o");
            }

            command.emplace_back("/entry:main");

            command.emplace_back("/out:" + outputName.AsString());

            for (auto &string : command) {
                stringCommand.emplace_back(string.c_str());
            }

            auto result = lld::coff::link(stringCommand, llvm::outs(), llvm::errs(), false, false);

            return result;
        }
    };

    SharedPtr<GS_Linker> GS_MSVCToolchain::GetLinker() {
        return std::make_shared<GS_MSVCLinker>();
    }

}
