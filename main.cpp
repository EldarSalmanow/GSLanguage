#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

I32 main() {
    Driver::GS_TranslationUnit unit(U"../test.gs");

    return unit.compile();
}
