#ifndef GSLANGUAGE_GS_GLOBALCONTEXT_H
#define GSLANGUAGE_GS_GLOBALCONTEXT_H

#include <IO/GS_Stream.h>

// TODO move macros to GSCrossPlatform library

#define GS_ATTRIBUTE(name) [[name]]

#define GS_NORETURN GS_ATTRIBUTE(noreturn)

namespace GSLanguageCompiler::Driver {

    /**
     * Signal handler function ptr type
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
         * GS_GlobalContext PUBLIC METHODS
         *
         */

        /**
         * Initializing global IO streams
         * @param stdIOStreamManager Standard IO stream manager
         * @return Initialization result
         */
        Result InitializeIO(IO::GSStdIOStreamManagerPtr stdIOStreamManager);

        /**
         * Initializing global signal handlers
         * @param signalHandlerFunction Signal handler function
         * @return Initialization result
         */
        Result InitializeSignals(SignalHandlerFunctionPtr signalHandlerFunction);

        /**
         * Initializing global context
         * @param stdIOStreamManager Standard IO stream manager
         * @param signalHandlerFunction Signal handler function
         * @return Initialization result
         */
        Result Initialize(IO::GSStdIOStreamManagerPtr stdIOStreamManager,
                          SignalHandlerFunctionPtr signalHandlerFunction);

        /**
         * Default initializing global context
         * @return Initialization result
         */
        Result Initialize();

        /**
         * Getting standard input stream from standard IO stream manager
         * @return Standard input stream
         */
        LRef<std::istream> In();

        /**
         * Getting standard output stream from standard IO stream manager
         * @return Standard output stream
         */
        LRef<std::ostream> Out();

        /**
         * Getting standard error stream from standard IO stream manager
         * @return Standard error stream
         */
        LRef<std::ostream> Err();

        /**
         * Getting standard logger stream from standard IO stream manager
         * @return Standard logger stream
         */
        LRef<std::ostream> Log();

        /**
         * Exiting from program
         * @param exitCode Exit code
         * @return No return
         * @todo Add cleanup
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
         * Standard IO stream manager
         */
        IO::GSStdIOStreamManagerPtr _stdIOStreamManager;
    };

    /**
     * Getting global context instance
     * @return Global context instance
     */
    LRef<GS_GlobalContext> GlobalContext();

}

#endif //GSLANGUAGE_GS_GLOBALCONTEXT_H
