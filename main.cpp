//#include <Driver/Driver.h>
//
//using namespace GSLanguageCompiler;
//
///**
// * Entry point for GSLanguageCompiler
// * @return Compiler result
// */
//I32 main(I32 argc, Ptr<Ptr<C>> argv) {
//    return Driver::GS_Compiler::Start(argc, argv);
//}

//#include <vector>

#include <Lexer/Lexer.h>

using namespace GSLanguageCompiler;

UString TTypeToString(Lexer::TokenType type) {
    UString types[] = {
#define GS_TOKENTYPE(type) #type
#include <Lexer/GS_Keywords.def>
    };

    return types[StaticCast<I32>(type)];
}

int main(int argc, char *argv[]) {
    auto textStream = IO::GS_Reader::Create(IO::GS_InFileStream::CreateInFile(argv[1])).CreateStream();
    auto tokenStream = Lexer::GS_Lexer::Create(textStream).CreateStream();

    auto token = tokenStream.CurrentToken();

    int i = 1;

    while (token.GetType() != Lexer::TokenType::EndOfFile) {
        auto type = token.GetType();
        auto value = token.GetValue();
        auto location = token.GetLocation();

        std::cout << "№" << i << std::endl <<
        "\tType: " << TTypeToString(type) << std::endl <<
        "\tValue: " << value << std::endl <<
        "\tLocation: " << location.GetStartLocation().GetSourceName() << " " << location.GetStartLocation().GetLine() << " " << location.GetStartLocation().GetColumn() <<
        location.GetEndLocation().GetSourceName() << " " << location.GetEndLocation().GetLine() << " " << location.GetEndLocation().GetColumn();

        tokenStream.NextToken();

        token = tokenStream.CurrentToken();

        ++i;
    }

    return 0;
}

class InStream {
public:

    std::istream &Stream;
};

class Location {
public:

    UString SourceName;

    U64 Line;

    U64 Column;
};

class Symbol {
public:

    USymbol UniSymbol;

    Location SymLocation;
};

class Reader {
public:

    std::vector<Symbol> Read() {
        std::vector<Symbol> symbols;

        return symbols;
    }

public:

    InStream Stream;
};

class TextStream {
public:

    Symbol CurrSym() {
        return *SymbolsIter;
    }

    Void NextSym() {
        ++SymbolsIter;
    }

    Void PrevSym() {
        --SymbolsIter;
    }

public:

    std::vector<Symbol> Symbols;

    std::vector<Symbol>::iterator SymbolsIter;
};

void f() {

}
