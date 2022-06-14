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

#include <IO/IO.h>
#include <AST/AST.h>

using namespace GSLanguageCompiler;

//Void test1() {
//    auto variableUsingExpression = AST::GS_VariableUsingExpression::Create("num_",
//                                                                           Lexer::GS_TokenLocation::Create(
//                                                                                   IO::GS_SymbolLocation::Create("main.gs", 3, 7),
//                                                                                   IO::GS_SymbolLocation::Create("main.gs", 3, 10)));
//
//    SourceManager::Files.emplace_back(File { "main.gs", { "var num = 10", "", "num = num_ + 1" } } );
//
//    StdError("Can`t found variable with name \'"_us + variableUsingExpression->GetName() + "\'!", variableUsingExpression->GetNameLocation());
//}

int main(int argc, char *argv[]) {
//    SourceManager::Files.emplace_back(File { "main.gs", { "var a: I31 = 10", "printf(\"Hello, World!\")" } } );
//
//    auto Handler = IO::GS_MessageHandler::Create();
//
//    StdError("Unknown type!"_us, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 1, 8), IO::GS_SymbolLocation::Create("main.gs", 1, 10)));
//    Handler.StdNote("I31 -> I32 ?"_us /*, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 1, 8), IO::GS_SymbolLocation::Create("main.gs", 1, 10))*/);
//    StdWarning("Using unstable 'printf' function!"_us, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 2, 1), IO::GS_SymbolLocation::Create("main.gs", 2, 6)));
//    Handler.StdNote("Use standard 'print' function! printf -> print"_us /*, Lexer::GS_TokenLocation::Create(IO::GS_SymbolLocation::Create("main.gs", 2, 1), IO::GS_SymbolLocation::Create("main.gs", 2, 6))*/);

    auto SM = IO::GS_SourceManager::Create();

    auto EH = IO::GS_MessageHandler::Create(SM);

    auto File = IO::GS_File::Create(IO::GS_InFileStream::CreateInFile("main.gs"));

    File->SetCode({ "var a: I31 = printf(\"Hello, World!\")" });

    SM->AddFile(File);

    EH->StdNote("Update GSLanguageCompiler to new 2.10.2 version.");

    EH->StdError("Unknown type 'I31'!", Lexer::GS_TokenLocation::Create(
            IO::GS_SymbolLocation::Create("main.gs", 1, 8),
            IO::GS_SymbolLocation::Create("main.gs", 1, 10)));

    EH->StdNote("'I31' -> 'I32' ?", Lexer::GS_TokenLocation::Create(
            IO::GS_SymbolLocation::Create("main.gs", 1, 8),
            IO::GS_SymbolLocation::Create("main.gs", 1, 10)));

    EH->StdError("'printf' function not return value!", Lexer::GS_TokenLocation::Create(
            IO::GS_SymbolLocation::Create("main.gs", 1, 14),
            IO::GS_SymbolLocation::Create("main.gs", 1, 19)));

    EH->StdWarning("Using unstable 'printf' function!", Lexer::GS_TokenLocation::Create(
            IO::GS_SymbolLocation::Create("main.gs", 1, 14),
            IO::GS_SymbolLocation::Create("main.gs", 1, 19)));

    EH->StdNote("Use stable 'print' function. "
                "'printf' -> 'print'", Lexer::GS_TokenLocation::Create(
            IO::GS_SymbolLocation::Create("main.gs", 1, 14),
            IO::GS_SymbolLocation::Create("main.gs", 1, 19)));

    return 0;
}

class SourceRange {
public:

    SourceRange(UString sourceName, U64 startLine, U64 startColumn, U64 endLine, U64 endColumn);

private:

    static SourceRange Create(UString sourceName, U64 startLine, U64 startColumn, U64 endLine, U64 endColumn);

    static SourceRange Create(UString sourceName, U64 line, U64 startColumn, U64 endColumn);

    static SourceRange Create(UString sourceName, U64 startLine, U64 endLine);

    static SourceRange Create();

public:

    UString GetSourceName() const;

    U64 GetStartLine() const;

    U64 GetStartColumn() const;

    U64 GetEndLine() const;

    U64 GetEndColumn() const;

private:

    UString _sourceName;

    U64 _startLine;

    U64 _startColumn;

    U64 _endLine;

    U64 _endColumn;
};

enum class MessageLevel {
    Note,
    Warning,
    Error
};

/*
 * Note: Update GSLanguageCompiler to new 2.10.2 version
 */
Void Print(UString message, MessageLevel messageLevel);

/*
 * main.gs 1: var a = say_hello()
 *                    ^^^^^^^^^^^
 * Error: Can`t found 'say_hello' function with void arguments!
 *
 * main.gs 5: >> func say_hello(String name): Void
 *               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * main.gs 8: >> func say_hello(String name, U8 age): Void
 *               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * Note: Found 2 'say_hello' function for calling
 */
Void Print(UString message, MessageLevel messageLevel, std::vector<SourceRange> sourceRanges, std::vector<UString> texts);

/*
 * main.gs 1: >> var a: I31 = 10
 *                      ^^^
 * Error: Unknown type 'I31'!
 */
Void Print(UString message, MessageLevel messageLevel, SourceRange sourceRange, UString text);
