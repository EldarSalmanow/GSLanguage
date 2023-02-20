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

        /*
         *
         * GS_Arguments PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for arguments
         * @param inputFileNames Input file names
         * @param outputFileName Output file name
         */
        GS_Arguments(std::vector<UString> inputFileNames,
                     UString outputFileName);

    public:

        /*
         *
         * GS_Arguments PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating arguments
         * @param inputFileNames Input file names
         * @param outputFileName Output file name
         * @return Arguments
         */
        static GS_Arguments Create(std::vector<UString> inputFileNames,
                                   UString outputFileName);

        /**
         * Creating arguments with default output file name
         * @param inputFileNames Input file names
         * @return Arguments
         * @todo Replace output name to ?
         */
        static GS_Arguments Create(std::vector<UString> inputFileNames);

        /**
         * Creating default arguments
         * @return Arguments
         * @todo Remove ?
         */
        static GS_Arguments Create();

        /**
         * Creating and parsing arguments from command line arguments
         * @param argc Arguments counter
         * @param argv Arguments values
         * @return Arguments
         * @todo Rewrite
         */
        static std::optional<GS_Arguments> Create(I32 argc, Ptr<Ptr<C>> argv);

    public:

        /*
         *
         * GS_Arguments PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for input file names
         * @return Input file names
         */
        ConstLRef<std::vector<UString>> GetInputFileNames() const;

        /**
         * Getter for output file name
         * @return Output file name
         */
        ConstLRef<UString> GetOutputFileName() const;

    private:

        /*
         *
         * GS_Arguments PRIVATE FIELDS
         *
         */

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
