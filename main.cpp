#include <IO/IO.h>
#include <AST/AST.h>

#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

class GlobalContext {
public:

    GlobalContext() = delete;

public:

    static I32 InitializeIO(IO::GSInStreamPtr  standardIn,
                            IO::GSOutStreamPtr standardOut,
                            IO::GSOutStreamPtr standardErr,
                            IO::GSOutStreamPtr standardLog) {
        _standardIn = standardIn;
        _standardOut = standardIn;
        _standardErr = standardIn;
        _standardLog = standardIn;

        return 0;
    }

    static I32 Initialize(IO::GSInStreamPtr  standardIn,
                          IO::GSOutStreamPtr standardOut,
                          IO::GSOutStreamPtr standardErr,
                          IO::GSOutStreamPtr standardLog) {
        if (!InitializeIO(std::move(standardIn),
                          std::move(standardOut),
                          std::move(standardErr),
                          std::move(standardLog))) {
            return 1;
        }

        return 0;
    }

    static I32 Initialize() {
        return Initialize(IO::GS_InConsoleStream::CreateCIn(),
                   IO::GS_OutConsoleStream::CreateCOut(),
                   IO::GS_OutConsoleStream::CreateCErr(),
                   IO::GS_OutConsoleStream::CreateCLog());
    }

public:

    static Void In(LRef<UString> string) {
        _standardIn->GetInStream() >> string;
    }

    static Void Out(ConstLRef<UString> string) {
        _standardOut->GetOutStream() << string;
    }

    static Void Err(ConstLRef<UString> string) {
        _standardErr->GetOutStream() << string;
    }

    static Void Log(ConstLRef<UString> string) {
        _standardLog->GetOutStream() << string;
    }

private:

    static IO::GSInStreamPtr  _standardIn;

    static IO::GSOutStreamPtr _standardOut;

    static IO::GSOutStreamPtr _standardErr;

    static IO::GSOutStreamPtr _standardLog;
};

enum class CompilingResult : I32 {
    Success = 0,
    Failure = 1
};

class Arguments {
public:

    Arguments(std::vector<UString> inputFileNames, UString outputFileName)
            : _inputFileNames(std::move(inputFileNames)), _outputFileName(std::move(outputFileName)) {}

public:

    static Arguments Create(std::vector<UString> inputFileNames, UString outputFileName) {
        return Arguments(std::move(inputFileNames), std::move(outputFileName));
    }

    static Arguments Create(std::vector<UString> inputFileNames) {
        // TODO

        return Arguments::Create(std::move(inputFileNames), UString());
    }

    static Arguments Create() {
        return Arguments::Create(std::vector<UString>(), UString());
    }

public:

    static Arguments Create(I32 argc, Ptr<Ptr<C>> argv) {
        // TODO

        return Arguments::Create();
    }

public:

    std::vector<UString> GetInputFileNames() const {
        return _inputFileNames;
    }

    UString GetOutputFileName() const {
        return _outputFileName;
    }

public:

    std::vector<UString> _inputFileNames;

    UString _outputFileName;
};

enum class SourceNameType {
    File,
    String,
    Custom
};

class SourceLocation {
public:

    SourceLocation(U64 sourceHash, U64 startPosition, U64 endPosition)
            : _sourceHash(sourceHash), _startPosition(startPosition), _endPosition(endPosition) {}

public:

    static SourceLocation Create(U64 sourceHash, U64 startPosition, U64 endPosition) {
        return SourceLocation(sourceHash, startPosition, endPosition);
    }

    static SourceLocation Create(U64 sourceHash, U64 endPosition) {
        return SourceLocation::Create(sourceHash, 1, endPosition);
    }

    static SourceLocation CreateWithoutHash(U64 startPosition, U64 endPosition) {
        return SourceLocation::Create(0, startPosition, endPosition);
    }

    static SourceLocation CreateWithoutHash(U64 endPosition) {
        return SourceLocation::CreateWithoutHash(1, endPosition);
    }

