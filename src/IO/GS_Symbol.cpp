#include <GS_Symbol.h>

namespace GSLanguageCompiler::IO {

    GS_SymbolLocation::GS_SymbolLocation(UString sourceName, U64 line, U64 column)
            : _sourceName(std::move(sourceName)), _line(line), _column(column) {}

    GS_SymbolLocation GS_SymbolLocation::Create(UString sourceName, U64 line, U64 column) {
        return GS_SymbolLocation(std::move(sourceName), line, column);
    }

    GS_SymbolLocation GS_SymbolLocation::Create(U64 line, U64 column) {
        return GS_SymbolLocation::Create("<unknown>"_us, line, column);
    }

    GS_SymbolLocation GS_SymbolLocation::Create() {
        return GS_SymbolLocation::Create("<unknown>"_us, 0, 0);
    }

    UString GS_SymbolLocation::GetSourceName() const {
        return _sourceName;
    }

    U64 GS_SymbolLocation::GetLine() const {
        return _line;
    }

    U64 GS_SymbolLocation::GetColumn() const {
        return _column;
    }

    GS_Symbol::GS_Symbol(USymbol symbol, GS_SymbolLocation location)
            : _symbol(std::move(symbol)), _location(std::move(location)) {}

    GS_Symbol GS_Symbol::Create(USymbol symbol, GS_SymbolLocation location) {
        return GS_Symbol(std::move(symbol), std::move(location));
    }

    GS_Symbol GS_Symbol::Create(USymbol symbol) {
        return GS_Symbol::Create(std::move(symbol), GS_SymbolLocation::Create());
    }

    GS_Symbol GS_Symbol::Create() {
        return GS_Symbol::Create(USymbol(), GS_SymbolLocation::Create());
    }

    USymbol GS_Symbol::GetSymbol() const {
        return _symbol;
    }

    GS_SymbolLocation GS_Symbol::GetLocation() const {
        return _location;
    }

}
