#include "include/Starter/GS_Starter.h"

std::function<int(int, char**)> startFunction = Starter::GS_Starter::startCompiler;

Debug::GS_Timer<int(int, char*[])> timer(startFunction);

/**
 * Main function in GSLanguageCompiler
 * @return Status number for operation system
 */
int main(int argc, char *argv[]) {
    return timer.runtime("Total time", argc, argv);
}
