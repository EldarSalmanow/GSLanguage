#include <GS_SourceManager.h>

#include <IO/GS_Reader.h>

namespace GSLanguageCompiler::IO {

    GS_SourceName::GS_SourceName(UString name, SourceNameType type)
            : _name(std::move(name)), _type(type), _hash(0) {
        std::hash<std::string> hasher;

        _hash = hasher(_name.AsUTF8());
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
            : _source(std::move(source)), /*_linesPositions(),*/ _name(std::move(name)), _hash(0) {
        // TODO check
//            U64 startLinePosition = 1, endLinePosition = 0;
//
//            for (U64 index = 0; index < _source.Size(); ++index) {
//                if (_source[index] == '\n') {
//                    endLinePosition = index;
//
//                    _linesPositions.emplace_back(std::make_pair(startLinePosition, endLinePosition));
//
//                    startLinePosition = index + 1;
//
//                    endLinePosition = 0;
//                }
//            }
//
//            _linesPositions.emplace_back(std::make_pair(startLinePosition, _source.Size()));

        std::hash<std::string> hasher;

        _hash = hasher(_source.AsUTF8());

        _hash ^= _name.GetHash();
    }

    std::shared_ptr<GS_Source> GS_Source::Create(UString source, GS_SourceName name) {
        return std::make_shared<GS_Source>(std::move(source), std::move(name));
    }

    std::shared_ptr<GS_Source> GS_Source::CreateFile(GS_SourceName name) {
        auto fileStream = IO::GS_InFileStream::CreateInFile(name.GetName());

        auto reader = IO::GS_Reader::Create(fileStream);

        return GS_Source::Create(reader.Read(), std::move(name));
    }

    std::shared_ptr<GS_Source> GS_Source::CreateString(UString source) {
        return GS_Source::Create(std::move(source), GS_SourceName::CreateString());
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

    Bool GS_SourceManager::AddSource(GSSourcePtr source) {
        for (auto &source_ : _sources) {
            if (source_ == source) {
                return false;
            }
        }

        _sources.emplace_back(std::move(source));

        return true;
    }

    GSSourcePtr GS_SourceManager::GetSource(U64 hash) const {
        for (auto &source : _sources) {
            if (source->GetHash() == hash) {
                return source;
            }
        }

        return nullptr;
    }

    GSSourcePtr GS_SourceManager::GetSource(GS_SourceName name) const {
        for (auto &source : _sources) {
            if (source->GetName() == name) {
                return source;
            }
        }

        return nullptr;
    }

    GSSourcePtrArray GS_SourceManager::GetSources() const {
        return _sources;
    }

}
