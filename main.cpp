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

// TODO replace to GSStream`s ?
I32 InitializeIO(Ptr<std::istream> standardIn,
                 Ptr<std::ostream> standardOut,
                 Ptr<std::ostream> standardErr,
                 Ptr<std::ostream> standardLog);

I32 InitializeIO();

I32 InitializeCompiler();

Void In(UString &string);

Void Out(ConstLRef<UString> string);

Void Err(ConstLRef<UString> string);

Void Log(ConstLRef<UString> string);

enum class CompilingResult : I32 {
    Success = 0,
    Failure = 1
};

class Arguments {
public:

    Arguments(std::vector<UString> inputFileNames, UString outputFileName);

public:

    static Arguments Create(std::vector<UString> inputFileNames, UString outputFileName);

    static Arguments Create(std::vector<UString> inputFileNames);

    static Arguments Create();

public:

    static Arguments Create(I32 argc, Ptr<Ptr<C>> argv);

public:

    std::vector<UString> GetInputFileNames() const;

    UString GetOutputFileName() const;

public:

    std::vector<UString> _inputFileNames;

    UString _outputFileName;
};

// TODO ??
class Context {
public:

    Context(IO::GSInStreamPtr standardIn,
            IO::GSOutStreamPtr standardOut,
            IO::GSOutStreamPtr standardErr,
            IO::GSOutStreamPtr standardLog,
            AST::GSASTContextPtr astContext);

public:

    static std::shared_ptr<Context> Create();

public:

    static std::shared_ptr<Context> Create(Arguments arguments);

public:

    Void In(UString &string);

    Void Out(ConstLRef<UString> string);

    Void Err(ConstLRef<UString> string);

    Void Log(ConstLRef<UString> string);

private:

    IO::GSInStreamPtr _standardIn;

    IO::GSOutStreamPtr _standardOut;

    IO::GSOutStreamPtr _standardErr;

    IO::GSOutStreamPtr _standardLog;
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