    static SourceLocation Create() {
        return SourceLocation::Create(0, 0, 0);
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

class SourceName {
public:

    SourceName(UString name, SourceNameType type)
            : _name(std::move(name)), _type(type), _hash(0) {
        std::hash<std::string> nameHasher;

        _hash = nameHasher(_name.AsUTF8());

        std::hash<U8> typeHasher;

        _hash ^= typeHasher(StaticCast<U8>(type));
    }

public:

    static SourceName Create(UString name, SourceNameType type) {
        return SourceName(std::move(name), type);
    }

    static SourceName CreateFile(UString name) {
        return SourceName::Create(std::move(name), SourceNameType::File);
    }

    static SourceName CreateString() {
        static U64 id = 1;

        auto name = UString(std::string("<string>_") + std::to_string(id));

        ++id;

        return SourceName::Create(name, SourceNameType::String);
    }

    static SourceName CreateCustom(UString name) {
        return SourceName::Create(std::move(name), SourceNameType::Custom);
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

    Bool operator==(ConstLRef<SourceName> name) const {
        return _hash == name.GetHash();
    }

    Bool operator!=(ConstLRef<SourceName> name) const {
        return !(*this == name);
    }

private:

    UString _name;

    SourceNameType _type;

    U64 _hash;
};

class Source {
public:

    Source(UString source, SourceName name)
            : _source(std::move(source)), _name(std::move(name)), _hash(0) {
        std::hash<std::string> sourceHasher;

        _hash = sourceHasher(_source.AsUTF8());

        _hash ^= _name.GetHash();
    }

public:

    static std::shared_ptr<Source> Create(UString source, SourceName name) {
        return std::make_shared<Source>(std::move(source), std::move(name));
    }

    static std::shared_ptr<Source> CreateFile(UString name) {
        auto fileStream = IO::GS_InFileStream::CreateInFile(name);

        auto source = IO::GS_Reader::Run(fileStream);

        return Source::Create(source, SourceName::CreateFile(name));
    }

    static std::shared_ptr<Source> CreateString(UString source) {
        return Source::Create(std::move(source), SourceName::CreateString());
    }

    static std::shared_ptr<Source> CreateCustom(UString source, UString name) {
        return Source::Create(std::move(source), SourceName::CreateCustom(std::move(name)));
    }

public:

    UString GetCodeByLocation(SourceLocation location) const {
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

    SourceName GetName() const {
        return _name;
    }

    U64 GetHash() const {
        return _hash;
    }

public:

    Bool operator==(ConstLRef<Source> source) const {
        return _hash == source.GetHash();
    }

    Bool operator!=(ConstLRef<Source> source) const {
        return !(*this == source);
    }

private:

    UString _source;

    SourceName _name;

    U64 _hash;
};

using SourcePtr = std::shared_ptr<Source>;

using SourcePtrArray = std::vector<SourcePtr>;

enum class MessageLevel {
    Note,
    Warning,
    Error,
    Fatal
};

// TODO ??
class Context {
public:

    Context(IO::GSInStreamPtr    standardIn,
            IO::GSOutStreamPtr   standardOut,
            IO::GSOutStreamPtr   standardErr,
            IO::GSOutStreamPtr   standardLog,
            SourcePtrArray       inputSources,
            IO::GSOutStreamPtr   outputStream,
            AST::GSASTContextPtr astContext);

public:

    static std::shared_ptr<Context> Create(IO::GSInStreamPtr    standardIn,
                                           IO::GSOutStreamPtr   standardOut,
                                           IO::GSOutStreamPtr   standardErr,
                                           IO::GSOutStreamPtr   standardLog,
                                           SourcePtrArray       inputSources,
                                           IO::GSOutStreamPtr   outputStream,
                                           AST::GSASTContextPtr astContext);

    static std::shared_ptr<Context> Create(SourcePtrArray       inputSources,
                                           IO::GSOutStreamPtr   outputStream,
                                           AST::GSASTContextPtr astContext);

    static std::shared_ptr<Context> Create(SourcePtrArray     inputSources,
                                           IO::GSOutStreamPtr outputStream);

    static std::shared_ptr<Context> Create();

public:

    static std::shared_ptr<Context> Create(Arguments arguments);

public:

    Void In(LRef<UString> string);

    Void Out(ConstLRef<UString> string);

    Void Err(ConstLRef<UString> string);

    Void Log(ConstLRef<UString> string);

public:

    Void AddInputSource(SourcePtr inputSource);

    SourcePtr GetInputSource(U64 inputSourceHash) const;

    SourcePtr GetInputSource(SourceName inputSourceName) const;

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
    Void Message(UString message, MessageLevel messageLevel, SourceLocation sourceLocation, UString text) const;

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
    Void Message(UString message, MessageLevel messageLevel, std::vector<SourceLocation> sourceLocations, std::vector<UString> texts);

private:

    IO::GSInStreamPtr    _standardIn;

    IO::GSOutStreamPtr   _standardOut;

    IO::GSOutStreamPtr   _standardErr;

    IO::GSOutStreamPtr   _standardLog;

    IO::GSSourcePtrArray _inputSources;

    IO::GSOutStreamPtr   _outputStream;

    AST::GSASTContextPtr _astContext;
};

using ContextPtr = std::shared_ptr<Context>;

class Session {
public:

    explicit Session(ContextPtr context);

public:

    static std::shared_ptr<Session> Create(ContextPtr context);

    static std::shared_ptr<Session> Create();

public:

    CompilingResult Run();

public:

    ContextPtr GetContext() const;

private:

    ContextPtr _context;
};

using SessionPtr = std::shared_ptr<Session>;

using SessionPtrArray = std::vector<SessionPtr>;

class Compiler {
public:

    explicit Compiler(SessionPtrArray sessions);

public:

    static std::shared_ptr<Compiler> Create(SessionPtrArray sessions);

    static std::shared_ptr<Compiler> Create();

public:

    static std::shared_ptr<Compiler> Create(Arguments arguments);

public:

    static CompilingResult Start(I32 argc, Ptr<Ptr<C>> argv);

public:

    CompilingResult Run();

public:

    Void AddSession(SessionPtr session);

public:

    SessionPtrArray GetSessions() const;

private:

    SessionPtrArray _sessions;
};

using CompilerPtr = std::shared_ptr<Compiler>;

I32 Run(I32 argc, Ptr<Ptr<C>> argv) {
    return StaticCast<I32>(Compiler::Start(argc, argv));
}

//#include <IO/IO.h>
//#include <AST/AST.h>
//
//void f() {
//    IO::GSSourcePtrArray InSources = {
//            IO::GS_Source::CreateCustom("func main() { var name = \"Eldar\"\n printl(\"Hello, ${name}!\") }"_us, "main.gs"_us)
//    };
//
//    IO::GSOutStreamPtr OutSource = IO::GS_OutFileStream::CreateOutFile("main.exe"_us);
//
//    auto IOC = IO::GS_IOContext::Create(InSources, OutSource);
//
//    auto ASTC = AST::GS_ASTContext::Create();
//
//    auto CC = Driver::GS_SessionContext::Create(IOC, ASTC);
//
//    auto IOC_ = CC->GetIOContext();
//
//    IOC_->Log("Starting GSLanguageCompiler...\n"_us);
//
//    auto Source = IOC_->GetInputSource(IO::GS_SourceName::CreateFile("<string>_1"));
//
//    IOC_->Out(Source->GetCodeByLocation(IO::GS_SourceLocation::CreateWithoutHash(1, 11)) + '\n');
//}
//
//I32 main(I32 argc, Ptr<Ptr<C>> argv) {
//    f();
//
//    return 0;
//}

/**
 *
 * CompilingContext -> IOContext, ASTContext
 *
 * IOContext -> StandardIn, StandardOut, StandardErr, StandardLog, InSources, OutSource
 *
 * ASTContext -> ASTTypeContext
 *
 * ASTTypeContext -> VoidType, I32Type, StringType
 *
 */
