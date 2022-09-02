#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H

#include <vector>

#include <optional>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Driver {

    class GS_Arguments {
    public:

        GS_Arguments(std::vector<UString> inputFileNames, UString outputFileName);

    public:

        static GS_Arguments Create(std::vector<UString> inputFileNames, UString outputFileName);

        static GS_Arguments Create(std::vector<UString> inputFileNames);

        static GS_Arguments Create();

    public:

        static std::optional<GS_Arguments> Create(I32 argc, Ptr<Ptr<C>> argv);

    public:

        std::vector<UString> GetInputFileNames() const;

        UString GetOutputFileName() const;

    private:

        std::vector<UString> _inputFileNames;

        UString _outputFileName;
    };

}

#endif //GSLANGUAGE_GS_ARGUMENTS_H
