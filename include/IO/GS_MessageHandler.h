#ifndef GSLANGUAGE_GS_MESSAGEHANDLER_H
#define GSLANGUAGE_GS_MESSAGEHANDLER_H

#include <vector>

#include <IO/GS_Stream.h>

namespace GSLanguageCompiler::IO {

    // TODO update

    class SourceRange {
    public:

        SourceRange(UString sourceName, U64 startLine, U64 startColumn, U64 endLine, U64 endColumn)
                : _sourceName(std::move(sourceName)),
                  _startLine(startLine),
                  _startColumn(startColumn),
                  _endLine(endLine),
                  _endColumn(endColumn) {}

    public:

        static SourceRange Create(UString sourceName, U64 startLine, U64 startColumn, U64 endLine, U64 endColumn) {
            return SourceRange(std::move(sourceName), startLine, startColumn, endLine, endColumn);
        }

        static SourceRange Create(UString sourceName, U64 line, U64 startColumn, U64 endColumn) {
            return SourceRange::Create(std::move(sourceName), line, startColumn, line, endColumn);
        }

        static SourceRange Create(UString sourceName, U64 startLine, U64 endLine) {
            return SourceRange::Create(std::move(sourceName), startLine, 0, endLine, 0);
        }

        static SourceRange Create() {
            return SourceRange::Create("<unknown>"_us, 0, 0, 0, 0);
        }

    public:

        UString GetSourceName() const {
            return _sourceName;
        }

        U64 GetStartLine() const {
            return _startLine;
        }

        U64 GetStartColumn() const {
            return _startColumn;
        }

        U64 GetEndLine() const {
            return _endLine;
        }

        U64 GetEndColumn() const {
            return _endColumn;
        }

    private:

        UString _sourceName;

        U64 _startLine;

        U64 _startColumn;

        U64 _endLine;

        U64 _endColumn;
    };

    /**
     * Message level
     */
    enum class MessageLevel {
        Note,
        Warning,
        Error,
        Fatal
    };

    /**
     * Class for handling and writing messages to output stream
     */
    class GS_MessageHandler {
    public:

        /**
         * Constructor for message handler
         * @param stream Output stream
         */
        explicit GS_MessageHandler(GSOutStreamPtr stream);

    public:

        /**
         * Creating message handler
         * @param stream Stream for writing messages
         * @return Message handler ptr
         */
        static std::shared_ptr<GS_MessageHandler> Create(GSOutStreamPtr stream);

        /**
         * Creating message handler with writing message to standard console error stream
         * @return Message handler ptr
         */
        static std::shared_ptr<GS_MessageHandler> Create();

    public:

        /*
         * Example:
         *
         * Print("Update GSLanguageCompiler to new 2.10.2 version.",
         *       MessageLevel::Note);
         *
         * Note: Update GSLanguageCompiler to new 2.10.2 version.
         */
        /**
         * Printing message
         * @param message Message
         * @param messageLevel Message level
         * @return
         */
        Void Print(UString message, MessageLevel messageLevel);

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
        /**
         * Printing message with text
         * @param message Message
         * @param messageLevel Message level
         * @param sourceRange Source range for underlining text
         * @param text Text for message (source code)
         * @return
         */
        Void Print(UString message, MessageLevel messageLevel, SourceRange sourceRange, UString text);

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
        /**
         * Printing message with some texts
         * @param message Message
         * @param messageLevel Message level
         * @param sourceRanges Source ranges for underlining texts (source codes)
         * @param texts Texts for message (source codes)
         * @return
         */
        Void Print(UString message, MessageLevel messageLevel, std::vector<SourceRange> sourceRanges, std::vector<UString> texts);

    private:

        /**
         * Begin printing line
         * @return
         */
        Void BeginPrintLine();

        /**
         * End printing line
         * @return
         */
        Void EndPrintLine();

    private:

        /**
         * Output stream for messages
         */
        GSOutStreamPtr _stream;
    };

    /**
     * Message handler ptr type
     */
    using GSMessageHandlerPtr = std::shared_ptr<GS_MessageHandler>;

}

#endif //GSLANGUAGE_GS_MESSAGEHANDLER_H
