#include <lld/Common/Driver.h>

#include <Driver/GS_Toolchains.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for using MSVC linker tool
     */
    class GS_MSVCLinker : public GS_Linker {
    public:

        /**
         * Linking translation units to executable file
         * @param units Units for linking
         * @param outputName Output file name
         * @return Is successfully linking
         */
        Bool Link(Vector<GSTranslationUnitPtr> units, UString outputName) override {
            Vector<ConstPtr<C8>> command;

            auto stringCommand = MakeCommand(units, outputName);

            for (auto &string : stringCommand) {
                command.emplace_back(string.c_str());
            }

            auto result = lld::coff::link(command, llvm::outs(), llvm::errs(), false, false);

            return result;
        }

    private:

        /**
         * Making string command for linking
         * @param units Units for linking
         * @param outputName Output file name
         * @return String command
         */
        Vector<String> MakeCommand(Vector<GSTranslationUnitPtr> units, UString outputName) {
            Vector<String> command;

            command.emplace_back("GSLanguage.exe");

            for (auto &unit : units) {
                command.emplace_back(unit->GetConfig()->GetInputName().AsString() + ".o");
            }

            command.emplace_back("/entry:main");

            command.emplace_back("/out:" + outputName.AsString());

            return command;
        }
    };

    GSLinkerPtr GS_MSVCToolchain::GetLinker() {
        return std::make_shared<GS_MSVCLinker>();
    }

}
