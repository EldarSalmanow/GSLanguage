#ifndef GSLANGUAGE_GS_GLOBALCONTEXT_H
#define GSLANGUAGE_GS_GLOBALCONTEXT_H

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::Driver {

    /**
     * Signal handler function type
     */
    using SignalHandlerFunctionPtr = Void (*) (I32);

    /**
     * Default signal handler function
     * @param signal Signal
     * @return
     */
    Void DefaultSignalHandler(I32 signal);

    /**
     * Global compiler context for containing and manipulating information and operation system
     */
    class GS_GlobalContext {
    public:

        /**
         * Delete copy constructor for global context
         * @param context Context
         */
        GS_GlobalContext(ConstLRef<GS_GlobalContext> context) = delete;

    public:

        /**
         * Getting global context instance
         * @return Global context instance
         */
        static LRef<GS_GlobalContext> GetInstance();

    public:

        /**
         * Initializing global IO streams
         * @param stdIOStreamsManager Standard IO streams manager
         * @return Initialization result
         */
        Result InitializeIO(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager);

        /**
         * Initializing global signal handlers
         * @param signalHandlerFunction Signal handler function
         * @return Initialization result
         */
        Result InitializeSignals(SignalHandlerFunctionPtr signalHandlerFunction);

        /**
         * Initializing global context
         * @param stdIOStreamsManager Standard IO streams manager
         * @param signalHandlerFunction Signal handler function
         * @return Initialization result
         */
        Result Initialize(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                          SignalHandlerFunctionPtr signalHandlerFunction);

        /**
         * Default initializing global context
         * @return Initialization result
         */
        Result Initialize();

    public:

        /**
         * Getting standard input stream from standard IO streams manager
         * @return Standard input stream
         */
        LRef<std::istream> In();

        /**
         * Getting standard output stream from standard IO streams manager
         * @return Standard output stream
         */
        LRef<std::ostream> Out();

        /**
         * Getting standard error stream from standard IO streams manager
         * @return Standard error stream
         */
        LRef<std::ostream> Err();

        /**
         * Getting standard logging stream from standard IO streams manager
         * @return Standard logging stream
         */
        LRef<std::ostream> Log();

    public:

        // TODO add GS_NORETURN macro

        /**
         * Exiting from program
         * @param exitCode Exit code
         * @return
         */
        [[noreturn]] Void Exit(I32 exitCode);

        [[noreturn]] Void Exit();

        // TODO comment

        [[noreturn]] Void ErrAndExit(ConstLRef<UString> string,
                                     I32 exitCode);

        [[noreturn]] Void ErrAndExit(ConstLRef<UString> string);

    public:

        /**
         * Delete assignment operator for global context
         * @param context Context
         * @return Context
         */
        LRef<GS_GlobalContext> operator=(ConstLRef<GS_GlobalContext> context) = delete;

    private:

        /**
         * Default constructor for global context
         */
        GS_GlobalContext();

    private:

        /**
         * Global context instance
         */
        static GS_GlobalContext _context;

    private:

        /**
         * Standard IO streams manager
         */
        IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager;
    };

    /**
     * Getting global context instance
     * @return Global context instance
     */
    LRef<GS_GlobalContext> GlobalContext();

}

#endif //GSLANGUAGE_GS_GLOBALCONTEXT_H
