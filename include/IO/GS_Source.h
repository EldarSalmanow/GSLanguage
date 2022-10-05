#ifndef GSLANGUAGE_GS_SOURCE_H
#define GSLANGUAGE_GS_SOURCE_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    class GS_Source;

    /**
     * Class for containing location in source
     */
    class GS_SourceLocation {
    public:

        /**
         * Constructor for source location
         * @param sourceHash Source hash
         * @param startPosition Start position
         * @param endPosition End position
         */
        GS_SourceLocation(U64 sourceHash, U64 startPosition, U64 endPosition);

    public:

        /**
         * Creating source location
         * @param sourceHash Source hash
         * @param startPosition Start position
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation Create(U64 sourceHash, U64 startPosition, U64 endPosition);

        /**
         * Creating source location
         * @param sourceHash Source hash
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation Create(U64 sourceHash, U64 endPosition);

        /**
         * Creating source location without source hash
         * @param startPosition Start position
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation CreateWithoutHash(U64 startPosition, U64 endPosition);

        /**
         * Creating source location without source hash
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation CreateWithoutHash(U64 endPosition);

        /**
         * Creating source location
         * @return Source location
         */
        static GS_SourceLocation Create();

    public:

        // todo update
        static U64 ToSymbolLocation(U64 line, U64 column, std::shared_ptr<GS_Source> source);

        static std::pair<U64, U64> ToLineColumnLocation(U64 position, std::shared_ptr<GS_Source> source);

    public:

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetSourceHash() const;

        /**
         * Getter for start position
         * @return Start position
         */
        U64 GetStartPosition() const;

        /**
         * Getter for end position
         * @return End position
         */
        U64 GetEndPosition() const;

    private:

        /**
         * Source hash
         */
        U64 _sourceHash;

        /**
         * Start position
         */
        U64 _startPosition;

        /**
         * End position
         */
        U64 _endPosition;
    };

    /**
     * Source name type
     */
    enum class SourceNameType {
        File,
        String,
        Custom
    };

    /**
     * Class for containing source name
     */
    class GS_SourceName {
    public:

        /**
         * Constructor for source name
         * @param name Source name
         * @param type Source name type
         */
        GS_SourceName(UString name, SourceNameType type);

    public:

        /**
         * Creating source name
         * @param name Source name
         * @param type Source name type
         * @return Source name
         */
        static GS_SourceName Create(UString name, SourceNameType type);

        /**
         * Creating file source name
         * @param name File name
         * @return Source name
         */
        static GS_SourceName CreateFile(UString name);

        /**
         * Creating string source name
         * @return Source name
         */
        static GS_SourceName CreateString();

        /**
         * Creating custom source name
         * @param name Custom name
         * @return Source name
         */
        static GS_SourceName CreateCustom(UString name);

    public:

        /**
         * Is file source name
         * @return Is file source name
         */
        Bool IsFile() const;

        /**
         * Is string source name
         * @return Is string source name
         */
        Bool IsString() const;

        /**
         * Is custom source name
         * @return Is custom source name
         */
        Bool IsCustom() const;

    public:

        /**
         * Getter for source name
         * @return Source name
         */
        UString GetName() const;

        /**
         * Getter for source name type
         * @return Source name type
         */
        SourceNameType GetType() const;

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetHash() const;

    public:

        /**
         * Equality operator for source name
         * @param name Source name
         * @return Is equal source names
         */
        Bool operator==(ConstLRef<GS_SourceName> name) const;

        /**
         * Not equality operator for source name
         * @param name Source name
         * @return Is not equal source names
         */
        Bool operator!=(ConstLRef<GS_SourceName> name) const;

    private:

        /**
         * Source name
         */
        UString _name;

        /**
         * Source name type
         */
        SourceNameType _type;

        /**
         * Source hash
         */
        U64 _hash;
    };

    /**
     * Class for containing source code
     */
    class GS_Source {
    public:

        /**
         * Constructor for source
         * @param source Source code
         * @param name Source name
         */
        GS_Source(UString source, GS_SourceName name);

    public:

        /**
         * Creating source
         * @param source Source code
         * @param name Source name
         * @return Source ptr
         */
        static std::shared_ptr<GS_Source> Create(UString source, GS_SourceName name);

        /**
         * Creating file source
         * @param name File name
         * @return Source ptr
         */
        static std::shared_ptr<GS_Source> CreateFile(UString name);

        /**
         * Creating string source
         * @param source Source code
         * @return Source ptr
         */
        static std::shared_ptr<GS_Source> CreateString(UString source);

        /**
         * Creating custom source
         * @param source Source code
         * @param name Source name
         * @return Source ptr
         */
        static std::shared_ptr<GS_Source> CreateCustom(UString source, UString name);

    public:

        /**
         * Getting code from source by source location
         * @param location Source location
         * @return Code in range [startPosition..endPosition]
         */
        UString GetCodeByLocation(GS_SourceLocation location);

    public:

        /**
         * Getter for source code
         * @return Source code
         */
        UString GetSource() const;

        /**
         * Getter for source name
         * @return Source name
         */
        GS_SourceName GetName() const;

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetHash() const;

    public:

        /**
         * Equality operator for source
         * @param source Source
         * @return Is equal sources
         */
        Bool operator==(ConstLRef<GS_Source> source) const;

        /**
         * Not equality operator for source
         * @param source Source
         * @return Is not equal sources
         */
        Bool operator!=(ConstLRef<GS_Source> source) const;

    private:

        /**
         * Source code
         */
        UString _source;

        /**
         * Source name
         */
        GS_SourceName _name;

        /**
         * Source hash
         */
        U64 _hash;
    };

    /**
     * Source ptr type
     */
    using GSSourcePtr = std::shared_ptr<GS_Source>;

    /**
     * Source ptr array type
     */
    using GSSourcePtrArray = std::vector<GSSourcePtr>;

    /**
     * Class for managing sources
     */
    class GS_SourceManager {
    public:

        /**
         * Constructor for source manager
         * @param sources Sources
         */
        explicit GS_SourceManager(GSSourcePtrArray sources);

    public:

        /**
         * Creating source manager
         * @param sources Sources
         * @return Source manager ptr
         */
        static std::shared_ptr<GS_SourceManager> Create(GSSourcePtrArray sources);

        /**
         * Creating source manager
         * @return Source manager ptr
         */
        static std::shared_ptr<GS_SourceManager> Create();

    public:

        /**
         * Add source to manager
         * @param source Source
         * @return Source hash
         */
        U64 AddSource(GSSourcePtr source);

        /**
         * Get source from manager by source hash
         * @param sourceHash Source hash
         * @return Source or nullptr
         */
        GSSourcePtr GetSource(U64 sourceHash) const;

        /**
         * Get source from manager by source name
         * @param sourceName Source name
         * @return Source or nullptr
         */
        GSSourcePtr GetSource(GS_SourceName sourceName) const;

    public:

        /**
         * Getter for sources
         * @return Sources
         */
        GSSourcePtrArray GetSources() const;

    public:

        /**
         * Sources
         */
        GSSourcePtrArray _sources;
    };

    /**
     * Source manager ptr type
     */
    using GSSourceManagerPtr = std::shared_ptr<GS_SourceManager>;

}

#endif //GSLANGUAGE_GS_SOURCE_H
