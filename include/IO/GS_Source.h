#ifndef GSLANGUAGE_GS_SOURCE_H
#define GSLANGUAGE_GS_SOURCE_H

#include <vector>

#include <optional>

#include <Driver/GS_GlobalContext.h>

namespace GSLanguageCompiler::IO {

    /**
     * Invalid hash constant
     */
    inline constexpr U64 InvalidHash = 0;

    /**
     * Invalid source position constant
     */
    inline constexpr U64 InvalidPosition = 0;

    /**
     * Class for containing information about source location
     */
    class GS_SourceLocation {
    public:

        /*
         *
         * GS_SourceLocation PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for source location
         * @param position Position
         * @param sourceHash Source hash
         */
        GS_SourceLocation(U64 position,
                          U64 sourceHash);

    public:

        /*
         *
         * GS_SourceLocation PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating concrete source location
         * @param position Position
         * @param sourceHash Source hash
         * @return Source location
         */
        static GS_SourceLocation Create(U64 position,
                                        U64 sourceHash);

        /**
         * Creating source location without source hash
         * @param position Position
         * @return Source location
         */
        static GS_SourceLocation Create(U64 position);

        /**
         * Creating invalid source location
         * @return Source location
         */
        static GS_SourceLocation Create();

    public:

        /*
         *
         * GS_SourceLocation PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for position
         * @return Position
         */
        U64 GetPosition() const;

        /**
         * Getter for source hash
         * @return Source hash
         */
        U64 GetSourceHash() const;

    public:

        /*
         *
         * GS_SourceLocation PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for source location
         * @param sourceLocation Source location
         * @return Is equal source locations
         */
        Bool operator==(ConstLRef<GS_SourceLocation> sourceLocation) const;

        /**
         * Comparison operator for source location
         * @param sourceLocation Source location
         * @return Partial comparison ordering
         */
        std::partial_ordering operator<=>(ConstLRef<GS_SourceLocation> sourceLocation) const;

    private:

        /*
         *
         * GS_SourceLocation PRIVATE FIELDS
         *
         */

        /**
         * Position
         */
        U64 _position;

        /**
         * Source hash
         */
        U64 _sourceHash;
    };

    /**
     * Converting byte source location to line column source location
     * @param sourceLocation Byte source location
     * @return Line column source location
     */
    std::tuple<U64, U64, U64> ToLineColumnLocation(ConstLRef<GS_SourceLocation> sourceLocation);

    /**
     * Converting line column source location to byte source location
     * @param line Line
     * @param column Column
     * @param sourceHash Source hash
     * @return Byte source location
     */
    GS_SourceLocation ToByteLocation(U64 line,
                                     U64 column,
                                     U64 sourceHash);

    /**
     * Class for containing source location range
     */
    class GS_SourceRange {
    public:

        /*
         *
         * GS_SourceRange PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for source location range [startLocation..endLocation]
         * @param startLocation Start source location
         * @param endLocation End source location
         */
        GS_SourceRange(GS_SourceLocation startLocation,
                       GS_SourceLocation endLocation)
                : _startLocation(startLocation),
                  _endLocation(endLocation) {
            if (_startLocation.GetSourceHash() != _endLocation.GetSourceHash()) {
                Driver::GlobalContext().Exit("Can`t create source location range with different source hash in source locations!");
            }

            if (_startLocation.GetPosition() != InvalidPosition && _startLocation.GetSourceHash() != InvalidHash
             && _endLocation.GetPosition() != InvalidPosition && _endLocation.GetSourceHash() != InvalidHash) {
                if (_startLocation > _endLocation) {
                    Driver::GlobalContext().Exit("Can`t create source range with start location \"bigger\" than end location!");
                }
            }
        }

    public:

        /*
         *
         * GS_SourceRange PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating source location range
         * @param startLocation Start source location
         * @param endLocation End source location
         * @return Source location range [startLocation..endLocation]
         */
        static GS_SourceRange Create(GS_SourceLocation startLocation,
                                     GS_SourceLocation endLocation) {
            return GS_SourceRange(startLocation,
                                  endLocation);
        }

        /**
         * Creating invalid source location range
         * @return Source location range
         */
        static GS_SourceRange Create() {
            return GS_SourceRange::Create(GS_SourceLocation::Create(),
                                          GS_SourceLocation::Create());
        }

    public:

        /*
         *
         * GS_SourceRange PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for start source location
         * @return Start source location
         */
        GS_SourceLocation GetStartLocation() const {
            return _startLocation;
        }

