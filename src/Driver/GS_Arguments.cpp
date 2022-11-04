#include <args.hxx>

#include <GS_GlobalContext.h>

#include <GS_Arguments.h>

namespace GSLanguageCompiler::Driver {

    GS_Arguments::GS_Arguments(std::vector<UString> inputFileNames,
                               UString outputFileName)
            : _inputFileNames(std::move(inputFileNames)),
              _outputFileName(std::move(outputFileName)) {}

    GS_Arguments GS_Arguments::Create(std::vector<UString> inputFileNames,
                                      UString outputFileName) {
        return GS_Arguments(std::move(inputFileNames),
                            std::move(outputFileName));
    }

    GS_Arguments GS_Arguments::Create(std::vector<UString> inputFileNames) {
        // TODO: replace output name to ?

        return GS_Arguments::Create(std::move(inputFileNames),
                                    "a.exe"_us);
    }

    GS_Arguments GS_Arguments::Create() {
        return GS_Arguments::Create(std::vector<UString>(),
                                    UString());
    }

    std::optional<GS_Arguments> GS_Arguments::Create(I32 argc, Ptr<Ptr<C>> argv) {
        args::ArgumentParser parser("GSLanguageCompiler - Compiler for GSLanguage");
        args::HelpFlag helpFlag(parser,
                                "help",
                                "Display help description about GSLanguageCompiler",
                                {'h', "help"});
        args::ValueFlag<std::string> inputFile(parser,
                                               "file",
                                               "File for compiling",
                                               {'f', "file"},
                                               args::Options::Required);
        args::ValueFlag<std::string> outputFile(parser,
                                                "output",
                                                "Output file",
                                                {'o', "out"},
                                                args::Options::Required);

        try {
            parser.ParseCLI(argc, argv);
        } catch (LRef<args::Help> help) {
            UStringStream stringStream;

            stringStream << parser.Help();

            GS_GlobalContext::Out(stringStream.String());

            return std::nullopt;
        } catch (LRef<args::Error> error) {
            UStringStream stringStream;

            stringStream << UString(error.what())
                         << "\n\n"_us
                         << parser.Help();

            GS_GlobalContext::Out(stringStream.String());

            return std::nullopt;
        }

        std::vector<UString> inputFileNames;
        UString outputFileName;

        if (inputFile) {
            inputFileNames.emplace_back(inputFile.Get());
        }

        if (outputFile) {
            outputFileName = outputFile.Get();
        }

        return GS_Arguments::Create(inputFileNames,
                                    outputFileName);
    }

    std::vector<UString> GS_Arguments::GetInputFileNames() const {
        return _inputFileNames;
    }

    UString GS_Arguments::GetOutputFileName() const {
        return _outputFileName;
    }

}
