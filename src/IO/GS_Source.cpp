#include <GS_Reader.h>

#include <GS_Source.h>

namespace GSLanguageCompiler::IO {

    GS_SourceLocation::GS_SourceLocation(U64 sourceHash, U64 startPosition, U64 endPosition)
            : _sourceHash(sourceHash), _startPosition(startPosition), _endPosition(endPosition) {}

    GS_SourceLocation GS_SourceLocation::Create(U64 sourceHash, U64 startPosition, U64 endPosition) {
        return GS_SourceLocation(sourceHash, startPosition, endPosition);
    }

    GS_SourceLocation GS_SourceLocation::Create(U64 sourceHash, U64 endPosition) {
        return GS_SourceLocation::Create(sourceHash, 1, endPosition);
    }

    GS_SourceLocation GS_SourceLocation::CreateWithoutHash(U64 startPosition, U64 endPosition) {
        return GS_SourceLocation::Create(0, startPosition, endPosition);
    }

    GS_SourceLocation GS_SourceLocation::CreateWithoutHash(U64 endPosition) {
        return GS_SourceLocation::CreateWithoutHash(1, endPosition);
    }

    GS_SourceLocation GS_SourceLocation::Create() {
        return GS_SourceLocation::Create(0, 0, 0);
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

    GS_SourceName::GS_SourceName(UString name, SourceNameType type)
            : _name(std::move(name)), _type(type), _hash(0) {
        std::hash<std::string> nameHasher;

        _hash = nameHasher(_name.AsUTF8());

        std::hash<U8> typeHasher;

        _hash ^= typeHasher(StaticCast<U8>(type));
    }

    GS_SourceName GS_SourceName::Create(UString name, SourceNameType type) {
        return GS_SourceName(std::move(name), type);
    }

    GS_SourceName GS_SourceName::CreateFile(UString name) {
        return GS_SourceName::Create(std::move(name), SourceNameType::File);
    }

    GS_SourceName GS_SourceName::CreateString() {
        static U64 id = 1;

        auto name = UString(std::string("<string_") + std::to_string(id) + std::string(">"));

        ++id;

        return GS_SourceName::Create(name, SourceNameType::String);
    }

    GS_SourceName GS_SourceName::CreateCustom(UString name) {
        return GS_SourceName::Create(std::move(name), SourceNameType::Custom);
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

    UString GS_SourceName::GetName() const {
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

    GS_Source::GS_Source(UString source, GS_SourceName name)
            : _source(std::move(source)), _name(std::move(name)), _hash(0) {
        std::hash<std::string> sourceHasher;

        _hash = sourceHasher(_source.AsUTF8());

        _hash ^= _name.GetHash();
    }

    std::shared_ptr<GS_Source> GS_Source::Create(UString source, GS_SourceName name) {
        return std::make_shared<GS_Source>(std::move(source), std::move(name));
    }

    std::shared_ptr<GS_Source> GS_Source::CreateFile(UString name) {
        auto fileStream = IO::GS_InFileStream::CreateInFile(name);

        auto reader = IO::GS_Reader::Create(fileStream);

        return GS_Source::Create(reader.Read(), GS_SourceName::CreateFile(name));
    }

    std::shared_ptr<GS_Source> GS_Source::CreateString(UString source) {
        return GS_Source::Create(std::move(source), GS_SourceName::CreateString());
    }

    std::shared_ptr<GS_Source> GS_Source::CreateCustom(UString source, UString name) {
        return GS_Source::Create(std::move(source), GS_SourceName::CreateCustom(std::move(name)));
    }

    UString GS_Source::GetCodeByLocation(GS_SourceLocation location) {
        UString code;

        for (U64 index = location.GetStartPosition() - 1; index < location.GetEndPosition(); ++index) {
            code += _source[index];
        }

        return code;
    }

    UString GS_Source::GetSource() const {
        return _source;
    }

    GS_SourceName GS_Source::GetName() const {
        return _name;
    }

    U64 GS_Source::GetHash() const {
        return _hash;
    }

    Bool GS_Source::operator==(ConstLRef<GSLanguageCompiler::IO::GS_Source> source) const {
        return _hash == source.GetHash();
    }

    Bool GS_Source::operator!=(ConstLRef<GSLanguageCompiler::IO::GS_Source> source) const {
        return !(*this == source);
    }

}
