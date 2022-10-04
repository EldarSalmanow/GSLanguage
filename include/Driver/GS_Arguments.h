#ifndef GSLANGUAGE_GS_ARGUMENTS_H
#define GSLANGUAGE_GS_ARGUMENTS_H

#include <vector>

#include <optional>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Class for parsing and containing arguments
     */
    class GS_Arguments {
    public:

        /**
         * Constructor for arguments
         * @param inputFileNames Input file names
         * @param outputFileName Output file name
         */
        GS_Arguments(std::vector<UString> inputFileNames, UString outputFileName);

    public:

        /**
         * Creating arguments
         * @param inputFileNames Input file names
         * @param outputFileName Output file name
         * @return Arguments
         */
        static GS_Arguments Create(std::vector<UString> inputFileNames, UString outputFileName);

        /**
         * Creating arguments
         * @param inputFileNames Input file names
         * @return Arguments
         */
        static GS_Arguments Create(std::vector<UString> inputFileNames);

        /**
         * Creating arguments
         * @return Arguments
         */
        static GS_Arguments Create();

    public:

        /**
         * Creating and parsing arguments
         * @param argc Arguments counter
         * @param argv Arguments values
         * @return Arguments
         */
        static std::optional<GS_Arguments> Create(I32 argc, Ptr<Ptr<C>> argv);

    public:

        /**
         * Getter for input file names
         * @return Input file names
         */
        std::vector<UString> GetInputFileNames() const;

        /**
         * Getter for output file name
         * @return Output file name
         */
        UString GetOutputFileName() const;

    private:

        /**
         * Input file names
         */
        std::vector<UString> _inputFileNames;

        /**
         * Output file name
         */
        UString _outputFileName;
    };

}

#endif //GSLANGUAGE_GS_ARGUMENTS_H