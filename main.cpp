#include <Starter/GS_Starter.h>

/**
 * Main function in GSLanguageCompiler
 * @param argc Arguments count
 * @param argv Arguments array
 * @return Status number for operation system
 */
GSInt main(GSInt argc, GSChar *argv[]) {
    return Starter::GS_Starter::start(argc, argv);
}
