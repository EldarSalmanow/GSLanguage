#include <GSCrossPlatform/Defines.h>

#if defined(GS_OS_WINDOWS)

    /**
     * Can`t include in rang.hpp io.h standard header because preprocessor include IO.h project header.
     * Including low-level I/O functions manually from corecrt_io.h
     */
    #include <corecrt_io.h>

#endif

#include <rang.hpp>

#include <GS_MessageHandler.h>

namespace GSLanguageCompiler::IO {

    inline rang::fg MessageLevelToFGColor(MessageLevel messageLevel) {
        switch (messageLevel) {
            case MessageLevel::Note:
                return rang::fg::blue;
            case MessageLevel::Warning:
                return rang::fg::yellow;
            case MessageLevel::Error:
                return rang::fg::red;
            case MessageLevel::Fatal:
                return rang::fg::gray;
        }

        return rang::fg::reset;
    }

    GS_MessageHandler::GS_MessageHandler(GSOutStreamPtr stream)
            : _stream(std::move(stream)) {}

    std::shared_ptr<GS_MessageHandler> GS_MessageHandler::Create(GSOutStreamPtr stream) {
        return std::make_shared<GS_MessageHandler>(std::move(stream));
    }

    std::shared_ptr<GS_MessageHandler> GS_MessageHandler::Create() {
        return GS_MessageHandler::Create(GS_OutConsoleStream::CreateCErr());
    }

    Void GS_MessageHandler::Print(UString message, MessageLevel messageLevel) {
        auto color = MessageLevelToFGColor(messageLevel);

        UString messagePrefix;

        switch (messageLevel) {
            case MessageLevel::Note:
                messagePrefix = "Note: ";

                break;
            case MessageLevel::Warning:
                messagePrefix = "Warning: ";

                break;
            case MessageLevel::Error:
                messagePrefix = "Error: ";

                break;
            case MessageLevel::Fatal:
                messagePrefix = "Fatal: ";

                break;
        }

        BeginPrintLine();

        _stream->GetOutStream() << color << messagePrefix + message;

        EndPrintLine();

        BeginPrintLine();

        EndPrintLine();
    }

    Void GS_MessageHandler::Print(UString message, MessageLevel messageLevel, SourceRange sourceRange, UString text) {
        auto color = MessageLevelToFGColor(messageLevel);

        BeginPrintLine();

        _stream->GetOutStream() << color << sourceRange.GetSourceName() << " " << sourceRange.GetStartLine() << ": >> " << text;

        EndPrintLine();

        BeginPrintLine();

        _stream->GetOutStream() << color;

        auto aligning = sourceRange.GetSourceName().Size() + std::to_string(sourceRange.GetStartLine()).size() + 6;

        for (U64 i = 1; i < sourceRange.GetStartColumn() + aligning; ++i) {
            _stream->GetOutStream() << " ";
        }

        for (U64 i = sourceRange.GetStartColumn() + aligning; i <= sourceRange.GetEndColumn() + aligning; ++i) {
            _stream->GetOutStream() << "^";
        }

        EndPrintLine();

        UString messagePrefix;

        switch (messageLevel) {
            case MessageLevel::Note:
                messagePrefix = "Note: ";

                break;
            case MessageLevel::Warning:
                messagePrefix = "Warning: ";

                break;
            case MessageLevel::Error:
                messagePrefix = "Error: ";

                break;
            case MessageLevel::Fatal:
                messagePrefix = "Fatal: ";

                break;
        }

        BeginPrintLine();

        _stream->GetOutStream() << color << messagePrefix + message;

        EndPrintLine();

        BeginPrintLine();

        EndPrintLine();
    }

    Void GS_MessageHandler::Print(UString message, MessageLevel messageLevel, std::vector<SourceRange> sourceRanges, std::vector<UString> texts) {
        if (sourceRanges.size() != texts.size()) {
            Print("MessageHandler::Print(UString, MessageLevel, std::vector<SourceRange>, std::vector<UString>): \nCan`t call GSLanguageCompiler internal function with different size of source ranges and texts!",
                  MessageLevel::Fatal);

            return;
        }

        auto color = MessageLevelToFGColor(messageLevel);

        for (U64 index = 0; index < sourceRanges.size(); ++index) {
            auto sourceRange = sourceRanges[index];
            auto text = texts[index];

            BeginPrintLine();

            _stream->GetOutStream() << color << sourceRange.GetSourceName() << " " << sourceRange.GetStartLine() << ": >> " << text;

            EndPrintLine();

            BeginPrintLine();

            _stream->GetOutStream() << color;

            auto aligning = sourceRange.GetSourceName().Size() + std::to_string(sourceRange.GetStartLine()).size() + 6;

            for (U64 i = 1; i < sourceRange.GetStartColumn() + aligning; ++i) {
                _stream->GetOutStream() << " ";
            }

            for (U64 i = sourceRange.GetStartColumn() + aligning; i <= sourceRange.GetEndColumn() + aligning; ++i) {
                _stream->GetOutStream() << "^";
            }

            EndPrintLine();
        }

        Print(message, messageLevel);
    }

    Void GS_MessageHandler::BeginPrintLine() {
        _stream->GetOutStream() << rang::style::reset << rang::fg::reset << rang::style::bold << "|> "_us;
    }

    Void GS_MessageHandler::EndPrintLine() {
        _stream->GetOutStream() << rang::style::reset << rang::fg::reset << std::endl;
    }

}
