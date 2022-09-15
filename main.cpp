#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

//Void Test() {
//    auto COut = IO::GS_OutConsoleStream::CreateCOut();
//
//    auto SM = IO::GS_SourceManager::Create();
//
//    auto sourceHash = SM->AddSource(IO::GS_Source::CreateString("func main() {\n\tsay_hello()\n}"));
//
//    IO::GS_TextMessage::Create("Update GSLanguageCompiler to new 1.1 version!",
//                               IO::MessageLevel::Note)
//                               ->Write(COut);
//
//    IO::GS_LocatedTextMessage::Create("Can`t find function 'say_hello'!",
//                                      IO::MessageLevel::Error,
//                                      IO::GS_SourceLocation::Create(sourceHash, 19, 27))
//                                      ->Write(COut);
//}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    auto globalContextInitializingResult = Driver::GS_GlobalContext::Initialize();

    if (!globalContextInitializingResult) {
        return 1;
    }

    auto compilingResult = Driver::GS_Compiler::Start(argc, argv);

    auto programResult = StaticCast<I32>(compilingResult);

    return programResult;
}
