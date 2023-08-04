#include <fstream>

#include <Driver/GS_GlobalContext.h>

#include <GS_Reader.h>

#include <GS_Source.h>

namespace GSLanguageCompiler::IO {

    GS_SourceLocation::GS_SourceLocation(U64 position,
                                         U64 length,
                                         U64 sourceHash)
            : _position(position),
              _length(length),
              _sourceHash(sourceHash) {}

    GS_SourceLocation GS_SourceLocation::Create(U64 position, U64 length, U64 sourceHash) {
        return GS_SourceLocation(position,
                                 length,
                                 sourceHash);
    }

    GS_SourceLocation GS_SourceLocation::Create(U64 position,
                                                U64 sourceHash) {
        return GS_SourceLocation::Create(position,
                                         1,
                                         sourceHash);
    }

    GS_SourceLocation GS_SourceLocation::Create() {
        return GS_SourceLocation::Create(InvalidPosition,
                                         InvalidHash);
    }

    U64 GS_SourceLocation::GetStartPosition() const {
        return _position;
    }

    U64 GS_SourceLocation::GetEndPosition() const {
        return _position + _length;
    }

    U64 GS_SourceLocation::GetPosition() const {
        return _position;
    }

    U64 GS_SourceLocation::GetLength() const {
        return _length;
    }

    U64 GS_SourceLocation::GetSourceHash() const {
        return _sourceHash;
    }

    Bool GS_SourceLocation::operator==(ConstLRef<GS_SourceLocation> location) const {
        return _position == location.GetPosition()
            && _length == location.GetLength()
            && _sourceHash == location.GetSourceHash();
    }

    GS_SourceBuffer::GS_SourceBuffer(UString source)
            : _source(std::move(source)) {}

    GS_SourceBuffer GS_SourceBuffer::Create(UString source) {
        return GS_SourceBuffer(std::move(source));
    }

    GS_SourceBuffer::Iterator GS_SourceBuffer::begin() {
        return _source.begin();
    }

    GS_SourceBuffer::Iterator GS_SourceBuffer::end() {
        return _source.end();
    }

    GS_SourceBuffer::ConstIterator GS_SourceBuffer::begin() const {
        return _source.begin();
    }

    GS_SourceBuffer::ConstIterator GS_SourceBuffer::end() const {
        return _source.end();
    }

    GS_SourceBuffer::ConstIterator GS_SourceBuffer::cbegin() const {
        return _source.cbegin();
    }

    GS_SourceBuffer::ConstIterator GS_SourceBuffer::cend() const {
        return _source.cend();
    }

    ConstLRef<UString> GS_SourceBuffer::GetSource() const {
        return _source;
    }

    Bool GS_SourceBuffer::operator==(ConstLRef<GS_SourceBuffer> sourceBuffer) const {
        return _source == sourceBuffer.GetSource();
    }

    LRef<USymbol> GS_SourceBuffer::operator[](ConstLRef<U64> index) {
        return _source[index];
    }

    ConstLRef<USymbol> GS_SourceBuffer::operator[](ConstLRef<U64> index) const {
        return _source[index];
    }

    GS_SourceName::GS_SourceName(UString name,
                                 SourceNameType type)
            : _name(std::move(name)),
              _type(type),
              _hash(InvalidHash) {
        std::hash<std::string> nameHasher;

        _hash = nameHasher(_name.AsUTF8());

        std::hash<U8> typeHasher;

        _hash ^= typeHasher(StaticCast<U8>(type));
    }

    GS_SourceName GS_SourceName::Create(UString name,
                                        SourceNameType type) {
        return GS_SourceName(std::move(name),
                             type);
    }

    GS_SourceName GS_SourceName::CreateFile(UString name) {
        return GS_SourceName::Create(std::move(name),
                                     SourceNameType::File);
    }

    GS_SourceName GS_SourceName::CreateString() {
        static U64 id = 1;

        UStringStream stringStream;

        stringStream << "<string_"_us
                     << id
                     << ">"_us;

        ++id;

        return GS_SourceName::Create(stringStream.String(),
                                     SourceNameType::String);
    }

    GS_SourceName GS_SourceName::CreateCustom(UString name) {
        return GS_SourceName::Create(std::move(name),
                                     SourceNameType::Custom);
    }

    Bool GS_SourceName::IsFile() const {
        return _type == SourceNameType::File;
    }

    Bool GS_SourceName::IsString() const {
        return _type == SourceNameType::String;
    }

    Bool GS_SourceName::IsCustom() const {
        return _type == SourceNameType::Custom;
    }

    ConstLRef<UString> GS_SourceName::GetName() const {
        return _name;
    }

    SourceNameType GS_SourceName::GetType() const {
        return _type;
    }

    U64 GS_SourceName::GetHash() const {
        return _hash;
    }

