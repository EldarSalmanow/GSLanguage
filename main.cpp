#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

#include <IO/IO.h>
#include <AST/AST.h>

namespace GSLanguageCompiler::IO {

    class GS_IOContext {
    public:

        GS_IOContext(GSInStreamPtr standardIn,
                     GSOutStreamPtr standardOut,
                     GSOutStreamPtr standardErr,
                     GSOutStreamPtr standardLog,
                     std::vector<GSInStreamPtr> inputSources,
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
                                                    std::vector<GSInStreamPtr> inputSources,
                                                    GSOutStreamPtr outputSource) {
            return std::make_shared<GS_IOContext>(std::move(standardIn),
                                                  std::move(standardOut),
                                                  std::move(standardErr),
                                                  std::move(standardLog),
                                                  std::move(inputSources),
                                                  std::move(outputSource));
        }

        static std::shared_ptr<GS_IOContext> Create(std::vector<GSInStreamPtr> inputSources, GSOutStreamPtr outputSource) {
            return GS_IOContext::Create(GS_InConsoleStream::CreateCIn(),
                                        GS_OutConsoleStream::CreateCOut(),
                                        GS_OutConsoleStream::CreateCErr(),
                                        GS_OutConsoleStream::CreateCLog(),
                                        std::move(inputSources),
                                        std::move(outputSource));
        }

        static std::shared_ptr<GS_IOContext> Create() {
            return GS_IOContext::Create(std::vector<GSInStreamPtr>(), GSOutStreamPtr());
        }

    public:

        Void AddInputSource(GSInStreamPtr inputSource) {
            _inputSources.emplace_back(std::move(inputSource));
        }

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

        std::vector<GSInStreamPtr> GetInputSources() const {
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

        std::vector<GSInStreamPtr> _inputSources;

        GSOutStreamPtr _outputSource;
    };

    using GSIOContextPtr = std::shared_ptr<GS_IOContext>;

}

class GS_CompilingContext {
public:

    GS_CompilingContext(IO::GSIOContextPtr ioContext, AST::GSASTContextPtr astContext)
            : _ioContext(std::move(ioContext)), _astContext(std::move(astContext)) {}

public:

    static std::shared_ptr<GS_CompilingContext> Create(IO::GSIOContextPtr ioContext, AST::GSASTContextPtr astContext) {
        return std::make_shared<GS_CompilingContext>(std::move(ioContext), std::move(astContext));
    }

public:

    IO::GSIOContextPtr GetIoContext() const {
        return _ioContext;
    }

    AST::GSASTContextPtr GetAstContext() const {
        return _astContext;
    }

private:

    IO::GSIOContextPtr _ioContext;

    AST::GSASTContextPtr _astContext;
};

using GSCompilingContextPtr = std::shared_ptr<GS_CompilingContext>;

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

enum class SourceNameType {
    File,
    String
};

class SourceName {
public:

    SourceName(UString name, SourceNameType type)
            : _name(std::move(name)), _type(type), _hash(0) {
        std::hash<std::string> hasher;

        _hash = hasher(_name.AsUTF8());
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

        auto name = UString(std::string("<string>") + std::to_string(id));

        ++id;

        return SourceName::Create(name, SourceNameType::String);
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
        std::hash<std::string> hasher;

        _hash = hasher(_source.AsUTF8());

        _hash ^= _name.GetHash();
    }

public:

    static std::shared_ptr<Source> Create(UString source, SourceName name) {
        return std::make_shared<Source>(std::move(source), std::move(name));
    }

    static std::shared_ptr<Source> CreateFile(SourceName name) {
        auto fileStream = IO::GS_InFileStream::CreateInFile(name.GetName());

        auto reader = IO::GS_Reader::Create(fileStream);

        return Source::Create(reader.Read(), std::move(name));
    }

    static std::shared_ptr<Source> CreateString(UString source) {
        return Source::Create(std::move(source), SourceName::CreateString());
    }

public:

