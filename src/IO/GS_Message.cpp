#include <GSCrossPlatform/Defines.h>

#if defined(GS_OS_WINDOWS)

    /**
     * Can`t include in rang.hpp io.h standard header because preprocessor include IO.h project header.
     * Including low-level I/O functions manually from corecrt_io.h
     */
    #include <corecrt_io.h>

#endif

#include <rang.hpp>

#include <GS_Message.h>

namespace GSLanguageCompiler::IO {

    GS_Message::~GS_Message() = default;

    GS_TextMessage::GS_TextMessage(UString text, IO::MessageLevel level)
            : _text(std::move(text)), _level(level) {}

    std::shared_ptr<GS_TextMessage> GS_TextMessage::Create(UString text, IO::MessageLevel level) {
        return std::make_shared<GS_TextMessage>(std::move(text), level);
    }

    UString GS_TextMessage::GetText() const {
        return _text;
    }

    MessageLevel GS_TextMessage::GetLevel() const {
        return _level;
    }

    Void WriteTextMessage(UString text, MessageLevel level, Driver::GSContextPtr context) {
        auto textMessage = GS_TextMessage::Create(std::move(text), level);

        textMessage->Write(std::move(context));
    }

    Void GS_TextMessage::Write(Driver::GSContextPtr context) const {
        auto outputStream = context->GetStdIOStreamsManager()->GetStdOutStream();

        auto &stream = outputStream->GetOutStream();

        stream << rang::style::bold;

        switch (_level) {
            case MessageLevel::Note:
                stream << rang::fg::blue << "Note >> ";

                break;
            case MessageLevel::Warning:
                stream << rang::fg::yellow << "Warning >> ";

                break;
            case MessageLevel::Error:
                stream << rang::fg::red << "Error >> ";

                break;
            case MessageLevel::Fatal:
                stream << rang::fg::gray << "Fatal >> ";

                break;
        }

        stream << _text << std::endl;

        stream << rang::style::reset << rang::fg::reset;
    }

    GS_LocatedTextMessage::GS_LocatedTextMessage(UString text, IO::MessageLevel level, IO::GS_SourceLocation location)
            : GS_TextMessage(std::move(text), level), _location(location) {}

    std::shared_ptr<GS_LocatedTextMessage> GS_LocatedTextMessage::Create(UString text, IO::MessageLevel level, IO::GS_SourceLocation location) {
        return std::make_shared<GS_LocatedTextMessage>(std::move(text), level, location);
    }

    IO::GS_SourceLocation GS_LocatedTextMessage::GetLocation() const {
        return _location;
    }

    Void GS_LocatedTextMessage::Write(Driver::GSContextPtr context) const {
        auto outputStream = context->GetStdIOStreamsManager()->GetStdOutStream();

        auto &stream = outputStream->GetOutStream();

        auto source = context->GetSourceManager()->GetSource(_location.GetSourceHash());

        if (!source) {
            UStringStream stringStream;

            stringStream << "Can`t find source in context with source hash '"_us
                         << _location.GetSourceHash()
                         << "' for printing error!"_us;

            WriteTextMessage(stringStream.String(),
                             MessageLevel::Fatal,
                             context);

            return;
        }

        auto [line, column] = GS_SourceLocation::ToLineColumnLocation(_location.GetStartPosition(), source);

//        auto [startLocation, endLocation] = source->GetLineColumnLocation(_location);

        stream << rang::style::bold;

        switch (GetLevel()) {
            case MessageLevel::Note:
                stream << rang::fg::blue << "Note ";

                break;
            case MessageLevel::Warning:
                stream << rang::fg::yellow << "Warning ";

                break;
            case MessageLevel::Error:
                stream << rang::fg::red << "Error ";

                break;
            case MessageLevel::Fatal:
                stream << rang::fg::gray << "Fatal ";

                break;
        }

        stream << "{ "
               << source->GetName().GetName()
               << " [ "
               << line
               << ":"
               << column
               << " ] "
               << " } >> "
               << GetText()
               << std::endl;

        stream << rang::style::reset << rang::fg::reset;
    }

