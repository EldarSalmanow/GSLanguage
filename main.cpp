#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
#include <AST/GS_TranslationUnit.h>
#include <Parser/GS_NewParser.h>

using namespace GSLanguageCompiler;

Reader::GS_Code read(const String &filename) {
    IFStream stream;
    stream.open(filename);

    Reader::GS_Reader reader(&stream);

    return reader.read();
}

Lexer::GSTokenArray tokenize(Reader::GS_Code code) {
    Lexer::GS_Lexer lexer(std::move(code));

    return lexer.tokenize();
}

AST::GSDeclarationPtrArray parse(Lexer::GS_TokenStream *stream) {
    Parser::New::GS_Parser parser;

    auto declarations = parser.parseProgram(stream);

    for (auto &error : parser.errors) {
        COut << error.errorMessage() << std::endl;
    }

    return declarations;
}

I32 main() {
    try {
        auto code = read("../test.gs");

        auto tokens = tokenize(code);

        auto tokenIterator = tokens.begin();

        auto tokenStream = Lexer::GS_TokenStream(tokenIterator);

        auto ast = parse(&tokenStream);
    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        return 1;
    }

    return 0;
}
