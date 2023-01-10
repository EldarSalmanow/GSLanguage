#include <Driver/GS_GlobalContext.h>

#include <GS_Reader.h>

#include <GS_Source.h>

namespace GSLanguageCompiler::IO {

    GS_ByteSourceLocation::GS_ByteSourceLocation(U64 sourceHash,
                                                 U64 position)
            : _sourceHash(sourceHash),
              _position(position) {}

    GS_ByteSourceLocation GS_ByteSourceLocation::Create(U64 sourceHash,
                                                        U64 position) {
        return GS_ByteSourceLocation(sourceHash,
                                     position);
    }

    GS_ByteSourceLocation GS_ByteSourceLocation::Create(U64 position) {
        return GS_ByteSourceLocation::Create(InvalidHash,
                                             position);
    }

    GS_ByteSourceLocation GS_ByteSourceLocation::Create() {
        return GS_ByteSourceLocation::Create(InvalidPosition);
    }

    U64 GS_ByteSourceLocation::GetSourceHash() const {
        return _sourceHash;
    }

    U64 GS_ByteSourceLocation::GetPosition() const {
        return _position;
    }

    Bool GS_ByteSourceLocation::operator==(ConstLRef<GS_ByteSourceLocation> sourceLocation) const {
        return _sourceHash == sourceLocation.GetSourceHash()
            && _position == sourceLocation.GetPosition();
    }

    Bool GS_ByteSourceLocation::operator!=(ConstLRef<GS_ByteSourceLocation> sourceLocation) const {
        return !(*this == sourceLocation);
    }

    GS_LineColumnSourceLocation::GS_LineColumnSourceLocation(U64 sourceHash,
                                                             U64 line,
                                                             U64 column)
            : _sourceHash(sourceHash),
              _line(line),
              _column(column) {}

    GS_LineColumnSourceLocation GS_LineColumnSourceLocation::Create(U64 sourceHash,
                                                                    U64 line,
                                                                    U64 column) {
        return GS_LineColumnSourceLocation(sourceHash,
                                           line,
                                           column);
    }

    GS_LineColumnSourceLocation GS_LineColumnSourceLocation::Create(U64 line,
                                                                    U64 column) {
        return GS_LineColumnSourceLocation::Create(InvalidHash,
                                                   line,
                                                   column);
    }

    GS_LineColumnSourceLocation GS_LineColumnSourceLocation::Create() {
        return GS_LineColumnSourceLocation::Create(InvalidPosition,
                                                   InvalidPosition);
    }

    U64 GS_LineColumnSourceLocation::GetSourceHash() const {
        return _sourceHash;
    }

    U64 GS_LineColumnSourceLocation::GetLine() const {
        return _line;
    }

    U64 GS_LineColumnSourceLocation::GetColumn() const {
        return _column;
    }

    Bool GS_LineColumnSourceLocation::operator==(ConstLRef<GS_LineColumnSourceLocation> sourceLocation) const {
        return _sourceHash == sourceLocation.GetSourceHash()
            && _line == sourceLocation.GetLine()
            && _column == sourceLocation.GetColumn();
    }

    Bool GS_LineColumnSourceLocation::operator!=(ConstLRef<GS_LineColumnSourceLocation> sourceLocation) const {
        return !(*this == sourceLocation);
    }

    GS_ByteSourceLocation ToByteLocation(ConstLRef<GS_LineColumnSourceLocation> lineColumnSourceLocation,
                                         ConstLRef<GS_Source> source) {
        auto sourceHash = lineColumnSourceLocation.GetSourceHash();
        auto line = lineColumnSourceLocation.GetLine();
        auto column = lineColumnSourceLocation.GetColumn();

        U64 position = 1;

        for (U64 lineIndex = 1; lineIndex != line; ++position) {
            if (source[position - 1] == '\n') {
                ++lineIndex;

//                ++position; ?
            }
        }

        position += column - 1; // ?

        return GS_ByteSourceLocation::Create(sourceHash,
                                             position);
    }

    GS_LineColumnSourceLocation ToLineColumnLocation(ConstLRef<GS_ByteSourceLocation> byteSourceLocation,
                                                     ConstLRef<GS_Source> source) {

    }

    template<typename SourceLocationT>
    GS_SourceRange<SourceLocationT>::GS_SourceRange(SourceLocation startLocation,
                                                    SourceLocation endLocation)
            : _startLocation(std::move(startLocation)),
              _endLocation(std::move(endLocation)) {}

    template<typename SourceLocationT>
    GS_SourceRange<SourceLocationT> GS_SourceRange<SourceLocationT>::Create(SourceLocation startLocation,
                                                                            SourceLocation endLocation) {
        return GS_SourceRange<SourceLocation>(std::move(startLocation),
                                              std::move(endLocation));
    }

    template<typename SourceLocationT>
    GS_SourceRange<SourceLocationT> GS_SourceRange<SourceLocationT>::CreateFromStart(SourceLocation startLocation) {
        return GS_SourceRange<SourceLocation>::Create(std::move(startLocation),
                                                      SourceLocation::Create());
    }

    template<typename SourceLocationT>
    GS_SourceRange<SourceLocationT> GS_SourceRange<SourceLocationT>::CreateToEnd(SourceLocation endLocation) {
        return GS_SourceRange<SourceLocation>::Create(SourceLocation::Create(),
                                                      std::move(endLocation));
    }

    template<typename SourceLocationT>
    GS_SourceRange<SourceLocationT> GS_SourceRange<SourceLocationT>::Create() {
        return GS_SourceRange<SourceLocation>::Create(SourceLocation::Create(),
                                                      SourceLocation::Create());
    }

    template<typename SourceLocationT>
    typename GS_SourceRange<SourceLocationT>::SourceLocation GS_SourceRange<SourceLocationT>::GetStartLocation() const {
        return _startLocation;
    }

    template<typename SourceLocationT>
    typename GS_SourceRange<SourceLocationT>::SourceLocation GS_SourceRange<SourceLocationT>::GetEndLocation() const {
        return _endLocation;
    }

    template<typename SourceLocationT>
    Bool GS_SourceRange<SourceLocationT>::operator==(ConstLRef<GS_SourceRange<SourceLocationT>> locationRange) const {
        return _startLocation == locationRange.GetStartLocation()
            && _endLocation == locationRange.GetEndLocation();
    }

    template<typename SourceLocationT>
    Bool GS_SourceRange<SourceLocationT>::operator!=(ConstLRef<GS_SourceRange<SourceLocationT>> locationRange) const {
        return !(*this == locationRange);
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

    Bool GS_SourceBuffer::operator!=(ConstLRef<GS_SourceBuffer> sourceBuffer) const {
        return !(*this == sourceBuffer);
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

        stringStream << "<string_"_us << id << ">"_us;

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

    Bool GS_SourceName::operator!=(ConstLRef<GS_SourceName> name) const {
        return !(*this == name);
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
            UStringStream stringStream;

            stringStream << "Can`t open file with name '"_us
                         << name
                         << "'!"_us;

            Driver::GlobalContext().ErrAndExit(stringStream.String());
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

    Bool GS_Source::operator!=(ConstLRef<GS_Source> source) const {
        return !(*this == source);
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
