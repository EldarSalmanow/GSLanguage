#include "include/Compiler/Util/GS_Arguments.h"
#include "include/Compiler/Reader/GS_Reader.h"
#include "include/Compiler/Lexer/GS_Lexer.h"
#include "include/Compiler/Parser/GS_Parser.h"

#include "test/Tests.h"

/**
 * Start compiler function
 * @param argc Number of console arguments
 * @param argv Array with console arguments
 */
void CompilingStart(int argc, char *argv[]) {
    GSLanguageCompiler::GS_Arguments arguments(argc, argv);
    arguments.parseArguments();

    // reading input file
    GSLanguageCompiler::GS_Reader reader(arguments.getFilename());
    std::vector<std::string> input = reader.readFile();

    // lexer analyzing
    GSLanguageCompiler::GS_Lexer lexer(input);
    std::vector<GSLanguageCompiler::GS_Token> tokens = lexer.tokenize();

    // testing
    Testing::printTokenTypes(tokens);
}

/**
 * Main function in GSLanguageCompiler
 * @return Status number for operation system
 */
int main(int argc, char *argv[]) {
    try {
        CompilingStart(argc, argv);
    }
    catch (GSLanguageCompiler::Exceptions::_GS_Exception &exception) {
        std::cerr << exception << std::endl;
    }
    catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
    return 0;
}
