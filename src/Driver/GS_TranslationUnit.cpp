#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>

#include <GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    String tokenTypeToString(Lexer::TokenType type) {
        String tokenTypesAsString[] = {
#define GS_TOKENTYPE(name) #name
#include <Lexer/GS_Keywords.def>
        };

        return tokenTypesAsString[static_cast<I32>(type)];
    }

    GS_TranslationUnit::GS_TranslationUnit(String name)
            : _name(std::move(name)) {}

    I32 GS_TranslationUnit::compile() {
        IFStream fileStream(_name);

        Reader::GS_Reader reader(&fileStream);

        Reader::GS_TextStream textStream(reader);

        Lexer::GS_Lexer lexer(textStream);

        Lexer::GSTokenArray tokens;

        auto token = lexer.getToken();

        while (token.getType() != Lexer::TokenType::EndOfFile) {
            std::cout << tokenTypeToString(token.getType()) << std::endl;

            tokens.emplace_back(token);

            token = lexer.getToken();
        }

        return 0;
    }

    String GS_TranslationUnit::getName() {
        return _name;
    }

}
