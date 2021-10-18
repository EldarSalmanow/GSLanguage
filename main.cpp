#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
#include <Parser/GS_Parser.h>

using namespace GSLanguageCompiler;

Reader::GS_Code read(const String &filename) {
    IFStream stream;
    stream.open(filename);

    Reader::GS_Reader reader(std::move(stream));

    return reader.read();
}

Lexer::GSTokenArray tokenize(Reader::GS_Code code) {
    Lexer::GS_Lexer lexer(std::move(code));

    return lexer.tokenize();
}

AST::GSDeclarationPtrArray parse(Lexer::GSTokenArray tokens) {
    Parser::GS_Parser parser(std::move(tokens));

    return parser.parse();
}

int main() {
    try {
        auto code = read("../../test.gs");

        auto tokens = tokenize(code);

        auto ast = parse(tokens);
    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        return 1;
    }

    return 0;
}

//#include <Starter/GS_Starter.h>

/**
 * Main function in GSLanguageCompiler
 * @param argc Arguments count
 * @param argv Arguments array
 * @return Status number for operation system
 */
//GSInt main(GSInt argc, GSChar *argv[]) {
//    return Starter::GS_Starter::start(argc, argv);
//}
