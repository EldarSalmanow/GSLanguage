#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
//#include <Parser/GS_Parser.h>

#include <GS_TranslationUnit.h>

namespace GSLanguageCompiler::Driver {

    UString tokenTypeToString(Lexer::TokenType type) {
        UString tokenTypesAsString[] = {
#define GS_TOKENTYPE(name) U#name
#include <Lexer/GS_Keywords.def>
        };

        return tokenTypesAsString[StaticCast<I32>(type)];
    }

    GS_TranslationUnit::GS_TranslationUnitDeclaration(UString name)
            : _name(std::move(name)) {}

    I32 GS_TranslationUnit::compile() {
        UFileStream fileStream;

        fileStream.Open(_name, in_mode);

        Reader::GS_Reader reader(&fileStream);

        Reader::GS_TextStream textStream(&reader);

        Lexer::GS_Lexer lexer(&textStream);

//        Lexer::GS_TokenStream tokenStream(&lexer);
//
//        Parser::GS_Parser parser(&tokenStream);
//
//        auto declarations = parser.parse();

        return 0;
    }

    UString GS_TranslationUnit::getName() const {
        return _name;
    }

}
