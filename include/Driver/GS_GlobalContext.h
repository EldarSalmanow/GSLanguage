#ifndef GSLANGUAGE_GS_GLOBALCONTEXT_H
#define GSLANGUAGE_GS_GLOBALCONTEXT_H

#include <IO/GS_Stream.h>

// TODO move macros to GSCrossPlatform library

#define GS_ATTRIBUTE(name) [[name]]

#define GS_NORETURN GS_ATTRIBUTE(noreturn)

namespace GSLanguageCompiler::Driver {

    /**
     * Signal handler function type
     */
    using SignalHandlerFunctionPtr = Void (*) (I32);

    /**
     * Default signal handler function
     * @param signal Signal
     * @return No return
     */
    GS_NORETURN Void DefaultSignalHandler(I32 signal);

    /**
     * Global compiler context for containing and manipulating information and operation system
     */
    class GS_GlobalContext {
    public:

        /*
         *
         * GS_GlobalContext PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Delete copy constructor for global context
         * @param context Context
         */
        GS_GlobalContext(ConstLRef<GS_GlobalContext> context) = delete;

    public:

        /*
         *
         * GS_GlobalContext PUBLIC STATIC METHODS
         *
         */

        /**
         * Getting global context instance
         * @return Global context instance
         */
        static LRef<GS_GlobalContext> GetInstance();

    public:

        /*
         *
         * GS_GlobalContext PUBLIC INITIALIZING METHODS
         *
         */

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

        /*
         *
         * GS_GlobalContext PUBLIC IO METHODS
         *
         */

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

        /*
         *
         * GS_GlobalContext PUBLIC EXIT METHODS
         *
         */

        /**
         * Exiting from program
         * @param exitCode Exit code
         * @return No return
         */
        GS_NORETURN Void Exit(I32 exitCode);

        /**
         * Exiting from program with exit code 1
         * @return No return
         */
        GS_NORETURN Void Exit();

    public:

        /*
         *
         * GS_GlobalContext PUBLIC OPERATORS
         *
         */

        /**
         * Delete assignment operator for global context
         * @param context Context
         * @return Context
         */
        LRef<GS_GlobalContext> operator=(ConstLRef<GS_GlobalContext> context) = delete;

    private:

        /*
         *
         * GS_GlobalContext PRIVATE CONSTRUCTORS
         *
         */

        /**
         * Default constructor for global context
         */
        GS_GlobalContext();

    private:

        /*
         *
         * GS_GlobalContext PRIVATE STATIC FIELDS
         *
         */

        /**
         * Global context instance
         */
        static GS_GlobalContext _context;

    private:

        /*
         *
         * GS_GlobalContext PRIVATE FIELDS
         *
         */

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
