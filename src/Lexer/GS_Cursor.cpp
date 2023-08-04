#include <GS_Cursor.h>

namespace GSLanguageCompiler::Lexer {

    GS_Cursor::GS_Cursor(ConstLRef<IO::GS_Source> source)
            : _source(source),
              _sourceIterator(_source.begin()),
              _savedPosition(1),
              _currentPosition(1) {}

    GS_Cursor GS_Cursor::Create(ConstLRef<IO::GS_Source> source) {
        return GS_Cursor(source);
    }

    ConstLRef<USymbol> GS_Cursor::CurrentSymbol() const {
        return *_sourceIterator;
    }

    Void GS_Cursor::NextSymbol() {
        ++_sourceIterator;

        ++_currentPosition;
    }

    ConstLRef<USymbol> GS_Cursor::LookupSymbol(U64 index) const {
        return _sourceIterator[index];
    }

    IO::GS_SourceLocation GS_Cursor::CurrentLocation() const {
        auto location = IO::GS_SourceLocation::Create(_savedPosition,
                                                      (_currentPosition - _savedPosition) + 1,
                                                      _source.GetHash());

        return location;
    }

    Void GS_Cursor::SavePosition() {
        _savedPosition = _currentPosition;
    }

    Bool GS_Cursor::IsEnd() const {
        return _sourceIterator == _source.end();
    }

    ConstLRef<USymbol> GS_Cursor::operator*() const {
        return CurrentSymbol();
    }

    LRef<GS_Cursor> GS_Cursor::operator++() {
        NextSymbol();

        return *this;
    }

}
