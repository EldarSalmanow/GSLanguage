#ifndef GSLANGUAGE_GS_STARTER_H
#define GSLANGUAGE_GS_STARTER_H

#include "../../include/Debug/GS_Timer.h"
#include "../../include/Debug/GS_Debug.h"

#include "../../include/Compiler/Util/GS_Arguments.h"
#include "../../include/Compiler/Reader/GS_Reader.h"
#include "../../include/Compiler/Lexer/GS_Lexer.h"
#include "../../include/Compiler/Parser/GS_Parser.h"

namespace Starter {

    using namespace GSLanguageCompiler;

    /**
     * Class for starting GSLanguageCompiler
     */
    class GS_Starter {
    public:
        /**
         * Starting compiler
         * @param argc Number of arguments
         * @param argv Array of arguments
         * @return Status number for operation system
         */
        static int startCompiler(int argc, char *argv[]);

    private:
        /**
        * Start compiling function
        * @param arguments Command line arguments before argument analyzing
        */
        static void startCompiling(GSArgumentsPointer &arguments);

        /**
        * Function for parsing command line arguments and generating config for compiling
        * @param argc Number of arguments
        * @param argv Array of arguments
        * @return Configs for compiling
        */
        static GSArgumentsPointer parseArguments(int argc, char **argv);
    };

}

#endif //GSLANGUAGE_GS_STARTER_H
