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

    GS_Symbol::GS_Symbol(USymbol value, GS_SymbolLocation location)
            : _value(std::move(value)), _location(std::move(location)) {}

    GS_Symbol GS_Symbol::Create(USymbol value, GS_SymbolLocation location) {
        return GS_Symbol(std::move(value), std::move(location));
    }

    GS_Symbol GS_Symbol::Create(USymbol value) {
        return GS_Symbol::Create(std::move(value), GS_SymbolLocation::Create());
    }

    GS_Symbol GS_Symbol::Create() {
        return GS_Symbol::Create(USymbol(), GS_SymbolLocation::Create());
    }

    USymbol GS_Symbol::GetValue() const {
        return _value;
    }

    GS_SymbolLocation GS_Symbol::GetLocation() const {
        return _location;
    }

}
