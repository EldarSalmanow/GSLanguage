#ifndef GSLANGUAGE_GS_SOURCEMANAGER_H
#define GSLANGUAGE_GS_SOURCEMANAGER_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    enum class SourceNameType {
        File,
        String
    };

    class GS_SourceName {
    public:

        GS_SourceName(UString name, SourceNameType type);

    public:

        static GS_SourceName Create(UString name, SourceNameType type);

        static GS_SourceName CreateFile(UString name);

        static GS_SourceName CreateString();

    public:

        UString GetName() const;

        SourceNameType GetType() const;

        U64 GetHash() const;

    public:

        Bool operator==(ConstLRef<GS_SourceName> name) const;

        Bool operator!=(ConstLRef<GS_SourceName> name) const;

    private:

        UString _name;

        SourceNameType _type;

        U64 _hash;
    };

    class GS_Source {
    public:

        GS_Source(UString source, GS_SourceName name);

    public:

        static std::shared_ptr<GS_Source> Create(UString source, GS_SourceName name);

        static std::shared_ptr<GS_Source> CreateFile(GS_SourceName name);

        static std::shared_ptr<GS_Source> CreateString(UString source);

    public:

//        UString GetCodeByLocation(SourceLocation location) {
//            UString code;
//
//            for (U64 index = location.GetStartPosition() - 1; index < location.GetEndPosition(); ++index) {
//                code += _source[index];
//            }
//
//            return code;
//        }

//        std::pair<U64, U64> GetLineAndColumnPosition(U64 bytePosition) {
//            U64 line = 0, column = 0;
//
//            for (U64 index = 0; index < _linesPositions.size(); ++index) {
//                auto [startLinePosition, endLinePosition] = _linesPositions[index];
//
//                if (startLinePosition <= bytePosition && bytePosition <= endLinePosition) {
//                    line = index + 1;
//
//                    column = bytePosition - (startLinePosition - 1);
//
//                    return std::make_pair(line, column);
//                }
//            }
//
//            return std::make_pair(0, 0);
//        }

//        UString GetLine(U64 line) {
//            auto [startLinePosition, endLinePosition] = _linesPositions[line - 1];
//
//            return GetCodeByLocation(SourceLocation::Create(_hash, startLinePosition, endLinePosition));
//        }

    public:

        UString GetSource() const;

        GS_SourceName GetName() const;

        U64 GetHash() const;

    public:

        Bool operator==(ConstLRef<GS_Source> source) const;

        Bool operator!=(ConstLRef<GS_Source> source) const;

    private:

        UString _source;

//        std::vector<UString> _sourceLines;
//
//        std::vector<std::pair<U64, U64>> _linesPositions;

        GS_SourceName _name;

        U64 _hash;
    };

    using GSSourcePtr = std::shared_ptr<GS_Source>;

    using GSSourcePtrArray = std::vector<GSSourcePtr>;

    class GS_SourceManager {
    public:

        explicit GS_SourceManager(GSSourcePtrArray sources);

    public:

        static std::shared_ptr<GS_SourceManager> Create(GSSourcePtrArray sources);

        static std::shared_ptr<GS_SourceManager> Create();

    public:

        Bool AddSource(GSSourcePtr source);

        GSSourcePtr GetSource(U64 hash) const;

        GSSourcePtr GetSource(GS_SourceName name) const;

    public:

        GSSourcePtrArray GetSources() const;

    private:

        GSSourcePtrArray _sources;
    };

    using GSSourceManagerPtr = std::shared_ptr<GS_SourceManager>;

}

#endif //GSLANGUAGE_GS_SOURCEMANAGER_H
