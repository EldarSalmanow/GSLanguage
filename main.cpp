//#include <Driver/Driver.h>
//
//using namespace GSLanguageCompiler;
//
///**
// * Entry point for GSLanguageCompiler
// * @return Compiler result
// */
//I32 main(I32 argc, Ptr<Ptr<C>> argv) {
//    return Driver::GS_Compiler::Start(argc, argv);
//}

#include <rang.hpp>

#include <IO/IO.h>
#include <AST/AST.h>

using namespace GSLanguageCompiler;

class File {
public:

    UString Name;

    std::vector<UString> Code;
};

class SourceManager {
public:

    inline static std::vector<File> Files;
};

Void Print(UString message, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream, rang::style style, rang::fg color) {
    auto BeginPrintLine = [style] (LRef<IO::GSOutStreamPtr> stream) {
        stream->GetOutStream() << rang::style::reset << rang::fg::reset << style << "|> "_us;
    };

    auto EndPrintLine = [] (LRef<IO::GSOutStreamPtr> stream) {
        stream->GetOutStream() << rang::style::reset << rang::fg::reset << std::endl;
    };

    auto startSymbolLocation = tokenLocation.GetStartLocation();
    auto endSymbolLocation = tokenLocation.GetEndLocation();

    BeginPrintLine(stream);

    UString code;

    for (auto &file : SourceManager::Files) {
        if (file.Name == startSymbolLocation.GetSourceName()) {
            code = file.Code[startSymbolLocation.GetLine() - 1];

            break;
        }
    }

    stream->GetOutStream() << color << startSymbolLocation.GetSourceName() << " " << startSymbolLocation.GetLine() << ": >> " << code;

    EndPrintLine(stream);

    BeginPrintLine(stream);

    stream->GetOutStream() << color;

    auto aligning = startSymbolLocation.GetSourceName().Size() + std::to_string(startSymbolLocation.GetLine()).size() + 6;

    for (U64 i = 1; i < startSymbolLocation.GetColumn() + aligning; ++i) {
        stream->GetOutStream() << " ";
    }

    for (U64 i = startSymbolLocation.GetColumn() + aligning; i <= endSymbolLocation.GetColumn() + aligning; ++i) {
        stream->GetOutStream() << "^";
    }

    EndPrintLine(stream);

    BeginPrintLine(stream);

    stream->GetOutStream() << color << message;

    EndPrintLine(stream);

    BeginPrintLine(stream);

    EndPrintLine(stream);
}

Void Note(UString note, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream) {
    Print("Note: "_us + note, std::move(tokenLocation), std::move(stream), rang::style::bold, rang::fg::blue);
}

Void Warning(UString warning, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream) {
    Print("Warning: "_us + warning, std::move(tokenLocation), std::move(stream), rang::style::bold, rang::fg::yellow);
}

Void Error(UString error, Lexer::GS_TokenLocation tokenLocation, IO::GSOutStreamPtr stream) {
    Print("Error: "_us + error, std::move(tokenLocation), std::move(stream), rang::style::bold, rang::fg::red);
}

Void StdNote(UString note, Lexer::GS_TokenLocation tokenLocation) {
    Note(std::move(note), std::move(tokenLocation), IO::GS_OutConsoleStream::CreateCErr());
}

Void StdWarning(UString warning, Lexer::GS_TokenLocation tokenLocation) {
    Warning(std::move(warning), std::move(tokenLocation), IO::GS_OutConsoleStream::CreateCErr());
}

Void StdError(UString error, Lexer::GS_TokenLocation tokenLocation) {
    Error(std::move(error), std::move(tokenLocation), IO::GS_OutConsoleStream::CreateCErr());
}

inline Void ColoursAndStyles() {
    rang::style styles[] = {
            rang::style::bold,
            rang::style::dim,
            rang::style::italic,
            rang::style::underline,
            rang::style::blink,
            rang::style::rblink,
            rang::style::reversed,
            rang::style::conceal,
            rang::style::crossed
    };

    rang::fg fgs[] = {
            rang::fg::black,
            rang::fg::red,
            rang::fg::green,
            rang::fg::yellow,
            rang::fg::blue,
            rang::fg::magenta,
            rang::fg::cyan,
            rang::fg::gray
    };

    for (auto &style : styles) {
        for (auto &fg : fgs) {
            std::cout << rang::style::reset << rang::fg::reset << style << fg << "Hello!" << rang::style::reset << rang::fg::reset << std::endl;
        }
    }
}

Void test1() {
    auto variableUsingExpression = AST::GS_VariableUsingExpression::Create("num_",
                                                                           Lexer::GS_TokenLocation::Create(
                                                                                   IO::GS_SymbolLocation::Create("main.gs", 3, 7),
                                                                                   IO::GS_SymbolLocation::Create("main.gs", 3, 10)));

    SourceManager::Files.emplace_back(File { "main.gs", { "var num = 10", "", "num = num_ + 1" } } );

    StdError("Can`t found variable with name \'"_us + variableUsingExpression->GetName() + "\'!", variableUsingExpression->GetNameLocation());
}

int main(int argc, char *argv[]) {
//    SourceManager::Files.emplace_back(File { "main.gs", { "var a: I31 = 10", "printf(\"Hello, World!\")" } } );
//
//    auto Handler = IO::GS_ErrorHandler::Create();
//
//    StdError("Unknown type!"_us, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 1, 8), IO::GS_SymbolLocation::Create("main.gs", 1, 10)));
//    Handler.StdNote("I31 -> I32 ?"_us /*, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 1, 8), IO::GS_SymbolLocation::Create("main.gs", 1, 10))*/);
//    StdWarning("Using unstable 'printf' function!"_us, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 2, 1), IO::GS_SymbolLocation::Create("main.gs", 2, 6)));
//    Handler.StdNote("Use standard 'print' function! printf -> print"_us /*, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 2, 1), IO::GS_SymbolLocation::Create("main.gs", 2, 6))*/);

    test1();

    return 0;
}