    Void WriteLocatedTextMessage(UString text, MessageLevel level, IO::GS_SourceLocation location, Driver::GSContextPtr context) {
        auto locatedTextMessage = GS_LocatedTextMessage::Create(std::move(text), level, location);

        locatedTextMessage->Write(std::move(context));
    }

//    inline rang::fg MessageLevelToFGColor(MessageLevel messageLevel) {
//        switch (messageLevel) {
//            case MessageLevel::Note:
//                return rang::fg::blue;
//            case MessageLevel::Warning:
//                return rang::fg::yellow;
//            case MessageLevel::Error:
//                return rang::fg::red;
//            case MessageLevel::Fatal:
//                return rang::fg::gray;
//        }
//
//        return rang::fg::reset;
//    }
//
//    GS_MessageHandler::GS_MessageHandler(GSOutStreamPtr stream)
//            : _stream(std::move(stream)) {}
//
//    std::shared_ptr<GS_MessageHandler> GS_MessageHandler::Create(GSOutStreamPtr stream) {
//        return std::make_shared<GS_MessageHandler>(std::move(stream));
//    }
//
//    std::shared_ptr<GS_MessageHandler> GS_MessageHandler::Create() {
//        return GS_MessageHandler::Create(GS_OutConsoleStream::CreateCErr());
//    }
//
//    Void GS_MessageHandler::Write(UString message, MessageLevel messageLevel) {
//        auto color = MessageLevelToFGColor(messageLevel);
//
//        UString messagePrefix;
//
//        switch (messageLevel) {
//            case MessageLevel::Note:
//                messagePrefix = "Note: ";
//
//                break;
//            case MessageLevel::Warning:
//                messagePrefix = "Warning: ";
//
//                break;
//            case MessageLevel::Error:
//                messagePrefix = "Error: ";
//
//                break;
//            case MessageLevel::Fatal:
//                messagePrefix = "Fatal: ";
//
//                break;
//        }
//
//        BeginPrintLine();
//
//        _stream->GetOutStream() << color << messagePrefix + message;
//
//        EndPrintLine();
//
//        BeginPrintLine();
//
//        EndPrintLine();
//    }
//
//    Void GS_MessageHandler::Write(UString message, MessageLevel messageLevel, SourceRange sourceRange, UString text) {
//        auto color = MessageLevelToFGColor(messageLevel);
//
//        BeginPrintLine();
//
//        _stream->GetOutStream() << color << sourceRange.GetSourceName() << " " << sourceRange.GetStartLine() << ": >> " << text;
//
//        EndPrintLine();
//
//        BeginPrintLine();
//
//        _stream->GetOutStream() << color;
//
//        auto aligning = sourceRange.GetSourceName().Size() + std::to_string(sourceRange.GetStartLine()).size() + 6;
//
//        for (U64 i = 1; i < sourceRange.GetStartColumn() + aligning; ++i) {
//            _stream->GetOutStream() << " ";
//        }
//
//        for (U64 i = sourceRange.GetStartColumn() + aligning; i <= sourceRange.GetEndColumn() + aligning; ++i) {
//            _stream->GetOutStream() << "^";
//        }
//
//        EndPrintLine();
//
//        UString messagePrefix;
//
//        switch (messageLevel) {
//            case MessageLevel::Note:
//                messagePrefix = "Note: ";
//
//                break;
//            case MessageLevel::Warning:
//                messagePrefix = "Warning: ";
//
//                break;
//            case MessageLevel::Error:
//                messagePrefix = "Error: ";
//
//                break;
//            case MessageLevel::Fatal:
//                messagePrefix = "Fatal: ";
//
//                break;
//        }
//
//        BeginPrintLine();
//
//        _stream->GetOutStream() << color << messagePrefix + message;
//
//        EndPrintLine();
//
//        BeginPrintLine();
//
//        EndPrintLine();
//    }
//
//    Void GS_MessageHandler::Write(UString message, MessageLevel messageLevel, std::vector<SourceRange> sourceRanges, std::vector<UString> texts) {
//        if (sourceRanges.size() != texts.size()) {
//            Print("MessageHandler::Write(UString, MessageLevel, std::vector<SourceRange>, std::vector<UString>): \nCan`t call GSLanguageCompiler internal function with different size of source ranges and texts!",
//                  MessageLevel::Fatal);
//
//            return;
//        }
//
//        auto color = MessageLevelToFGColor(messageLevel);
//
//        for (U64 index = 0; index < sourceRanges.size(); ++index) {
//            auto sourceRange = sourceRanges[index];
//            auto text = texts[index];
//
//            BeginPrintLine();
//
//            _stream->GetOutStream() << color << sourceRange.GetSourceName() << " " << sourceRange.GetStartLine() << ": >> " << text;
//
//            EndPrintLine();
//
//            BeginPrintLine();
//
//            _stream->GetOutStream() << color;
//
//            auto aligning = sourceRange.GetSourceName().Size() + std::to_string(sourceRange.GetStartLine()).size() + 6;
//
//            for (U64 i = 1; i < sourceRange.GetStartColumn() + aligning; ++i) {
//                _stream->GetOutStream() << " ";
//            }
//
//            for (U64 i = sourceRange.GetStartColumn() + aligning; i <= sourceRange.GetEndColumn() + aligning; ++i) {
//                _stream->GetOutStream() << "^";
//            }
//
//            EndPrintLine();
//        }
//
//        Write(message, messageLevel);
//    }
//
//    Void GS_MessageHandler::BeginPrintLine() {
//        _stream->GetOutStream() << rang::style::reset << rang::fg::reset << rang::style::bold << "|> "_us;
//    }
//
//    Void GS_MessageHandler::EndPrintLine() {
//        _stream->GetOutStream() << rang::style::reset << rang::fg::reset << std::endl;
//    }

}