    Bool GS_SourceName::operator==(ConstLRef<GS_SourceName> name) const {
        return _hash == name.GetHash();
    }

    GS_Source::GS_Source(GS_SourceBuffer buffer,
                         GS_SourceName name)
            : _buffer(std::move(buffer)),
              _name(std::move(name)),
              _hash(InvalidHash) {
        std::hash<std::string> sourceHasher;

        _hash = sourceHasher(_buffer.GetSource().AsUTF8());

        _hash ^= _name.GetHash();
    }

    std::unique_ptr<GS_Source> GS_Source::Create(GS_SourceBuffer buffer,
                                                 GS_SourceName name) {
        return std::make_unique<GS_Source>(std::move(buffer),
                                           std::move(name));
    }

    std::unique_ptr<GS_Source> GS_Source::CreateFile(UString name) {
        auto movedName = std::move(name);

        std::ifstream fileStream(movedName.AsUTF8());

        if (!fileStream.is_open()) {
            UStringStream stringStream;

            stringStream << "Can`t open file with name '"_us
                         << movedName
                         << "'!"_us;

            Driver::GlobalContext().Exit(stringStream.String());
        }

        auto reader = IO::GS_Reader::Create(fileStream);

        auto source = reader.Read();

        return GS_Source::Create(GS_SourceBuffer::Create(source),
                                 GS_SourceName::CreateFile(std::move(movedName)));
    }

    std::unique_ptr<GS_Source> GS_Source::CreateString(UString source) {
        return GS_Source::Create(GS_SourceBuffer::Create(std::move(source)),
                                 GS_SourceName::CreateString());
    }

    std::unique_ptr<GS_Source> GS_Source::CreateCustom(UString source,
                                                       UString name) {
        return GS_Source::Create(GS_SourceBuffer::Create(std::move(source)),
                                 GS_SourceName::CreateCustom(std::move(name)));
    }

    std::tuple<U64, U64> GS_Source::GetLineColumnPosition(U64 position) const {
        if (position == InvalidPosition) {
            return std::make_tuple(InvalidPosition,
                                   InvalidPosition);
        }

        if (position > _buffer.GetSource().Size()) {
            Driver::GlobalContext().Exit("Can`t convert byte position to line column position with position bigger than source size!");
        }

        U64 line = 1, column = 1;

        for (U64 index = 0; index < position; ++index) {
            if (_buffer[index] == '\n') {
                ++line;

                column = 1;

                continue;
            }

            ++column;
        }

        return std::make_tuple(line,
                               column);
    }

    U64 GS_Source::GetBytePosition(U64 line,
                                   U64 column) const {
        if (line == InvalidPosition
         || column == InvalidPosition) {
            return InvalidPosition;
        }

        U64 position = 1;

        for (U64 lineIndex = 1; lineIndex < line; ++position) {
            if (position > _buffer.GetSource().Size()) {
                Driver::GlobalContext().Exit("Can`t convert line column position to byte position with line bigger than source size!");
            }

            if (_buffer[position - 1] == '\n') {
                ++lineIndex;
            }
        }

        for (U64 columnIndex = 1; columnIndex < column; ++position) {
            if (position > _buffer.GetSource().Size()) {
                Driver::GlobalContext().Exit("Can`t convert line column position to byte position with column bigger than source size!");
            }

            if (_buffer[position - 1] == '\n') {
                Driver::GlobalContext().Exit("Can`t convert line column position to byte position with column bigger than column in line!");
            }
        }

        return position;
    }

    U64 GetIndexByLocation(U64 position,
                           ConstLRef<GS_SourceBuffer> sourceBuffer) {
        if (position == InvalidPosition) {
            return 0;
        }

        if (position > sourceBuffer.GetSource().Size()) {
            Driver::GlobalContext().Exit("Can`t convert byte source location to index with position in byte source location bigger than source buffer size!");
        }

        auto index = position - 1;

        return index;
    }

    GS_Source::Iterator GS_Source::GetIteratorByPosition(U64 position) {
        return _buffer.begin() + GetIndexByLocation(position,
                                                    _buffer);
    }

    GS_Source::ConstIterator GS_Source::GetIteratorByPosition(U64 position) const {
        return _buffer.cbegin() + GetIndexByLocation(position,
                                                     _buffer);
    }

    GS_Source::Iterator GS_Source::GetIteratorByPosition(U64 line,
                                                         U64 column) {
        auto position = GetBytePosition(line, column);

        return GetIteratorByPosition(position);
    }

    GS_Source::ConstIterator GS_Source::GetIteratorByPosition(U64 line,
                                                              U64 column) const {
        auto position = GetBytePosition(line, column);

        return GetIteratorByPosition(position);
    }

