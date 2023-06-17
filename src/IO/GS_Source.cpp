#include <fstream>

#include <GS_Reader.h>

#include <GS_Source.h>

namespace GSLanguageCompiler::IO {

    GS_SourceLocation::GS_SourceLocation(U64 position,
                                         U64 sourceHash)
            : _position(position),
              _sourceHash(sourceHash) {}

    GS_SourceLocation GS_SourceLocation::Create(U64 position,
                                                U64 sourceHash) {
        return GS_SourceLocation(position,
                                 sourceHash);
    }

    GS_SourceLocation GS_SourceLocation::Create(U64 position) {
        return GS_SourceLocation::Create(position,
                                         InvalidHash);
    }

    GS_SourceLocation GS_SourceLocation::Create() {
        return GS_SourceLocation::Create(InvalidPosition);
    }

    U64 GS_SourceLocation::GetPosition() const {
        return _position;
    }

    U64 GS_SourceLocation::GetSourceHash() const {
        return _sourceHash;
    }

    Bool GS_SourceLocation::operator==(ConstLRef<GS_SourceLocation> sourceLocation) const {
        return _position == sourceLocation.GetPosition()
            && _sourceHash == sourceLocation.GetSourceHash();
    }

    std::partial_ordering GS_SourceLocation::operator<=>(ConstLRef<GS_SourceLocation> sourceLocation) const {
        auto position = sourceLocation.GetPosition();
        auto sourceHash = sourceLocation.GetSourceHash();

        if ((_position == InvalidPosition && _sourceHash == InvalidHash)
         || (position == InvalidPosition && sourceHash == InvalidHash)) {
            return std::partial_ordering::unordered;
        }

        return _position <=> position;
    }

    // TODO: realize
    std::tuple<U64, U64, U64> ToLineColumnLocation(ConstLRef<GS_SourceLocation> sourceLocation) {
        return std::make_tuple(InvalidPosition,
                               InvalidPosition,
                               InvalidHash);
    }

    GS_SourceLocation ToByteLocation(U64 line,
                                     U64 column,
                                     U64 sourceHash) {
        return GS_SourceLocation::Create();
    }

    GS_SourceBuffer::GS_SourceBuffer(UString source)
            : _source(std::move(source)) {}

    GS_SourceBuffer GS_SourceBuffer::Create(UString source) {
        return GS_SourceBuffer(std::move(source));
    }

    U64 GetIndexByLocation(GS_SourceLocation sourceLocation,
                           ConstLRef<GS_SourceBuffer> sourceBuffer) {
        auto position = sourceLocation.GetPosition();

        if (sourceLocation.GetPosition() == InvalidPosition
         && sourceLocation.GetSourceHash() == InvalidHash) {
            return 0;
        }

        if (position > sourceBuffer.GetSource().Size()) {
            Driver::GlobalContext().Exit("Can`t convert byte source location to index with position in byte source location bigger than source buffer size!");
        }

        auto index = position - 1;

        return index;
    }

    GS_SourceBuffer::Iterator GS_SourceBuffer::GetIteratorByLocation(GS_SourceLocation sourceLocation) {
        return _source.begin() + GetIndexByLocation(sourceLocation,
                                                    *this);
    }

    GS_SourceBuffer::ConstIterator GS_SourceBuffer::GetIteratorByLocation(GS_SourceLocation sourceLocation) const {
        return _source.cbegin() + GetIndexByLocation(sourceLocation,
                                                     *this);
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
        std::ifstream fileStream(name.AsUTF8());

        if (!fileStream.is_open()) {
            Driver::GlobalContext().Exit();
        }

        auto reader = IO::GS_Reader::Create(fileStream);

        auto source = reader.Read();

        return GS_Source::Create(GS_SourceBuffer::Create(source),
                                 GS_SourceName::CreateFile(std::move(name)));
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