        /**
         * Getter for end source location
         * @return End source location
         */
        GS_SourceLocation GetEndLocation() const {
            return _endLocation;
        }

    public:

        /*
         *
         * GS_SourceRange PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for source location range
         * @param locationRange Source location range
         * @return Is equal source location ranges
         */
        Bool operator==(ConstLRef<GS_SourceRange> locationRange) const {
            return _startLocation == locationRange.GetStartLocation()
                && _endLocation == locationRange.GetEndLocation();
        }

    private:

        /*
         *
         * GS_SourceRange PRIVATE FIELDS
         *
         */

        /**
         * Start source location
         */
        GS_SourceLocation _startLocation;

        /**
         * End source location
         */
        GS_SourceLocation _endLocation;
    };

    /**
     * Class for containing source code
     */
    class GS_SourceBuffer {
    public:

        /*
         *
         * GS_SourceBuffer PUBLIC TYPES
         *
         */

        /**
         * Iterator type
         */
        using Iterator = UString::Iterator;

        /**
         * Const iterator type
         */
        using ConstIterator = UString::ConstIterator;

    public:

        /*
         *
         * GS_SourceBuffer PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for source buffer
         * @param source Source code
         */
        explicit GS_SourceBuffer(UString source);

    public:

        /*
         *
         * GS_SourceBuffer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating source buffer
         * @param source Source code
         * @return Source buffer
         */
        static GS_SourceBuffer Create(UString source);

    public:

        /*
         *
         * GS_SourceBuffer PUBLIC METHODS
         *
         */

        /**
         * Getting source code iterator by source location
         * @param sourceLocation Source location
         * @return Source code iterator
         */
        Iterator GetIteratorByLocation(GS_SourceLocation sourceLocation);

        /**
         * Getting source code const iterator by source location
         * @param sourceLocation Source location
         * @return Source code const iterator
         */
        ConstIterator GetIteratorByLocation(GS_SourceLocation sourceLocation) const;

        /**
         * Getting code from source buffer in source location range
         * @param locationRange Source location range
         * @return Code in range [startLocation..endLocation)
         */
        UString GetCodeInRange(ConstLRef<GS_SourceRange> locationRange) const {
            auto startLocation = locationRange.GetStartLocation();
            auto endLocation = locationRange.GetEndLocation();

            auto startIterator = GetIteratorByLocation(startLocation);
            auto endIterator = GetIteratorByLocation(endLocation);

            UString code;

            for (; startIterator != endIterator; ++startIterator) {
                code += *startIterator;
            }

            return code;
        }

    public:

        /*
         *
         * GS_SourceBuffer PUBLIC ITERATOR METHODS
         *
         */

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

        /*
         *
         * GS_SourceBuffer PUBLIC GETTER METHODS
         *
         */

        /**
         * Getting source code
         * @return Source code
         */
        ConstLRef<UString> GetSource() const;

    public:

        /*
         *
         * GS_SourceBuffer PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for source buffer
         * @param sourceBuffer Source buffer
         * @return Is equal source buffers
         */
        Bool operator==(ConstLRef<GS_SourceBuffer> sourceBuffer) const;

        /**
         * Index operator for source buffer
         * @param index Index
         * @return Symbol by index in source code
         */
        LRef<USymbol> operator[](ConstLRef<U64> index);

        /**
         * Index operator for source buffer
         * @param index Index
         * @return Symbol by index in source code
         */
        ConstLRef<USymbol> operator[](ConstLRef<U64> index) const;

    private:

        /*
         *
         * GS_SourceBuffer PRIVATE FIELDS
         *
         */

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

        /*
         *
         * GS_SourceName PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for source name
         * @param name Source name
         * @param type Source name type
         */
        GS_SourceName(UString name,
                      SourceNameType type);

    public:

        /*
         *
         * GS_SourceName PUBLIC STATIC CREATION METHODS
         *
         */

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

        /*
         *
         * GS_SourceName PUBLIC METHODS
         *
         */

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

        /*
         *
         * GS_SourceName PUBLIC GETTER METHODS
         *
         */

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

        /*
         *
         * GS_SourceName PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for source name
         * @param name Source name
         * @return Is equal source names
         */
        Bool operator==(ConstLRef<GS_SourceName> name) const;

    private:

        /*
         *
         * GS_SourceName PRIVATE FIELDS
         *
         */

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

        /*
         *
         * GS_Source PUBLIC TYPES
         *
         */

        /**
         * Iterator type (const iterator type)
         */
        using Iterator = GS_SourceBuffer::ConstIterator;

