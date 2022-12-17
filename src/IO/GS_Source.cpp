#include <Driver/GS_GlobalContext.h>

#include <GS_Reader.h>

#include <GS_Source.h>

namespace GSLanguageCompiler::IO {

    GS_SourceLocation::GS_SourceLocation(U64 sourceHash,
                                         U64 startPosition,
                                         U64 endPosition)
            : _sourceHash(sourceHash),
              _startPosition(startPosition),
              _endPosition(endPosition) {}

    GS_SourceLocation GS_SourceLocation::Create(U64 sourceHash,
                                                U64 startPosition,
                                                U64 endPosition) {
        return GS_SourceLocation(sourceHash,
                                 startPosition,
                                 endPosition);
    }

    GS_SourceLocation GS_SourceLocation::Create(U64 sourceHash,
                                                U64 endPosition) {
        return GS_SourceLocation::Create(sourceHash,
                                         1,
                                         endPosition);
    }

    GS_SourceLocation GS_SourceLocation::CreateWithoutHash(U64 startPosition,
                                                           U64 endPosition) {
        return GS_SourceLocation::Create(0,
                                         startPosition,
                                         endPosition);
    }

    GS_SourceLocation GS_SourceLocation::CreateWithoutHash(U64 endPosition) {
        return GS_SourceLocation::CreateWithoutHash(1,
                                                    endPosition);
    }

    GS_SourceLocation GS_SourceLocation::Create() {
        return GS_SourceLocation::Create(0,
                                         0,
                                         0);
    }

    GS_SourceLocation GS_SourceLocation::FromFullSourceLocation(GS_FullSourceLocation fullSourceLocation,
                                                                ConstLRef<GS_Source> source) {
        auto sourceHash = fullSourceLocation.GetSourceHash();
        auto startLine = fullSourceLocation.GetStartLine();
        auto startColumn = fullSourceLocation.GetStartColumn();
        auto endLine = fullSourceLocation.GetEndLine();
        auto endColumn = fullSourceLocation.GetEndColumn();

        // todo add check source hash
        auto stringSource = source.GetBuffer().GetSource();

        U64 startPosition = 0;

        for (U64 index = 0, lineCount = 1;; ++index, ++startPosition) {
            if (stringSource[index] == '\n') {
                ++lineCount;
            }

            if (lineCount == startLine) {
                break;
            }
        }

        // todo add validating line and column position
        startPosition += startColumn;

        U64 endPosition = 0;

        for (U64 index = 0, lineCount = 1;; ++index, ++endPosition) {
            if (stringSource[index] == '\n') {
                ++lineCount;
            }

            if (lineCount == endLine) {
                break;
            }
        }

        endPosition += endColumn;

        return GS_SourceLocation::Create(sourceHash,
                                         startPosition,
                                         endPosition);
    }

    U64 GS_SourceLocation::GetSourceHash() const {
        return _sourceHash;
    }

    U64 GS_SourceLocation::GetStartPosition() const {
        return _startPosition;
    }

    U64 GS_SourceLocation::GetEndPosition() const {
        return _endPosition;
    }

    GS_FullSourceLocation::GS_FullSourceLocation(U64 sourceHash,
                                                 U64 startLine,
                                                 U64 startColumn,
                                                 U64 endLine,
                                                 U64 endColumn)
            : _sourceHash(sourceHash),
              _startLine(startLine),
              _startColumn(startColumn),
              _endLine(endLine),
              _endColumn(endColumn) {}

    GS_FullSourceLocation GS_FullSourceLocation::Create(U64 sourceHash,
                                                        U64 startLine,
                                                        U64 startColumn,
                                                        U64 endLine,
                                                        U64 endColumn) {
        return GS_FullSourceLocation(sourceHash,
                                     startLine,
                                     startColumn,
                                     endLine,
                                     endColumn);
    }

    GS_FullSourceLocation GS_FullSourceLocation::Create(U64 sourceHash,
                                                        U64 endLine,
                                                        U64 endColumn) {
        return GS_FullSourceLocation::Create(sourceHash,
                                             1,
                                             1,
                                             endLine,
                                             endColumn);
    }

    GS_FullSourceLocation GS_FullSourceLocation::CreateWithoutHash(U64 startLine,
                                                                   U64 startColumn,
                                                                   U64 endLine,
                                                                   U64 endColumn) {
        return GS_FullSourceLocation::Create(0,
                                             startLine,
                                             startColumn,
                                             endLine,
                                             endColumn);
    }

    GS_FullSourceLocation GS_FullSourceLocation::CreateWithoutHash(U64 endLine,
                                                                   U64 endColumn) {
        return GS_FullSourceLocation::CreateWithoutHash(1,
                                                        1,
                                                        endLine,
                                                        endColumn);
    }

    GS_FullSourceLocation GS_FullSourceLocation::Create() {
        return GS_FullSourceLocation::Create(0,
                                             0,
                                             0,
                                             0,
                                             0);
    }

    GS_FullSourceLocation GS_FullSourceLocation::FromSourceLocation(GS_SourceLocation sourceLocation,
                                                                    ConstLRef<GS_Source> source) {
        auto sourceHash = sourceLocation.GetSourceHash();
        auto startPosition = sourceLocation.GetStartPosition();
        auto endPosition = sourceLocation.GetEndPosition();

        // todo add check source hash
        auto stringSource = source.GetBuffer().GetSource();

        U64 startLine = 1, startColumn = 0;

        for (U64 index = 0; index < startPosition; ++index) {
            if (stringSource[index] == '\n') {
                ++startLine;

                startColumn = 0;
            } else {
                ++startColumn;
            }
        }

        U64 endLine = 1, endColumn = 0;

        for (U64 index = 0; index < endPosition; ++index) {
            if (stringSource[index] == '\n') {
                ++endLine;

                endColumn = 0;
            } else {
                ++endColumn;
            }
        }

        return GS_FullSourceLocation::Create(sourceHash,
                                             startLine,
                                             startColumn,
                                             endLine,
                                             endColumn);
    }

    U64 GS_FullSourceLocation::GetSourceHash() const {
        return _sourceHash;
    }

    U64 GS_FullSourceLocation::GetStartLine() const {
        return _startLine;
    }

    U64 GS_FullSourceLocation::GetStartColumn() const {
        return _startColumn;
    }

    U64 GS_FullSourceLocation::GetEndLine() const {
        return _endLine;
    }

    U64 GS_FullSourceLocation::GetEndColumn() const {
        return _endColumn;
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

    GS_SourceName::GS_SourceName(UString name,
                                 SourceNameType type)
            : _name(std::move(name)),
              _type(type),
              _hash(0) {
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
              _hash(0) {
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

    UString GS_Source::GetCodeByLocation(GS_SourceLocation location) const {
        UString code;

        for (U64 index = location.GetStartPosition() - 1; index < location.GetEndPosition(); ++index) {
            code += _buffer.GetSource()[index];
        }

        return code;
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

    GS_SourceManager::GS_SourceManager(GSSourcePtrArray sources)
            : _sources(std::move(sources)) {}

    std::shared_ptr<GS_SourceManager> GS_SourceManager::Create(GSSourcePtrArray sources) {
        return std::make_shared<GS_SourceManager>(std::move(sources));
    }

    std::shared_ptr<GS_SourceManager> GS_SourceManager::Create() {
        return GS_SourceManager::Create(GSSourcePtrArray());
    }

    ConstLRef<GS_Source> GS_SourceManager::AddSource(GSSourcePtr source) {
        _sources.emplace_back(std::move(source));

        return *_sources[_sources.size() - 1]; // TODO optimize
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