    UString GS_Source::GetCodeInRange(GS_SourceLocation location) const {
        auto sourceHash = location.GetSourceHash();

        if (sourceHash != InvalidHash
         && sourceHash != _hash) {
            Driver::GlobalContext().Exit();
        }

        auto startPosition = location.GetStartPosition();
        auto endPosition = location.GetEndPosition();

        auto beginIterator = GetIteratorByPosition(startPosition);
        auto endIterator = GetIteratorByPosition(endPosition);

        return GetCodeInRange(beginIterator,
                              endIterator);
    }

    UString GS_Source::GetCodeInRange(GS_Source::ConstIterator beginIterator,
                                      GS_Source::ConstIterator endIterator) const {
        UString string;

        for (auto currentIterator = beginIterator;
             currentIterator != endIterator && currentIterator != _buffer.cend();
             ++currentIterator) {
            string += *currentIterator;
        }

        return string;
    }

    UString GS_Source::GetCodeWhile(GS_Source::ConstIterator beginIterator,
                                    Bool (*predicate)(ConstLRef<USymbol>)) const {
        UString string;

        for (auto currentIterator = beginIterator;
             predicate(*currentIterator) && currentIterator != _buffer.cend();
             ++currentIterator) {
            string += *currentIterator;
        }

        return string;
    }

    GS_Source::ConstIterator GS_Source::begin() const {
        return _buffer.begin();
    }

    GS_Source::ConstIterator GS_Source::end() const {
        return _buffer.end();
    }

    GS_Source::ConstIterator GS_Source::cbegin() const {
        return _buffer.cbegin();
    }

    GS_Source::ConstIterator GS_Source::cend() const {
        return _buffer.cend();
    }

    ConstLRef<GS_SourceBuffer> GS_Source::GetBuffer() const {
        return _buffer;
    }

    ConstLRef<GS_SourceName> GS_Source::GetName() const {
        return _name;
    }

    U64 GS_Source::GetHash() const {
        return _hash;
    }

    Bool GS_Source::operator==(ConstLRef<GS_Source> source) const {
        return _hash == source.GetHash();
    }

    LRef<USymbol> GS_Source::operator[](ConstLRef<U64> index) {
        return _buffer[index];
    }

    ConstLRef<USymbol> GS_Source::operator[](ConstLRef<U64> index) const {
        return _buffer[index];
    }

    GS_SourceManager::GS_SourceManager(GSSourcePtrArray sources)
            : _sources(std::move(sources)) {}

    std::unique_ptr<GS_SourceManager> GS_SourceManager::Create(GSSourcePtrArray sources) {
        return std::make_unique<GS_SourceManager>(std::move(sources));
    }

    std::unique_ptr<GS_SourceManager> GS_SourceManager::Create() {
        return GS_SourceManager::Create(GSSourcePtrArray());
    }

    ConstLRef<GS_Source> GS_SourceManager::AddSource(GSSourcePtr source) {
        _sources.emplace_back(std::move(source));

        return *_sources[_sources.size() - 1];
    }

    ConstLRef<GS_Source> GS_SourceManager::AddFileSource(UString name) {
        auto fileSource = GS_Source::CreateFile(std::move(name));

        auto &fileSourceRef = AddSource(std::move(fileSource));

        return fileSourceRef;
    }

    ConstLRef<GS_Source> GS_SourceManager::AddStringSource(UString source) {
        auto stringSource = GS_Source::CreateString(std::move(source));

        auto &stringSourceRef = AddSource(std::move(stringSource));

        return stringSourceRef;
    }

    ConstLRef<GS_Source> GS_SourceManager::AddCustomSource(UString source,
                                                           UString name) {
        auto customSource = GS_Source::CreateCustom(std::move(source),
                                                    std::move(name));

        auto &customSourceRef = AddSource(std::move(customSource));

        return customSourceRef;
    }

    std::optional<GS_Source> GS_SourceManager::GetSource(U64 sourceHash) const {
        for (auto &source : _sources) {
            if (source->GetHash() == sourceHash) {
                return std::make_optional(*source);
            }
        }

        return std::nullopt;
    }

    std::optional<GS_Source> GS_SourceManager::GetSource(GS_SourceName sourceName) const {
        auto movedSourceName = std::move(sourceName);

        for (auto &source : _sources) {
            if (source->GetName() == movedSourceName) {
                return std::make_optional(*source);
            }
        }

        return std::nullopt;
    }

    std::optional<GS_Source> GS_SourceManager::GetFileSource(UString fileName) const {
        return GetSource(GS_SourceName::CreateFile(std::move(fileName)));
    }

    std::optional<GS_Source> GS_SourceManager::GetCustomSource(UString sourceName) const {
        return GetSource(GS_SourceName::CreateCustom(std::move(sourceName)));
    }

    ConstLRef<GSSourcePtrArray> GS_SourceManager::GetSources() const {
        return _sources;
    }

}
