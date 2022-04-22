#include <lld/Common/Driver.h>

#include <Driver/GS_Toolchains.h>

namespace GSLanguageCompiler::Driver {

    // TODO update or remove

    class LinkerCommandBuilder {
    public:

        virtual ~LinkerCommandBuilder() = default;

    public:

        virtual Vector<String> Build() = 0;

    public:

        virtual Void AddInput(UString name) = 0;

        virtual Void AddOutput(UString name) = 0;

        virtual Void AddEntry(UString name) = 0;
    };

    class MSVCLinkerCommandBuilder : public LinkerCommandBuilder {
    public:

        Vector<String> Build() override {
            Vector<String> command;

            command.emplace_back("GSLanguage.exe");

            for (auto &input : _inputs) {
                command.emplace_back(input.AsString());
            }

            if (!_entry.Empty()) {
                command.emplace_back("/entry:" + _entry.AsString());
            }

            if (!_output.Empty()) {
                command.emplace_back("/out:" + _output.AsString());
            }

            _inputs.clear();
            _output = ""_us;
            _entry = ""_us;

            return command;
        }

    public:

        Void AddInput(UString name) override {
            _inputs.emplace_back(std::move(name));
        }

        Void AddOutput(UString name) override {
            _output = std::move(name);
        }

        Void AddEntry(UString name) override {
            _entry = std::move(name);
        }

    private:

        Vector<UString> _inputs;

        UString _output;

        UString _entry;
    };

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
            auto LCB = std::make_shared<MSVCLinkerCommandBuilder>();

            for (auto &unit : units) {
                LCB->AddInput(unit->GetConfig()->GetInputName().AsString() + ".o");
            }

            LCB->AddEntry("main");

            LCB->AddOutput(outputName);

            return LCB->Build();

//            Vector<String> command;
//
//            for (auto &unit : units) {
//                command.emplace_back(unit->GetConfig()->GetInputName().AsString() + ".o");
//            }
//
//            command.emplace_back("/entry:main");
//
//            command.emplace_back("/out:" + outputName.AsString());
//
//            return command;
        }
    };

    GSLinkerPtr GS_MSVCToolchain::GetLinker() {
        return std::make_shared<GS_MSVCLinker>();
    }

}