        /**
         * Const iterator type
         */
        using ConstIterator = GS_SourceBuffer::ConstIterator;

    public:

        /*
         *
         * GS_Source PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for source
         * @param buffer Source buffer
         * @param name Source name
         */
        GS_Source(GS_SourceBuffer buffer,
                  GS_SourceName name);

    public:

        /*
         *
         * GS_Source PUBLIC STATIC CREATE METHODS
         *
         */

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

        /*
         *
         * GS_Source PUBLIC METHODS
         *
         */

        /**
         * Getting source code iterator by source location
         * @param sourceLocation Source location
         * @return Source code iterator
         */
        Iterator GetIteratorByLocation(GS_SourceLocation sourceLocation) {
            return _buffer.GetIteratorByLocation(sourceLocation);
        }

        /**
         * Getting source code const iterator by source location
         * @param sourceLocation Source location
         * @return Source code const iterator
         */
        ConstIterator GetIteratorByLocation(GS_SourceLocation sourceLocation) const {
            return _buffer.GetIteratorByLocation(sourceLocation);
        }

        /**
         * Getting code from source in source location range
         * @param locationRange Source location range
         * @return Code in range [startLocation..endLocation)
         */
        UString GetCodeInRange(GS_SourceRange locationRange) const {
            return _buffer.GetCodeInRange(locationRange);
        }

    public:

        /*
         *
         * GS_Source PUBLIC ITERATOR METHODS
         *
         */

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

        /*
         *
         * GS_Source PUBLIC GETTER METHODS
         *
         */

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

        /*
         *
         * GS_Source PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for source
         * @param source Source
         * @return Is equal sources
         */
        Bool operator==(ConstLRef<GS_Source> source) const;

        /**
         * Index operator for source
         * @param index Index
         * @return Symbol by index in source buffer
         */
        LRef<USymbol> operator[](ConstLRef<U64> index);

        /**
         * Index operator for source
         * @param index Index
         * @return Symbol by index in source buffer
         */
        ConstLRef<USymbol> operator[](ConstLRef<U64> index) const;

    private:

        /*
         *
         * GS_Source PRIVATE FIELDS
         *
         */

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

        /*
         *
         * GS_SourceManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for source manager
         * @param sources Sources
         */
        explicit GS_SourceManager(GSSourcePtrArray sources);

    public:

        /*
         *
         * GS_SourceManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating source manager
         * @param sources Sources
         * @return Source manager ptr
         */
        static std::unique_ptr<GS_SourceManager> Create(GSSourcePtrArray sources);

        /**
         * Creating source manager
         * @return Source manager ptr
         */
        static std::unique_ptr<GS_SourceManager> Create();

    public:

        /*
         *
         * GS_SourceManager PUBLIC METHODS
         *
         */

        /**
         * Adding source
         * @param source Source
         * @return Source
         */
        ConstLRef<GS_Source> AddSource(GSSourcePtr source);

        /**
         * Adding file source
         * @param name File name
         * @return File source
         */
        ConstLRef<GS_Source> AddFileSource(UString name);

        /**
         * Adding string source
         * @param source Source code
         * @return String source
         */
        ConstLRef<GS_Source> AddStringSource(UString source);

        /**
         * Adding custom source
         * @param source Source code
         * @param name Source name
         * @return Custom source
         */
        ConstLRef<GS_Source> AddCustomSource(UString source,
                                             UString name);

        /**
         * Getting source by source hash
         * @param sourceHash Source hash
         * @return Source or null
         */
        std::optional<GS_Source> GetSource(U64 sourceHash) const;

        /**
         * Getting source by source name
         * @param sourceName Source name
         * @return Source or null
         */
        std::optional<GS_Source> GetSource(GS_SourceName sourceName) const;

        /**
         * Getting file source by file name
         * @param fileName File name
         * @return File source or null
         */
        std::optional<GS_Source> GetFileSource(UString fileName) const;

        /**
         * Getting custom source by source name
         * @return Custom source or null
         */
        std::optional<GS_Source> GetCustomSource(UString sourceName) const;

    public:

        /*
         *
         * GS_SourceManager PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for sources
         * @return Sources
         */
        ConstLRef<GSSourcePtrArray> GetSources() const;

    public:

        /*
         *
         * GS_SourceManager PRIVATE FIELDS
         *
         */

        /**
         * Sources
         */
        GSSourcePtrArray _sources;
    };

    /**
     * Source manager ptr type
     */
    using GSSourceManagerPtr = std::unique_ptr<GS_SourceManager>;

}

#endif //GSLANGUAGE_GS_SOURCE_H
