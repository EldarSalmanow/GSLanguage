#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * High level entry point for GSLanguageCompiler
 * @param argc Arguments counter
 * @param argv Arguments values
 * @return Compiler result
 */
Result GSMain(I32 argc, Ptr<Ptr<C>> argv) {
    auto globalContextInitializingResult = Driver::GlobalContext().Initialize();

    if (globalContextInitializingResult != Result::Ok) {
        return Result::Err;
    }

    auto compilingResult = Driver::GS_Compiler::Start(argc, argv);

    auto result = Driver::ToResult(compilingResult);

    return result;
}

/**
 * Low level entry point for GSLanguageCompiler
 * @param argc Arguments counter
 * @param argv Arguments values
 * @return Exit code
 */
I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    auto compilerResult = GSMain(argc, argv);

    auto exitCode = ToExitCode(compilerResult);

    return exitCode;
}
