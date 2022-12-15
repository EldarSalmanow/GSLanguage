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

    GS_Message::GS_Message(UString text,
                           MessageLevel level,
                           std::optional<GS_SourceLocation> location)
            : _text(std::move(text)),
              _level(level),
              _location(location) {}

    GS_Message GS_Message::Create(UString text,
                                  MessageLevel level,
                                  std::optional<GS_SourceLocation> location) {
        return GS_Message(std::move(text),
                          level,
                          location);
    }

    GS_Message GS_Message::Create(UString text,
                                  MessageLevel level,
                                  GS_SourceLocation location) {
        return GS_Message::Create(std::move(text),
                                  level,
                                  std::make_optional(location));
    }

    GS_Message GS_Message::Create(UString text,
                                  MessageLevel level) {
        return GS_Message::Create(std::move(text),
                                  level,
                                  std::nullopt);
    }

    ConstLRef<UString> GS_Message::GetText() const {
        return _text;
    }

    MessageLevel GS_Message::GetLevel() const {
        return _level;
    }

    std::optional<GS_SourceLocation> GS_Message::GetLocation() const {
        return _location;
    }

    GS_MessageHandler::GS_MessageHandler(LRef<std::ostream> outputStream,
                                         LRef<GS_SourceManager> sourceManager)
            : _outputStream(outputStream),
              _sourceManager(sourceManager) {}

    std::unique_ptr<GS_MessageHandler> GS_MessageHandler::Create(LRef<std::ostream> outputStream,
                                                                 LRef<GS_SourceManager> sourceManager) {
        return std::make_unique<GS_MessageHandler>(outputStream,
                                                   sourceManager);
    }

    Void GS_MessageHandler::Write(GS_Message message) {
        auto movedMessage = std::move(message);

        auto &messageText = movedMessage.GetText();
        auto messageLevel = movedMessage.GetLevel();
        auto messageLocation = movedMessage.GetLocation();

        _outputStream << rang::style::bold;

        switch (messageLevel) {
            case MessageLevel::Note:
                _outputStream << rang::fg::blue
                              << "Note ";

                break;
            case MessageLevel::Warning:
                _outputStream << rang::fg::yellow
                              << "Warning ";

                break;
            case MessageLevel::Error:
                _outputStream << rang::fg::red
                              << "Error ";

                break;
            case MessageLevel::Fatal:
                _outputStream << rang::fg::gray
                              << "Fatal ";

                break;
        }

        if (messageLocation.has_value()) {
            auto location = messageLocation.value();

            auto source = _sourceManager.GetSource(location.GetSourceHash());

//            if (!source) {
//                UStringStream stringStream;
//
//                stringStream << "Can`t find source in context with source hash '"_us
//                             << location.GetSourceHash()
//                             << "' for printing error!"_us;
//
//                auto fatalMessage = GS_Message::Create(stringStream.String(),
//                                                       MessageLevel::Fatal);
//
//                Write(fatalMessage);
//
//                return;
//            }

            auto fullSourceLocation = GS_FullSourceLocation::FromSourceLocation(location,
                                                                                source);

            auto line = fullSourceLocation.GetStartLine();
            auto column = fullSourceLocation.GetStartColumn();

            _outputStream << "{ "
                          << source.GetName().GetName()
                          << " [ "
                          << line
                          << ":"
                          << column
                          << " ] "
                          << " } ";
        }

        _outputStream << ">> "
                      << messageText
                      << std::endl;

        _outputStream << rang::style::reset
                      << rang::fg::reset;
    }

    Void GS_MessageHandler::Write(UString text,
                                  MessageLevel level,
                                  GS_SourceLocation location) {
        auto message = GS_Message::Create(std::move(text),
                                          level,
                                          location);

        Write(message);
    }

    Void GS_MessageHandler::Write(UString text,
                                  MessageLevel level) {
        auto message = GS_Message::Create(std::move(text),
                                          level);

        Write(message);
    }

    LRef<std::ostream> GS_MessageHandler::GetOutputStream() {
        return _outputStream;
    }

    LRef<GS_SourceManager> GS_MessageHandler::GetSourceManager() {
        return _sourceManager;
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
