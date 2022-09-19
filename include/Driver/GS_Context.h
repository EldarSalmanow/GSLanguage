#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <IO/IO.h>

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

namespace GSLanguageCompiler::Driver {

    // TODO
    class GS_Context {
    public:

        GS_Context(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                   IO::GSSourceManagerPtr       sourceManager,
                   IO::GSOutStreamPtr           outputStream,
                   AST::GSASTContextPtr         astContext);

//        GS_Context(IO::GSInStreamPtr    standardIn,
//                   IO::GSOutStreamPtr   standardOut,
//                   IO::GSOutStreamPtr   standardErr,
//                   IO::GSOutStreamPtr   standardLog,
//                   IO::GSSourcePtrArray inputSources,
//                   IO::GSOutStreamPtr   outputStream,
//                   AST::GSASTContextPtr astContext);

    public:

        static std::shared_ptr<GS_Context> Create(IO::GSStdIOStreamsManagerPtr stdIOStreamsManager,
                                                  IO::GSSourceManagerPtr       sourceManager,
                                                  IO::GSOutStreamPtr           outputStream,
                                                  AST::GSASTContextPtr         astContext);

        static std::shared_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSOutStreamPtr     outputStream,
                                                  AST::GSASTContextPtr   astContext);

        static std::shared_ptr<GS_Context> Create(IO::GSSourceManagerPtr sourceManager,
                                                  IO::GSOutStreamPtr     outputStream);

//        static std::shared_ptr<GS_Context> Create(IO::GSInStreamPtr    standardIn,
//                                                  IO::GSOutStreamPtr   standardOut,
//                                                  IO::GSOutStreamPtr   standardErr,
//                                                  IO::GSOutStreamPtr   standardLog,
//                                                  IO::GSSourcePtrArray inputSources,
//                                                  IO::GSOutStreamPtr   outputStream,
//                                                  AST::GSASTContextPtr astContext);
//
//        static std::shared_ptr<GS_Context> Create(IO::GSSourcePtrArray inputSources,
//                                                  IO::GSOutStreamPtr   outputStream,
//                                                  AST::GSASTContextPtr astContext);
//
//        static std::shared_ptr<GS_Context> Create(IO::GSSourcePtrArray inputSources,
//                                                  IO::GSOutStreamPtr   outputStream);

        static std::shared_ptr<GS_Context> Create();

    public:

        static std::shared_ptr<GS_Context> Create(GS_Arguments arguments);

    public:

        IO::GSInStreamPtr GetStdInStream();

        IO::GSOutStreamPtr GetStdOutStream();

        IO::GSOutStreamPtr GetStdErrStream();

        IO::GSOutStreamPtr GetStdLogStream();

//        Void In(LRef<UString> string);
//
//        Void Out(ConstLRef<UString> string);
//
//        Void Err(ConstLRef<UString> string);
//
//        Void Log(ConstLRef<UString> string);

    public:

        U64 AddInputSource(IO::GSSourcePtr inputSource);

        IO::GSSourcePtr GetInputSource(U64 inputSourceHash) const;

        IO::GSSourcePtr GetInputSource(IO::GS_SourceName inputSourceName) const;

    public:

        // TODO

        /*
         * Example:
         *
         * Write("Update GSLanguageCompiler to new 2.10.2 version.",
         *       MessageLevel::Note);
         *
         * Note: Update GSLanguageCompiler to new 2.10.2 version.
         */
//        Void Message(UString message, IO::MessageLevel messageLevel) const;

        /*
         * Example:
         *
         * Write("Unknown type 'I31'!",
         *       MessageLevel::Error,
         *       SourceRange::Create("main.gs", 1, 8, 10),
         *       "var a: I31 = 10");
         *
         * main.gs 1: >> var a: I31 = 10
         *                      ^^^
         * Error: Unknown type 'I31'!
         */
//        Void Message(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation sourceLocation, UString text) const;

        /*
         * Example:
         *
         * Write("Found 2 'say_hello' function for calling.",
         *       MessageLevel::Note,
         *       { SourceRange::Create("main.gs", 5, 1, 33), SourceRange::Create("main.gs", 8, 1, 41) },
         *       { "func say_hello(String name): Void", "func say_hello(String name, U8 age): Void" });
         *
         * main.gs 5: >> func say_hello(String name): Void
         *               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         * main.gs 8: >> func say_hello(String name, U8 age): Void
         *               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         * Note: Found 2 'say_hello' function for calling.
         */
//        Void Message(UString message, IO::MessageLevel messageLevel, std::vector<IO::GS_SourceLocation> sourceLocations, std::vector<UString> texts) const;

    public:

        IO::GSSourcePtrArray GetInputSources() const;

        IO::GSOutStreamPtr GetOutputStream() const;

        AST::GSASTContextPtr GetASTContext() const;

    private:

//        IO::GSInStreamPtr    _standardIn;
//
//        IO::GSOutStreamPtr   _standardOut;
//
//        IO::GSOutStreamPtr   _standardErr;
//
//        IO::GSOutStreamPtr   _standardLog;
//
//        IO::GSSourcePtrArray _inputSources;

        IO::GSStdIOStreamsManagerPtr _stdIOStreamsManager;

        IO::GSSourceManagerPtr _sourceManager;

        IO::GSOutStreamPtr   _outputStream;

        AST::GSASTContextPtr _astContext;
    };

    using GSContextPtr = std::shared_ptr<GS_Context>;

}

#endif //GSLANGUAGE_GS_CONTEXT_H
