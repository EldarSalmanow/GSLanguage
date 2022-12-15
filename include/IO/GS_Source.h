#ifndef GSLANGUAGE_GS_SOURCE_H
#define GSLANGUAGE_GS_SOURCE_H

#include <vector>

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    class GS_FullSourceLocation;

    class GS_Source;

    /**
     * Class for containing information about location in source
     */
    class GS_SourceLocation {
    public:

        /**
         * Constructor for source location
         * @param sourceHash Source hash
         * @param startPosition Start position
         * @param endPosition End position
         */
        GS_SourceLocation(U64 sourceHash,
                          U64 startPosition,
                          U64 endPosition);

    public:

        /**
         * Creating source location
         * @param sourceHash Source hash
         * @param startPosition Start position
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation Create(U64 sourceHash,
                                        U64 startPosition,
                                        U64 endPosition);

        /**
         * Creating source location
         * @param sourceHash Source hash
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation Create(U64 sourceHash,
                                        U64 endPosition);

        /**
         * Creating source location without source hash
         * @param startPosition Start position
         * @param endPosition End position
         * @return Source location
         */
        static GS_SourceLocation CreateWithoutHash(U64 startPosition,
                                                   U64 endPosition);

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

        /**
         * Creating source location from ful source location
         * @param fullSourceLocation Full source location
         * @param source Source
         * @return Source location
         */
        static GS_SourceLocation FromFullSourceLocation(GS_FullSourceLocation fullSourceLocation,
                                                        ConstLRef<GS_Source> source);

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
     * Class for containing full information about location in source
     */
    class GS_FullSourceLocation {
    public:

        /**
         * Constructor for full source location
         * @param sourceHash Source hash
         * @param startLine Start line
         * @param startColumn Start column
         * @param endLine End line
         * @param endColumn End column
         */
        GS_FullSourceLocation(U64 sourceHash,
                              U64 startLine,
                              U64 startColumn,
                              U64 endLine,
                              U64 endColumn);

    public:

        /**
         * Creating full source location
         * @param sourceHash Source hash
         * @param startLine Start line
         * @param startColumn Start column
         * @param endLine End line
         * @param endColumn End column
         * @return Full source location
         */
        static GS_FullSourceLocation Create(U64 sourceHash,
                                            U64 startLine,
                                            U64 startColumn,
                                            U64 endLine,
                                            U64 endColumn);

        /**
         * Creating full source location
         * @param sourceHash Source hash
         * @param endLine End line
         * @param endColumn End column
         * @return Full source location
         */
        static GS_FullSourceLocation Create(U64 sourceHash,
                                            U64 endLine,
                                            U64 endColumn);

        /**
         * Creating full source location without source hash
         * @param startLine Start line
         * @param startColumn Start column
         * @param endLine End line
         * @param endColumn End column
         * @return Full source location
         */
        static GS_FullSourceLocation CreateWithoutHash(U64 startLine,
                                                       U64 startColumn,
                                                       U64 endLine,
                                                       U64 endColumn);

        /**
         * Creating full source location without source hash
         * @param endLine End line
         * @param endColumn End column
         * @return Full source location
         */
        static GS_FullSourceLocation CreateWithoutHash(U64 endLine,
                                                       U64 endColumn);

        /**
         * Creating full source location
         * @return Full source location
         */
        static GS_FullSourceLocation Create();

    public:

        /**
         * Creating full source location from source location
         * @param sourceLocation Source location
         * @param source Source
         * @return Full source location
         */
        static GS_FullSourceLocation FromSourceLocation(GS_SourceLocation sourceLocation,
                                                        ConstLRef<GS_Source> source);

    public:

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetSourceHash() const;

        /**
         * Getter for start line
         * @return Start line
         */
        U64 GetStartLine() const;

        /**
         * Getter for start column
         * @return Start column
         */
        U64 GetStartColumn() const;

        /**
         * Getter for end line
         * @return End line
         */
        U64 GetEndLine() const;

        /**
         * Getter for end column
         * @return End column
         */
        U64 GetEndColumn() const;

    private:

        /**
         * Source hash
         */
        U64 _sourceHash;

        /**
         * Start line
         */
        U64 _startLine;

        /**
         * Start column
         */
        U64 _startColumn;

        /**
         * End line
         */
        U64 _endLine;

        /**
         * End column
         */
        U64 _endColumn;
    };

    /**
     * Buffer for containing source code
     */
    class GS_SourceBuffer {
    public:

        /**
         * Iterator type
         */
        using Iterator = UString::Iterator;

        /**
         * Const iterator type
         */
        using ConstIterator = UString::ConstIterator;

    public:

        /**
         * Constructor for source buffer
         * @param source Source code
         */
        explicit GS_SourceBuffer(UString source);

    public:

        /**
         * Creating source buffer
         * @param source Source code
         * @return Source buffer
         */
        static GS_SourceBuffer Create(UString source);

    public:

        /**
         * Getting begin source code iterator
         * @return Begin source code iterator
         */
        Iterator begin();

        /**
         * Getting end source code iterator
         * @return End source code iterator
         */
        Iterator end();

        /**
         * Getting begin source code const iterator
         * @return Begin source code const iterator
         */
        ConstIterator begin() const;

        /**
         * Getting end source code const iterator
         * @return End source code const iterator
         */
        ConstIterator end() const;

        /**
         * Getting begin source code const iterator
         * @return Begin source code const iterator
         */
        ConstIterator cbegin() const;

        /**
         * Getting end source code const iterator
         * @return End source code const iterator
         */
        ConstIterator cend() const;

    public:

        /**
         * Getting source code
         * @return Source code
         */
        ConstLRef<UString> GetSource() const;

    private:

        /**
         * Source code
         */
        UString _source;
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
        GS_SourceName(UString name,
                      SourceNameType type);

    public:

        /**
         * Creating source name
         * @param name Source name
         * @param type Source name type
         * @return Source name
         */
        static GS_SourceName Create(UString name,
                                    SourceNameType type);

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
        ConstLRef<UString> GetName() const;

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
         * Iterator (const) type
         */
        using Iterator = GS_SourceBuffer::ConstIterator;

        /**
         * Const iterator type
         */
        using ConstIterator = GS_SourceBuffer::ConstIterator;

    public:

        /**
         * Constructor for source
         * @param buffer Source buffer
         * @param name Source name
         */
        GS_Source(GS_SourceBuffer buffer,
                  GS_SourceName name);

    public:

        /**
         * Creating source
         * @param buffer Source buffer
         * @param name Source name
         * @return Source ptr
         */
        static std::unique_ptr<GS_Source> Create(GS_SourceBuffer buffer,
                                                 GS_SourceName name);

        /**
         * Creating file source
         * @param name File name
         * @return Source ptr
         */
        static std::unique_ptr<GS_Source> CreateFile(UString name);

        /**
         * Creating string source
         * @param source Source code
         * @return Source ptr
         */
        static std::unique_ptr<GS_Source> CreateString(UString source);

        /**
         * Creating custom source
         * @param source Source code
         * @param name Source name
         * @return Source ptr
         */
        static std::unique_ptr<GS_Source> CreateCustom(UString source,
                                                       UString name);

    public:

        /**
         * Getting code from source by source location
         * @param location Source location
         * @return Code in range [startPosition..endPosition]
         */
        UString GetCodeByLocation(GS_SourceLocation location) const;

    public:

        /**
         * Getting begin source buffer const iterator
         * @return Begin source buffer const iterator
         */
        ConstIterator begin() const;

        /**
         * Getting end source buffer const iterator
         * @return End source buffer const iterator
         */
        ConstIterator end() const;

        /**
         * Getting begin source buffer const iterator
         * @return Begin source buffer const iterator
         */
        ConstIterator cbegin() const;

        /**
         * Getting end source buffer const iterator
         * @return End source buffer const iterator
         */
        ConstIterator cend() const;

    public:

        /**
         * Getter for source buffer
         * @return Source buffer
         */
        ConstLRef<GS_SourceBuffer> GetBuffer() const;

        /**
         * Getter for source name
         * @return Source name
         */
        ConstLRef<GS_SourceName> GetName() const;

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
         * Source buffer
         */
        GS_SourceBuffer _buffer;

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
    using GSSourcePtr = std::unique_ptr<GS_Source>;

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
         * Adding source to manager
         * @param source Source
         * @return Source
         */
        ConstLRef<GS_Source> AddSource(GSSourcePtr source);

        /**
         * Adding file source to manager
         * @param name File name
         * @return File source
         */
        ConstLRef<GS_Source> AddFileSource(UString name);

        /**
         * Adding string source to manager
         * @param source Source code
         * @return String source
         */
        ConstLRef<GS_Source> AddStringSource(UString source);

        /**
         * Adding custom source to manager
         * @param source Source code
         * @param name Source name
         * @return Custom source
         */
        ConstLRef<GS_Source> AddCustomSource(UString source,
                                             UString name);

        /**
         * Get source from manager by source hash
         * @param sourceHash Source hash
         * @return Source
         */
        ConstLRef<GS_Source> GetSource(U64 sourceHash) const; // TODO add optional ?

        /**
         * Get source from manager by source name
         * @param sourceName Source name
         * @return Source
         */
        ConstLRef<GS_Source> GetSource(GS_SourceName sourceName) const;

        /**
         * Get file source from manager by file name
         * @param fileName File name
         * @return File source
         */
        ConstLRef<GS_Source> GetFileSource(UString fileName) const;

        /**
         * Get custom source from manager by source name
         * @return Custom source
         */
        ConstLRef<GS_Source> GetCustomSource(UString sourceName) const;

    public:

        /**
         * Getter for sources
         * @return Sources
         */
        ConstLRef<GSSourcePtrArray> GetSources() const; // TODO remove ?

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
