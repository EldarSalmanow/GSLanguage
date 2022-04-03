#include <args.hxx>

#include <GS_CompilerSessionConfig.h>

namespace GSLanguageCompiler::Driver {

    GS_CompilerSessionConfig::GS_CompilerSessionConfig(GSTranslationUnitConfigPtrArray unitConfigs, Vector<UString> librariesPaths, UString outputName)
            : _unitConfigs(std::move(unitConfigs)), _librariesPaths(std::move(librariesPaths)), _outputName(std::move(outputName)) {}

    SharedPtr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(GSTranslationUnitConfigPtrArray unitConfigs, Vector<UString> librariesPaths, UString outputName) {
        return std::make_shared<GS_CompilerSessionConfig>(std::move(unitConfigs), std::move(librariesPaths), std::move(outputName));
    }

    SharedPtr<GS_CompilerSessionConfig> GS_CompilerSessionConfig::Create(I32 argc, Ptr<Ptr<C8>> argv) {
        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser, "help", "Display help description about GSLanguageCompiler", {'h', "help"});
        args::ValueFlag<String> inputFile(parser, "file", "File for compiling", {'f', "file"}, args::Options::Required);
        args::ValueFlag<String> outputFile(parser, "output", "Output file", {'o', "out"}, args::Options::Required);
        args::ValueFlag<String> librariesPaths(parser, "libPaths", "Libraries paths", {"libpaths"});

        try {
            parser.ParseCLI(argc, argv);
        } catch (LRef<args::Help> help) {
            std::cout << parser;

            return nullptr;
        } catch (LRef<args::Error> error) {
            std::cout << error.what() << std::endl << std::endl;

            std::cout << parser;

            return nullptr;
        }

        GSTranslationUnitConfigPtrArray unitConfigs;

        if (inputFile) {
            auto unitConfig = GS_TranslationUnitConfig::Create(inputFile.Get());

            unitConfigs.emplace_back(unitConfig);
        }

        Vector<UString> libPaths;

        UString path;

        for (auto &symbol : librariesPaths.Get()) {
            if (symbol == ';') {
                libPaths.emplace_back(path);

                path = U""_us;

                continue;
            }

            path += StaticCast<CodePoint>(symbol);
        }

        if (!path.Empty()) {
            libPaths.emplace_back(path);

            path = U""_us;
        }

        UString outputName;

        if (outputFile) {
            outputName = outputFile.Get();
        }

        auto compilerConfig = GS_CompilerSessionConfig::Create(unitConfigs, libPaths, outputName);

        return compilerConfig;
    }

    GSTranslationUnitConfigPtrArray GS_CompilerSessionConfig::GetUnitConfigs() const {
        return _unitConfigs;
    }

    Vector<UString> GS_CompilerSessionConfig::GetLibrariesPaths() const {
        return _librariesPaths;
    }

    UString GS_CompilerSessionConfig::GetOutputName() const {
        return _outputName;
    }

}
