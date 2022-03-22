#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
int main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}
