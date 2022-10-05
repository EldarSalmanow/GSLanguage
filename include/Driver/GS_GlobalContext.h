#ifndef GSLANGUAGE_GS_GLOBALCONTEXT_H
#define GSLANGUAGE_GS_GLOBALCONTEXT_H

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
         * Delete constructor for global context. Only static class
         */
        GS_GlobalContext() = delete;

    public:

        /**
         * Initializing global IO streams
         * @param stdIOStreamsManager Standard IO streams manager
         * @return Initialization result
         */
        static I32 InitializeIO(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager);

        /**
         * Initializing global signal handlers
         * @param signalHandlerFunction Signal handler function
         * @return Initialization result
         */
        static I32 InitializeSignals(SignalHandlerFunctionPtr signalHandlerFunction);

        /**
         * Initializing global context
         * @param stdIOStreamsManager Standard IO streams manager
         * @param signalHandlerFunction Signal handler function
         * @return Initialization result
         */
        static I32 Initialize(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager, SignalHandlerFunctionPtr signalHandlerFunction);

        /**
         * Default initializing global context
         * @return Initialization result
         */
        static I32 Initialize();

    public:

        /**
         * Read string from standard input stream from standard IO streams manager
         * @param string String for reading
         * @return
         */
        static Void In(LRef<UString> string);

        /**
         * Write string to standard output stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        static Void Out(ConstLRef<UString> string);

        /**
         * Write string to standard error stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        static Void Err(ConstLRef<UString> string);

        /**
         * Write string to standard logging stream from standard IO streams manager
         * @param string String for writing
         * @return
         */
        static Void Log(ConstLRef<UString> string);

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

    private:

        /**
         * Standard IO streams manager
         */
        inline static IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager = nullptr;
    };

}

#endif //GSLANGUAGE_GS_GLOBALCONTEXT_H
