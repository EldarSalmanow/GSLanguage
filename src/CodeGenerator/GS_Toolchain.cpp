#include <lld/Common/Driver.h>

#include <GS_Toolchain.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_Linker::~GS_Linker() = default;

    GS_LLDLinker::GS_LLDLinker() = default;

    std::shared_ptr<GS_LLDLinker> GS_LLDLinker::Create() {
        return std::make_shared<GS_LLDLinker>();
    }

    Void GS_LLDLinker::Link(std::vector<UString> input,
                            UString output) {
        std::vector<std::string> command;

        command.emplace_back("GSLanguage.exe");

        for (auto &inputFile : input) {
            command.emplace_back(inputFile.AsUTF8());
        }

        command.emplace_back("/entry:main");
        command.emplace_back("/out:" + output.AsUTF8());

        std::vector<ConstPtr<C>> stringCommand;

        for (auto &string : command) {
            stringCommand.emplace_back(string.c_str());
        }

        auto linkResult = lld::coff::link(stringCommand,
                                          llvm::outs(),
                                          llvm::errs(),
                                          false,
                                          false);
    }

    GS_Toolchain::GS_Toolchain(GSLinkerPtr linker)
            : _linker(std::move(linker)) {}

    std::unique_ptr<GS_Toolchain> GS_Toolchain::Create(GSLinkerPtr linker) {
        return std::make_unique<GS_Toolchain>(std::move(linker));
    }

    std::unique_ptr<GS_Toolchain> GS_Toolchain::Create() {
        auto linker = GS_LLDLinker::Create();

        return GS_Toolchain::Create(linker);
    }

    GSLinkerPtr GS_Toolchain::GetLinker() {
        return _linker;
    }

}
