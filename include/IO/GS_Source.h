#ifndef GSLANGUAGE_GS_SOURCE_H
#define GSLANGUAGE_GS_SOURCE_H

#include <vector>

#include <IO/GS_Reader.h>

namespace GSLanguageCompiler::IO {

    enum class SourceNameType {
        File,
        String,
        Custom
    };

    class GS_SourceLocation {
    public:

        GS_SourceLocation(U64 sourceHash, U64 startPosition, U64 endPosition)
                : _sourceHash(sourceHash), _startPosition(startPosition), _endPosition(endPosition) {}

    public:

        static GS_SourceLocation Create(U64 sourceHash, U64 startPosition, U64 endPosition) {
            return GS_SourceLocation(sourceHash, startPosition, endPosition);
        }

        static GS_SourceLocation Create(U64 sourceHash, U64 endPosition) {
            return GS_SourceLocation::Create(sourceHash, 1, endPosition);
        }

        static GS_SourceLocation CreateWithoutHash(U64 startPosition, U64 endPosition) {
            return GS_SourceLocation::Create(0, startPosition, endPosition);
        }

        static GS_SourceLocation CreateWithoutHash(U64 endPosition) {
            return GS_SourceLocation::CreateWithoutHash(1, endPosition);
        }

        static GS_SourceLocation Create() {
            return GS_SourceLocation::Create(0, 0, 0);
        }

    public:

        U64 GetSourceHash() const {
            return _sourceHash;
        }

        U64 GetStartPosition() const {
            return _startPosition;
        }

        U64 GetEndPosition() const {
            return _endPosition;
        }

    private:

        U64 _sourceHash;

        U64 _startPosition;

        U64 _endPosition;
    };

    class GS_SourceName {
    public:

        GS_SourceName(UString name, SourceNameType type)
                : _name(std::move(name)), _type(type), _hash(0) {
            std::hash<std::string> nameHasher;

            _hash = nameHasher(_name.AsUTF8());

            std::hash<U8> typeHasher;

            _hash ^= typeHasher(StaticCast<U8>(type));
        }

    public:

        static GS_SourceName Create(UString name, SourceNameType type) {
            return GS_SourceName(std::move(name), type);
        }

        static GS_SourceName CreateFile(UString name) {
            return GS_SourceName::Create(std::move(name), SourceNameType::File);
        }

        static GS_SourceName CreateString() {
            static U64 id = 1;

            auto name = UString(std::string("<string>_") + std::to_string(id));

            ++id;

            return GS_SourceName::Create(name, SourceNameType::String);
        }

        static GS_SourceName CreateCustom(UString name) {
            return GS_SourceName::Create(std::move(name), SourceNameType::Custom);
        }

    public:

        Bool IsFile() const {
            return _type == SourceNameType::File;
        }

        Bool IsString() const {
            return _type == SourceNameType::String;
        }

        Bool IsCustom() const {
            return _type == SourceNameType::Custom;
        }

    public:

        UString GetName() const {
            return _name;
        }

        SourceNameType GetType() const {
            return _type;
        }

        U64 GetHash() const {
            return _hash;
        }

    public:

        Bool operator==(ConstLRef<GS_SourceName> name) const {
            return _hash == name.GetHash();
        }

        Bool operator!=(ConstLRef<GS_SourceName> name) const {
            return !(*this == name);
        }

    private:

        UString _name;

        SourceNameType _type;

        U64 _hash;
    };

    class GS_Source {
    public:

        GS_Source(UString source, GS_SourceName name)
                : _source(std::move(source)), _name(std::move(name)), _hash(0) {
            std::hash<std::string> sourceHasher;

            _hash = sourceHasher(_source.AsUTF8());

            _hash ^= _name.GetHash();
        }

    public:

        static std::shared_ptr<GS_Source> Create(UString source, GS_SourceName name) {
            return std::make_shared<GS_Source>(std::move(source), std::move(name));
        }

        static std::shared_ptr<GS_Source> CreateFile(UString name) {
            auto fileStream = IO::GS_InFileStream::CreateInFile(name);

            auto reader = IO::GS_Reader::Create(fileStream);

            return GS_Source::Create(reader.Read(), GS_SourceName::CreateFile(name));
        }

        static std::shared_ptr<GS_Source> CreateString(UString source) {
            return GS_Source::Create(std::move(source), GS_SourceName::CreateString());
        }

        static std::shared_ptr<GS_Source> CreateCustom(UString source, UString name) {
            return GS_Source::Create(std::move(source), GS_SourceName::CreateCustom(std::move(name)));
        }

    public:

        UString GetCodeByLocation(GS_SourceLocation location) {
            UString code;

            for (U64 index = location.GetStartPosition() - 1; index < location.GetEndPosition(); ++index) {
                code += _source[index];
            }

            return code;
        }

    public:

        UString GetSource() const {
            return _source;
        }

        GS_SourceName GetName() const {
            return _name;
        }

        U64 GetHash() const {
            return _hash;
        }

    public:

        Bool operator==(ConstLRef<GS_Source> source) const {
            return _hash == source.GetHash();
        }

        Bool operator!=(ConstLRef<GS_Source> source) const {
            return !(*this == source);
        }

    private:

        UString _source;

        GS_SourceName _name;

        U64 _hash;
    };

    using GSSourcePtr = std::shared_ptr<GS_Source>;

    using GSSourcePtrArray = std::vector<GSSourcePtr>;

}

#endif //GSLANGUAGE_GS_SOURCE_H
