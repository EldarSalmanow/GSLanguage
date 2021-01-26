#include "include/Compiler/Util/GS_Arguments.h"
#include "include/Compiler/Reader/GS_Reader.h"
#include "include/Compiler/Lexer/GS_Lexer.h"
#include "include/Compiler/Parser/GS_Parser.h"

#include "test/Tests.h"

using namespace GSLanguageCompiler;

/**
 * Start compiler function
 * @param argc Number of console arguments
 * @param argv Array with console arguments
 */
void CompilingStart(int argc, char *argv[]) {
    std::shared_ptr<GS_Arguments> arguments(new GS_Arguments(argc, argv));
    arguments->parseArguments();

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
    try {
        CompilingStart(argc, argv);
    }
    catch (Exceptions::_GS_Exception &exception) {
        std::cerr << exception << std::endl;
    }
    catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
    return 0;
}
