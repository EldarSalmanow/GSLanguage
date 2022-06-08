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

#include <vector>

#include <IO/IO.h>

using namespace GSLanguageCompiler;

/**
 * Class for containing information about symbol location
 */
class GS_SymbolLocation {
public:

    /**
     * Constructor for symbol location
     * @param sourceName Source name
     * @param line Line
     * @param column Column
     * @return Symbol location
     */
    GS_SymbolLocation(UString sourceName, U64 line, U64 column)
            : _sourceName(std::move(sourceName)), _line(line), _column(column) {}

public:

    /**
     * Creating symbol location
     * @param sourceName Source name
     * @param line Line
     * @param column Column
     * @return Symbol location
     */
    static GS_SymbolLocation Create(UString sourceName, U64 line, U64 column) {
        return GS_SymbolLocation(std::move(sourceName), line, column);
    }

    /**
     * Creating symbol location
     * @param line Line
     * @param column Column
     * @return Symbol location
     */
    static GS_SymbolLocation Create(U64 line, U64 column) {
        return GS_SymbolLocation::Create("<unknown>"_us, line, column);
    }

    /**
     * Creating symbol location
     * @return Symbol location
     */
    static GS_SymbolLocation Create() {
        return GS_SymbolLocation::Create(0, 0);
    }

public:

    /**
     * Getter for source name
     * @return Source name
     */
    UString GetSourceName() const {
        return _sourceName;
    }

    /**
     * Getter for line
     * @return Line
     */
    U64 GetLine() const {
        return _line;
    }

    /**
     * Getter for column
     * @return Column
     */
    U64 GetColumn() const {
        return _column;
    }

private:

    /**
     * Source name
     */
    UString _sourceName;

    /**
     * Line
     */
    U64 _line;

    /**
     * Column
     */
    U64 _column;
};

class GS_Symbol {
public:

    GS_Symbol(USymbol symbol, GS_SymbolLocation symbolLocation)
            : _symbol(std::move(symbol)), _location(std::move(symbolLocation)) {}

public:

    static GS_Symbol Create(USymbol symbol, GS_SymbolLocation symbolLocation) {
        return GS_Symbol(std::move(symbol), std::move(symbolLocation));
    }

    static GS_Symbol Create(USymbol symbol) {
        return GS_Symbol::Create(std::move(symbol), GS_SymbolLocation::Create());
    }

    static GS_Symbol Create() {
        return GS_Symbol::Create(USymbol(), GS_SymbolLocation::Create());
    }

public:

    USymbol GetSymbol() const {
        return _symbol;
    }

    GS_SymbolLocation GetLocation() const {
        return _location;
    }

private:

    USymbol _symbol;

    GS_SymbolLocation _location;
};

std::vector<GS_Symbol> Read(IO::GSInStreamPtr stream) {
    std::vector<GS_Symbol> symbols;

    auto sourceName = stream->GetStreamInfo()->GetFileName();
    U64 line = 1, column = 1;

    while (true) {
        USymbol symbol;

        stream->GetInStream() >> symbol;

        if (stream->GetInStream().eof()) {
            break;
        }

        auto location = GS_SymbolLocation::Create(sourceName, line, column);

        symbols.emplace_back(GS_Symbol::Create(symbol, location));

        if (symbol == '\n') {
            ++line;

            column = 1;
        } else {
            ++column;
        }
    }

    return symbols;
}

int main(int argc, char *argv[]) {
    auto symbols = Read(IO::GS_InFileStream::CreateInFile(argv[1]));

    for (auto &symbol : symbols) {
        auto location = symbol.GetLocation();

        std::cout << symbol.GetSymbol().CodePoint() << " " << location.GetSourceName() << " " << location.GetLine() << " " << location.GetColumn() << std::endl;
    }

    return 0;
}
