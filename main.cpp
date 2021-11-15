#include <Driver/GS_TranslationUnitsManager.h>

using namespace GSLanguageCompiler;

I32 main() {
    Driver::GS_TranslationUnit unit("../test.gs");

    return unit.compile();
}
