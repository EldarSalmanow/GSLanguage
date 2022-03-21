#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Function for startup GSLanguageCompiler
 * @param argc Arguments counter
 * @param argv Arguments values
 * @return Compiler result. 0 - successful, any results - error
 */
I32 RunCompiler(I32 argc, Ptr<Ptr<C8>> argv) {
    auto manager = Driver::GS_TranslationUnitsManager::Create();

    auto unit = Driver::GS_TranslationUnit::Create(U"../test.gs"_us, U"test.o"_us); // TODO add arguments parser

    manager->AddUnit(unit);

    return manager->CompileUnits();
}

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return RunCompiler(argc, argv);
}
