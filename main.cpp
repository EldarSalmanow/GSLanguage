#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
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
