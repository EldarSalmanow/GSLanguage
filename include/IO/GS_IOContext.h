#ifndef GSLANGUAGE_GS_IOCONTEXT_H
#define GSLANGUAGE_GS_IOCONTEXT_H

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

    /**
     * Message level
     */
    enum class MessageLevel {
        Note,
        Warning,
        Error,
        Fatal
    };

    // TODO update output stream to container for code ?

    class GS_IOContext {
    public:

        GS_IOContext(GSInStreamPtr standardIn,
                     GSOutStreamPtr standardOut,
                     GSOutStreamPtr standardErr,
                     GSOutStreamPtr standardLog,
                     GSSourcePtrArray inputSources,
                     GSOutStreamPtr outputSource)
                : _standardIn(std::move(standardIn)),
                  _standardOut(std::move(standardOut)),
                  _standardErr(std::move(standardErr)),
                  _standardLog(std::move(standardLog)),
                  _inputSources(std::move(inputSources)),
                  _outputSource(std::move(outputSource)) {}

    public:

        static std::shared_ptr<GS_IOContext> Create(GSInStreamPtr standardIn,
                                                    GSOutStreamPtr standardOut,
                                                    GSOutStreamPtr standardErr,
                                                    GSOutStreamPtr standardLog,
                                                    GSSourcePtrArray inputSources,
                                                    GSOutStreamPtr outputSource) {
            return std::make_shared<GS_IOContext>(std::move(standardIn),
                                                  std::move(standardOut),
                                                  std::move(standardErr),
                                                  std::move(standardLog),
                                                  std::move(inputSources),
                                                  std::move(outputSource));
        }

        static std::shared_ptr<GS_IOContext> Create(GSSourcePtrArray inputSources, GSOutStreamPtr outputSource) {
            return GS_IOContext::Create(GS_InConsoleStream::CreateCIn(),
                                        GS_OutConsoleStream::CreateCOut(),
                                        GS_OutConsoleStream::CreateCErr(),
                                        GS_OutConsoleStream::CreateCLog(),
                                        std::move(inputSources),
                                        std::move(outputSource));
        }

        static std::shared_ptr<GS_IOContext> Create() {
            return GS_IOContext::Create(GSSourcePtrArray(), GSOutStreamPtr());
        }

    public:

        Void In(LRef<UString> string) const {
            _standardIn->GetInStream() >> string;
        }

        Void Out(UString string) const {
            _standardOut->GetOutStream() << string;
        }

        Void Err(UString string) const {
            _standardErr->GetOutStream() << string;
        }

        Void Log(UString string) const {
            _standardLog->GetOutStream() << string;
        }

    public:

        Void AddInputSource(GSSourcePtr inputSource) {
            _inputSources.emplace_back(std::move(inputSource));
        }

        GSSourcePtr GetInputSource(U64 inputSourceHash) const {
            for (auto &inputSource : _inputSources) {
                if (inputSource->GetHash() == inputSourceHash) {
                    return inputSource;
                }
            }

            return nullptr;
        }

        GSSourcePtr GetInputSource(GS_SourceName inputSourceName) const {
            for (auto &inputSource : _inputSources) {
                if (inputSource->GetName() == inputSourceName) {
                    return inputSource;
                }
            }

            return nullptr;
        }

    public:

        /*
         * Example:
         *
         * Print("Update GSLanguageCompiler to new 2.10.2 version.",
         *       MessageLevel::Note);
         *
         * Note: Update GSLanguageCompiler to new 2.10.2 version.
         */
        Void Message(UString message, MessageLevel messageLevel) const;

        /*
         * Example:
         *
         * Print("Unknown type 'I31'!",
         *       MessageLevel::Error,
         *       SourceRange::Create("main.gs", 1, 8, 10),
         *       "var a: I31 = 10");
         *
         * main.gs 1: >> var a: I31 = 10
         *                      ^^^
         * Error: Unknown type 'I31'!
         */
        Void Message(UString message, MessageLevel messageLevel, GS_SourceLocation sourceLocation, UString text) const;

        /*
         * Example:
         *
         * Print("Found 2 'say_hello' function for calling.",
         *       MessageLevel::Note,
         *       { SourceRange::Create("main.gs", 5, 1, 33), SourceRange::Create("main.gs", 8, 1, 41) },
         *       { "func say_hello(String name): Void", "func say_hello(String name, U8 age): Void" });
         *
         * main.gs 5: >> func say_hello(String name): Void
         *               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         * main.gs 8: >> func say_hello(String name, U8 age): Void
         *               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         * Note: Found 2 'say_hello' function for calling.
         */
        Void Message(UString message, MessageLevel messageLevel, std::vector<GS_SourceLocation> sourceLocations, std::vector<UString> texts);

    public:

        GSInStreamPtr GetStandardIn() const {
            return _standardIn;
        }

        GSOutStreamPtr GetStandardOut() const {
            return _standardOut;
        }

        GSOutStreamPtr GetStandardErr() const {
            return _standardErr;
        }

        GSOutStreamPtr GetStandardLog() const {
            return _standardLog;
        }

        GSSourcePtrArray GetInputSources() const {
            return _inputSources;
        }

        GSOutStreamPtr GetOutputSource() const {
            return _outputSource;
        }

    private:

        GSInStreamPtr _standardIn;

        GSOutStreamPtr _standardOut;

        GSOutStreamPtr _standardErr;

        GSOutStreamPtr _standardLog;

        GSSourcePtrArray _inputSources;

        GSOutStreamPtr _outputSource;
    };

    using GSIOContextPtr = std::shared_ptr<GS_IOContext>;

}

#endif //GSLANGUAGE_GS_IOCONTEXT_H
