#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>

using namespace GSLanguageCompiler;

String tokenTypeToString(Lexer::TokenType type) {
    String tokenTypesAsString[] = {
#define GS_TOKENTYPE(name) #name
#include <Lexer/GS_Keywords.def>
    };

    return tokenTypesAsString[static_cast<I32>(type)];
}

I32 main() {
    try {
        IFStream code("../test.gs");

        Reader::GS_Reader reader(&code);

        Reader::GS_TextStream textStream(reader);

        Lexer::GS_Lexer lexer(textStream);

        Lexer::GSTokenArray tokens;

        auto token = lexer.getToken();

        while (token.getType() != Lexer::TokenType::EndOfFile) {
            tokens.emplace_back(token);

            std::cout << tokenTypeToString(token.getType()) << std::endl;

            token = lexer.getToken();
        }
    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        return 1;
    }

    return 0;
}
