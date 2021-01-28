#include "include/Compiler/Util/GS_Arguments.h"
#include "include/Compiler/Reader/GS_Reader.h"
#include "include/Compiler/Lexer/GS_Lexer.h"
#include "include/Compiler/Parser/GS_Parser.h"

#include "test/Tests.h"

using namespace GSLanguageCompiler;

/**
 * Function for parsing command line arguments and generating config for compiling
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Object std::shared_ptr<GS_Arguments> (configs for compiling)
 */
std::shared_ptr<GS_Arguments> parseArguments(int argc, char *argv[]) {
    std::shared_ptr<GS_Arguments> arguments(new GS_Arguments(argc, argv));

    if (argc < 3) {
        arguments->printUsage();
    }

    arguments->parseArguments();

    return arguments;
}

/**
 * Start compiler function
 * @param arguments Command line arguments before argument analyzing
 */
void CompilingStart(std::shared_ptr<GS_Arguments> &arguments) {
    // reading input file
    std::shared_ptr<GS_Reader> reader(new GS_Reader(arguments->getFilename()));
    std::vector<std::string> input = reader->readFile();

    // lexer analyzing
    std::shared_ptr<GS_Lexer> lexer(new GS_Lexer(input));
    std::vector<GS_Token> tokens = lexer->tokenize();

    // lexer testing
    Testing::printTokenTypes(tokens);

    // parser analyzing
//    std::shared_ptr<GS_Parser> parser(new GS_Parser(tokens));
//    std::vector<std::shared_ptr<GS_Expression>> expressions = parser->parse();

    // parser testing
//    Testing::printExpressions(expressions);
}

/**
 * Main function in GSLanguageCompiler
 * @return Status number for operation system
 */
int main(int argc, char *argv[]) {
    std::shared_ptr<GS_Arguments> arguments = parseArguments(argc, argv);

    if (arguments->getFilename().empty()) return 0;

    try {
        CompilingStart(arguments);
    }
    catch (Exceptions::_GS_Exception &exception) {
        std::cerr << exception << std::endl;
    }
    catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
    return 0;
}
