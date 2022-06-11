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

    auto streamToken = tokenStream.CurrentToken();

    Lexer::GSTokenArray tokens;

    while (streamToken.GetType() != Lexer::TokenType::EndOfFile) {
        tokens.emplace_back(streamToken);

        tokenStream.NextToken();

        streamToken = tokenStream.CurrentToken();
    }

    for (U64 i = 0; i < tokens.size(); ++i) {
        auto token = tokens[i];

        auto type = token.GetType();
        auto value = token.GetValue();
        auto location = token.GetLocation();

        std::cout << "№" << i + 1 << std::endl <<
                  "\tType: " << TTypeToString(type) << std::endl <<
                  "\tValue: " << value << std::endl <<
                  "\tLocation: " << location.GetStartLocation().GetSourceName() << " " << location.GetStartLocation().GetLine() << " " << location.GetStartLocation().GetColumn() << " " <<
                  location.GetEndLocation().GetSourceName() << " " << location.GetEndLocation().GetLine() << " " << location.GetEndLocation().GetColumn() << std::endl;
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

enum class TType {
    Identifier,
    Number,

    Plus,
    Minus,
    Star,
    Slash,

    Space
};

class TokenLocation {
public:

    Location SLoc;

    Location ELoc;
};

class Token {
public:

    TType Type;

    UString Value;

    TokenLocation Location;
};

class Lexer_ {
public:

    std::vector<Token> Tokenize() {
        std::vector<Token> tokens;

        return tokens;
    }

public:

    TextStream Stream;
};

class TokenStream {
public:

    Token CurrToken() {
        return *TokensIter;
    }

    Void NextToken() {
        ++TokensIter;
    }

    Void PrevToken() {
        --TokensIter;
    }

public:

    std::vector<Token> Tokens;

    std::vector<Token>::iterator TokensIter;
};

class NodeLocation {
public:

    TokenLocation SLoc;

    TokenLocation ELoc;
};

class Node {
public:

    Node(NodeLocation location)
            : Location(location) {}

public:

    NodeLocation GetLocation() {
        return Location;
    }

public:

    NodeLocation Location;
};

class NumNode : public Node {
public:

    NumNode(I32 num, NodeLocation location)
            : Num(num), Node(location) {}

public:

    I32 Num;
};

Location CreateLocation(UString sourceName, U64 line, U64 column) {
    return { sourceName, line, column };
}

TokenLocation CreateTokenLocation(Location sloc, Location eloc) {
    return { sloc, eloc };
}

TokenLocation CreateTokenLocation(Location location) {
    return CreateTokenLocation(location, location);
}

NodeLocation CreateNodeLocation(TokenLocation sloc, TokenLocation eloc) {
    return { sloc, eloc };
}

NodeLocation CreateNodeLocation(TokenLocation location) {
    return CreateNodeLocation(location);
}

void f() {
    std::ifstream file("main.gs");

    InStream stream = {file};

    Reader reader = {stream};

    TextStream textStream = {reader.Read()};

    Lexer_ lexer = {textStream};

    TokenStream tokenStream = {lexer.Tokenize()};

    Node *node = new NumNode(12, CreateNodeLocation(CreateTokenLocation(CreateLocation("main.gs", 1, 1), CreateLocation("main.gs", 1, 2))));
}