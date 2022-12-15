#ifndef GSLANGUAGE_GS_GLOBALCONTEXT_H
#define GSLANGUAGE_GS_GLOBALCONTEXT_H

#include <GSCrossPlatform/UException.h>

#include <IO/IO.h>

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
         * Read string from standard input stream from standard IO streams manager
         * @param string String for reading
         * @return
         */
        Void In(LRef<UString> string);

        /**
         * Write string to standard output stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        Void Out(ConstLRef<UString> string);

        /**
         * Write string to standard error stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        Void Err(ConstLRef<UString> string);

        /**
         * Write string to standard logging stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        Void Log(ConstLRef<UString> string);

    public:

        // TODO add GS_NORETURN macro

        /**
         * Exiting from program
         * @param exitCode Exit code
         * @return
         */
        [[noreturn]] Void Exit(I32 exitCode);

        // TODO comment

        [[noreturn]] Void ErrAndExit(ConstLRef<UString> string,
                                     I32 exitCode);

        [[noreturn]] Void ErrAndExit(ConstLRef<UString> string);

    public:

        /**
         * Getter for standard input stream from standard IO streams manager
         * @return Standard input stream
         */
        IO::GSInStreamPtr GetStdInStream() const;

        /**
         * Getter for standard output stream from standard IO streams manager
         * @return Standard output stream
         */
        IO::GSOutStreamPtr GetStdOutStream() const;

        /**
         * Getter for standard error stream from standard IO streams manager
         * @return Standard error stream
         */
        IO::GSOutStreamPtr GetStdErrStream() const;

        /**
         * Getter for standard logging stream from standard IO streams manager
         * @return Standard logging stream
         */
        IO::GSOutStreamPtr GetStdLogStream() const;

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
