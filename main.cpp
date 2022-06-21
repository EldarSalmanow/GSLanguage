#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

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