    UString GetCodeByLocation(SourceLocation location) {
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

void f() {
    std::vector<IO::GSInStreamPtr> InSources = {
            IO::GS_InFileStream::CreateInFile("main.gs"_us),
            IO::GS_InFileStream::CreateInFile("std.gs"_us)
    };

    IO::GSOutStreamPtr OutSource = IO::GS_OutFileStream::CreateOutFile("main.exe"_us);

    auto IOC = IO::GS_IOContext::Create(InSources, OutSource);

    auto ASTC = AST::GS_ASTContext::Create();

    auto CC = GS_CompilingContext::Create(IOC, ASTC);
}

/**
 *
 * CompilingContext -> IOContext, ASTContext
 *
 * IOContext -> StandardIn, StandardOut, StandardErr, StandardLog, Sources
 *
 * ASTContext -> ASTTypeContext
 *
 * ASTTypeContext -> VoidType, I32Type, StringType
 *
 */

/*
#include <IO/IO.h>

using namespace GSLanguageCompiler;

class SourceManager {
public:

    explicit SourceManager(std::vector<IO::GSStreamPtr> streams)
            : _streams(std::move(streams)),
              _consoleIn(IO::GS_InConsoleStream::CreateCIn()),
              _consoleOut(IO::GS_OutConsoleStream::CreateCOut()),
              _consoleErr(IO::GS_OutConsoleStream::CreateCErr()),
              _consoleLog(IO::GS_OutConsoleStream::CreateCLog()) {}

public:

    static std::shared_ptr<SourceManager> Create(std::vector<IO::GSStreamPtr> streams) {
        return std::make_shared<SourceManager>(std::move(streams));
    }

    static std::shared_ptr<SourceManager> Create() {
        return SourceManager::Create(std::vector<IO::GSStreamPtr>());
    }

public:

    IO::GSInStreamPtr CreateInFile(UString name) {
        auto file = IO::GS_InFileStream::CreateInFile(std::move(name));

        AddStream(file);

        return file;
    }

    IO::GSOutStreamPtr CreateOutFile(UString name) {
        auto file = IO::GS_OutFileStream::CreateOutFile(std::move(name));

        AddStream(file);

        return file;
    }

    Void AddStream(IO::GSStreamPtr stream) {
        _streams.emplace_back(std::move(stream));
    }

public:

    IO::GSInStreamPtr GetConsoleIn() const {
        return _consoleIn;
    }

    IO::GSOutStreamPtr GetConsoleOut() const {
        return _consoleOut;
    }

    IO::GSOutStreamPtr GetConsoleErr() const {
        return _consoleErr;
    }

    IO::GSOutStreamPtr GetConsoleLog() const {
        return _consoleLog;
    }

private:

    std::vector<IO::GSStreamPtr> _streams;

    IO::GSInStreamPtr _consoleIn;

    IO::GSOutStreamPtr _consoleOut;

    IO::GSOutStreamPtr _consoleErr;

    IO::GSOutStreamPtr _consoleLog;
};

int main(int argc, char *argv[]) {
    auto SM = SourceManager::Create();

    auto file = SM->CreateOutFile("GSLanguageCompilerLogs.txt");

    auto MH = IO::GS_MessageHandler::Create(file);

    MH->Print("Невозможно найти функцию 'say_hello' с нулевыми аргументами!",
              IO::MessageLevel::Error,
              IO::SourceRange::Create("main.gs", 1, 9, 19),
              "var a = say_hello()");

    MH->Print("Найдено 2 функции 'say_hello' для вызова.",
              IO::MessageLevel::Note,
              { IO::SourceRange::Create("main.gs", 5, 1, 33), IO::SourceRange::Create("main.gs", 8, 1, 41) },
              { "func say_hello(String name): Void", "func say_hello(String name, U8 age): Void" });

//    MH->Print("Can`t found 'say_hello' function with void arguments!",
//              IO::MessageLevel::Error,
//              IO::SourceRange::Create("main.gs", 1, 9, 19),
//              "var a = say_hello()");
//
//    MH->Print("Found 2 'say_hello' function for calling.",
//              IO::MessageLevel::Note,
//              { IO::SourceRange::Create("main.gs", 5, 1, 33), IO::SourceRange::Create("main.gs", 8, 1, 41) },
//              { "func say_hello(String name): Void", "func say_hello(String name, U8 age): Void" });

    return 0;
}
*/