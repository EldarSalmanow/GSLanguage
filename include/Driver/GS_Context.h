#ifndef GSLANGUAGE_GS_CONTEXT_H
#define GSLANGUAGE_GS_CONTEXT_H

#include <IO/IO.h>

#include <AST/AST.h>

#include <Driver/GS_Arguments.h>

namespace GSLanguageCompiler::Driver {

//    class StandardIOManager {
//    public:
//
//        StandardIOManager(IO::GSInStreamPtr  standardIn,
//                          IO::GSOutStreamPtr standardOut,
//                          IO::GSOutStreamPtr standardErr,
//                          IO::GSOutStreamPtr standardLog);
//
//    public:
//
//        static std::shared_ptr<StandardIOManager> Create(IO::GSInStreamPtr  standardIn,
//                                                         IO::GSOutStreamPtr standardOut,
//                                                         IO::GSOutStreamPtr standardErr,
//                                                         IO::GSOutStreamPtr standardLog);
//
//        static std::shared_ptr<StandardIOManager> Create();
//
//    public:
//
//        Void In(LRef<UString> string);
//
//        Void Out(ConstLRef<UString> string);
//
//        Void Err(ConstLRef<UString> string);
//
//        Void Log(ConstLRef<UString> string);
//
//    private:
//
//        IO::GSInStreamPtr  _standardIn;
//
//        IO::GSOutStreamPtr _standardOut;
//
//        IO::GSOutStreamPtr _standardErr;
//
//        IO::GSOutStreamPtr _standardLog;
//    };
//
//    using StandardIOManagerPtr = std::shared_ptr<StandardIOManager>;
//
//    class Message {
//    public:
//
//        virtual ~Message() = default;
//
//    public:
//
//        virtual Void Print(IO::GSOutStreamPtr outputStream) = 0;
//    };
//
//    using MessagePtr = std::shared_ptr<Message>;
//
//    class Note : public Message {
//    public:
//
//        explicit Note(UString note, IO::GS_SourceLocation sourceLocation)
//                : _note(std::move(note)) {}
//
//    public:
//
//    public:
//
//        Void Print(IO::GSOutStreamPtr outputStream) override {
//
//        }
//
//    private:
//
//        UString _note;
//    };
//
//    class Warning : public Message {
//    public:
//
//        explicit Warning(UString warning)
//                : _warning(std::move(warning)) {}
//
//    public:
//
//        Void Print(IO::GSOutStreamPtr outputStream) override {
//
//        }
//
//    private:
//
//        UString _warning;
//    };
//
//    class Error : public Message {
//    public:
//
//        explicit Error(UString error)
//                : _error(std::move(error)) {}
//
//    public:
//
//        Void Print(IO::GSOutStreamPtr outputStream) override {
//
//        }
//
//    private:
//
//        UString _error;
//    };
//
//    class Fatal : public Message {
//    public:
//
//        explicit Fatal(UString fatal)
//                : _fatal(std::move(fatal)) {}
//
//    public:
//
//        Void Print(IO::GSOutStreamPtr outputStream) override {
//
//        }
//
//    private:
//
//        UString _fatal;
//    };
//
//    inline LRef<IO::GSOutStreamPtr> operator<<(LRef<IO::GSOutStreamPtr> outputStream, MessagePtr message) {
//        message->Print(outputStream);
//
//        return outputStream;
//    }

    // TODO create class for message handling ( IO context ? )
    enum class MessageLevel {
        Note,
        Warning,
        Error,
        Fatal
    };

    // TODO
    class GS_Context {
    public:

        GS_Context(IO::GSInStreamPtr    standardIn,
                   IO::GSOutStreamPtr   standardOut,
                   IO::GSOutStreamPtr   standardErr,
                   IO::GSOutStreamPtr   standardLog,
                   IO::GSSourcePtrArray inputSources,
                   IO::GSOutStreamPtr   outputStream,
                   AST::GSASTContextPtr astContext);

    public:

        static std::shared_ptr<GS_Context> Create(IO::GSInStreamPtr    standardIn,
                                                  IO::GSOutStreamPtr   standardOut,
                                                  IO::GSOutStreamPtr   standardErr,
                                                  IO::GSOutStreamPtr   standardLog,
                                                  IO::GSSourcePtrArray inputSources,
                                                  IO::GSOutStreamPtr   outputStream,
                                                  AST::GSASTContextPtr astContext);

        static std::shared_ptr<GS_Context> Create(IO::GSSourcePtrArray inputSources,
                                                  IO::GSOutStreamPtr   outputStream,
                                                  AST::GSASTContextPtr astContext);

        static std::shared_ptr<GS_Context> Create(IO::GSSourcePtrArray inputSources,
                                                  IO::GSOutStreamPtr   outputStream);

        static std::shared_ptr<GS_Context> Create();

    public:

        static std::shared_ptr<GS_Context> Create(GS_Arguments arguments);

    public:

        Void In(LRef<UString> string);

        Void Out(ConstLRef<UString> string);

        Void Err(ConstLRef<UString> string);

        Void Log(ConstLRef<UString> string);

    public:

        Void AddInputSource(IO::GSSourcePtr inputSource);

        IO::GSSourcePtr GetInputSource(U64 inputSourceHash) const;

        IO::GSSourcePtr GetInputSource(IO::GS_SourceName inputSourceName) const;

    public:

        // TODO

        /*
         * Example:
         *
         * Print("Update GSLanguageCompiler to new 2.10.2 version.",
         *       MessageLevel::Note);
         *
         * Note: Update GSLanguageCompiler to new 2.10.2 version.
         */
        Void Message(UString message, MessageLevel messageLevel) const;

        /*
         * Example:
         *
         * Print("Unknown type 'I31'!",
         *       MessageLevel::Error,
         *       SourceRange::Create("main.gs", 1, 8, 10),
         *       "var a: I31 = 10");
         *
         * main.gs 1: >> var a: I31 = 10
         *                      ^^^
         * Error: Unknown type 'I31'!
         */
        Void Message(UString message, MessageLevel messageLevel, IO::GS_SourceLocation sourceLocation, UString text) const;

        /*
         * Example:
         *
         * Print("Found 2 'say_hello' function for calling.",
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
        Void Message(UString message, MessageLevel messageLevel, std::vector<IO::GS_SourceLocation> sourceLocations, std::vector<UString> texts) const;

    public:

        IO::GSSourcePtrArray GetInputSources() const;

        IO::GSOutStreamPtr GetOutputStream() const;

        AST::GSASTContextPtr GetASTContext() const;

    private:

        IO::GSInStreamPtr    _standardIn;

        IO::GSOutStreamPtr   _standardOut;

        IO::GSOutStreamPtr   _standardErr;

        IO::GSOutStreamPtr   _standardLog;

        IO::GSSourcePtrArray _inputSources;

        IO::GSOutStreamPtr   _outputStream;

        AST::GSASTContextPtr _astContext;
    };

    using GSContextPtr = std::shared_ptr<GS_Context>;

}

#endif //GSLANGUAGE_GS_CONTEXT_H
