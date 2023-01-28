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
                           std::optional<GSByteSourceRange> locationRange)
            : _text(std::move(text)),
              _level(level),
              _locationRange(locationRange) {}

    GS_Message GS_Message::Create(UString text,
                                  MessageLevel level,
                                  std::optional<GSByteSourceRange> locationRange) {
        return GS_Message(std::move(text),
                          level,
                          locationRange);
    }

    GS_Message GS_Message::Create(UString text,
                                  MessageLevel level,
                                  GSByteSourceRange locationRange) {
        return GS_Message::Create(std::move(text),
                                  level,
                                  std::make_optional(locationRange));
    }

    GS_Message GS_Message::Create(UString text,
                                  MessageLevel level,
                                  GS_ByteSourceLocation sourceLocation) {
        // TODO check

        auto sourceHash = sourceLocation.GetSourceHash();
        auto position = sourceLocation.GetPosition();

        auto endSourceLocation = GS_ByteSourceLocation::Create(sourceHash,
                                                               position + 1);

        auto locationRange = GSByteSourceRange::Create(sourceLocation, endSourceLocation);

        return GS_Message::Create(std::move(text),
                                  level,
                                  locationRange);
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

    std::optional<GSByteSourceRange> GS_Message::GetLocationRange() const {
        return _locationRange;
    }

    Bool GS_Message::operator==(ConstLRef<GS_Message> message) const {
        return _text == message.GetText()
            && _level == message.GetLevel()
            && _locationRange == message.GetLocationRange();
    }

    GS_MessageBuffer::GS_MessageBuffer(GSMessageArray messages)
            : _messages(std::move(messages)) {}

    GS_MessageBuffer GS_MessageBuffer::Create(GSMessageArray messages) {
        return GS_MessageBuffer(std::move(messages));
    }

    GS_MessageBuffer GS_MessageBuffer::Create() {
        return GS_MessageBuffer::Create(GSMessageArray());
    }

    GS_MessageBuffer::Iterator GS_MessageBuffer::begin() {
        return _messages.begin();
    }

    GS_MessageBuffer::Iterator GS_MessageBuffer::end() {
        return _messages.end();
    }

    GS_MessageBuffer::ConstIterator GS_MessageBuffer::begin() const {
        return _messages.begin();
    }

    GS_MessageBuffer::ConstIterator GS_MessageBuffer::end() const {
        return _messages.end();
    }

    GS_MessageBuffer::ConstIterator GS_MessageBuffer::cbegin() const {
        return _messages.cbegin();
    }

    GS_MessageBuffer::ConstIterator GS_MessageBuffer::cend() const {
        return _messages.cend();
    }

    ConstLRef<GSMessageArray> GS_MessageBuffer::GetMessages() const {
        return _messages;
    }

    Bool GS_MessageBuffer::operator==(ConstLRef<GS_MessageBuffer> messageBuffer) const {
        return _messages == messageBuffer.GetMessages();
    }

    LRef<GS_Message> GS_MessageBuffer::operator[](ConstLRef<U64> index) {
        return _messages[index];
    }

    ConstLRef<GS_Message> GS_MessageBuffer::operator[](ConstLRef<U64> index) const {
        return _messages[index];
    }

    GS_MessageBuilder::GS_MessageBuilder(UString messageText,
                                         MessageLevel messageLevel,
                                         std::optional<GSByteSourceRange> messageLocationRange)
            : _messageText(std::move(messageText)),
              _messageLevel(messageLevel),
              _messageLocationRange(messageLocationRange) {}

    GS_MessageBuilder GS_MessageBuilder::Create(UString messageText,
                                                MessageLevel messageLevel,
                                                std::optional<GSByteSourceRange> messageLocationRange) {
        return GS_MessageBuilder(std::move(messageText),
                                 messageLevel,
                                 messageLocationRange);
    }

    GS_MessageBuilder GS_MessageBuilder::Create(UString messageText,
                                                MessageLevel messageLevel,
                                                GSByteSourceRange messageLocationRange) {
        return GS_MessageBuilder::Create(std::move(messageText),
                                         messageLevel,
                                         std::make_optional(messageLocationRange));
    }

    GS_MessageBuilder GS_MessageBuilder::Create(UString messageText,
                                                MessageLevel messageLevel,
                                                GS_ByteSourceLocation messageSourceLocation) {
        // TODO check

        auto messageSourceHash = messageSourceLocation.GetSourceHash();
        auto messagePosition = messageSourceLocation.GetPosition();

        auto endSourceLocation = GS_ByteSourceLocation::Create(messageSourceHash,
                                                               messagePosition + 1);

        auto locationRange = GSByteSourceRange::Create(messageSourceLocation, endSourceLocation);

        return GS_MessageBuilder::Create(std::move(messageText),
                                         messageLevel,
                                         locationRange);
    }

    GS_MessageBuilder GS_MessageBuilder::Create(UString messageText,
                                                MessageLevel messageLevel) {
        return GS_MessageBuilder::Create(std::move(messageText),
                                         messageLevel,
                                         std::nullopt);
    }

    GS_MessageBuilder GS_MessageBuilder::Create() {
        return GS_MessageBuilder::Create(UString(),
                                         MessageLevel::Error,
                                         std::nullopt);
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Text(UString messageText) {
        _messageText = std::move(messageText);

        return *this;
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Level(MessageLevel messageLevel) {
        _messageLevel = messageLevel;

        return *this;
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Note() {
        return Level(MessageLevel::Note);
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Warning() {
        return Level(MessageLevel::Warning);
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Error() {
        return Level(MessageLevel::Error);
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Fatal() {
        return Level(MessageLevel::Fatal);
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Location(GSByteSourceRange messageLocationRange) {
        _messageLocationRange = messageLocationRange;

        return *this;
    }

    LRef<GS_MessageBuilder> GS_MessageBuilder::Location(GS_ByteSourceLocation messageSourceLocation) {
        // TODO check

        auto messageSourceHash = messageSourceLocation.GetSourceHash();
        auto messagePosition = messageSourceLocation.GetPosition();

        auto endMessageSourceLocation = GS_ByteSourceLocation::Create(messageSourceHash,
                                                                      messagePosition + 1);

        auto messageLocationRange = GSByteSourceRange::Create(messageSourceLocation,
                                                              endMessageSourceLocation);

        return Location(messageLocationRange);
    }

    GS_Message GS_MessageBuilder::Message() {
        auto message = GS_Message::Create(_messageText,
                                          _messageLevel,
                                          _messageLocationRange);

        _messageText = UString();
        _messageLevel = MessageLevel::Error;
        _messageLocationRange = std::nullopt;

        return message;
    }

    ConstLRef<UString> GS_MessageBuilder::GetMessageText() const {
        return _messageText;
    }

    MessageLevel GS_MessageBuilder::GetMessageLevel() const {
        return _messageLevel;
    }

    std::optional<GSByteSourceRange> GS_MessageBuilder::GetMessageLocationRange() const {
        return _messageLocationRange;
    }

    GS_MessageStream::GS_MessageStream(LRef<GSMessageHandler> messageHandler,
                                       LRef<GS_SourceManager> sourceManager)
            : _messageHandler(messageHandler),
              _sourceManager(sourceManager) {}

    std::unique_ptr<GS_MessageStream> GS_MessageStream::Create(LRef<GSMessageHandler> messageHandler,
                                                               LRef<GS_SourceManager> sourceManager) {
        return std::make_unique<GS_MessageStream>(messageHandler,
                                                  sourceManager);
    }

    Void GS_MessageStream::Write(GS_Message message) {
        // TODO realize
    }

    LRef<GSMessageHandler> GS_MessageStream::GetMessageHandler() {
        return _messageHandler;
    }

    LRef<GS_SourceManager> GS_MessageStream::GetSourceManager() {
        return _sourceManager;
    }

    LRef<GS_MessageStream> GS_MessageStream::operator<<(ConstLRef<GS_Message> message) {
        Write(message);

        return *this;
    }

    LRef<GS_MessageStream> GS_MessageStream::operator<<(LRef<GS_MessageBuilder> builder) {
        auto message = builder.Message();

        *this << message;

        return *this;
    }

    GS_MessageStreamsManager::GS_MessageStreamsManager(GSMessageStreamPtr messageOut,
                                                       GSMessageStreamPtr messageErr,
                                                       GSMessageStreamPtr messageLog)
            : _messageOut(std::move(messageOut)),
              _messageErr(std::move(messageErr)),
              _messageLog(std::move(messageLog)) {}

    std::unique_ptr<GS_MessageStreamsManager> GS_MessageStreamsManager::Create(GSMessageStreamPtr messageOut,
                                                                               GSMessageStreamPtr messageErr,
                                                                               GSMessageStreamPtr messageLog) {
        return std::make_unique<GS_MessageStreamsManager>(std::move(messageOut),
                                                          std::move(messageErr),
                                                          std::move(messageLog));
    }

    std::unique_ptr<GS_MessageStreamsManager> GS_MessageStreamsManager::Create(LRef<GS_StdIOStreamsManager> stdIOStreamsManager,
                                                                               LRef<GS_SourceManager> sourceManager) {
        auto &standardOut = stdIOStreamsManager.Out();
        auto &standardErr = stdIOStreamsManager.Err();
        auto &standardLog = stdIOStreamsManager.Log();

        auto messageOut = GS_MessageStream::Create(standardOut,
                                                   sourceManager);
        auto messageErr = GS_MessageStream::Create(standardErr,
                                                   sourceManager);
        auto messageLog = GS_MessageStream::Create(standardLog,
                                                   sourceManager);

        return GS_MessageStreamsManager::Create(std::move(messageOut),
                                                std::move(messageErr),
                                                std::move(messageLog));
    }

    LRef<GS_MessageStream> GS_MessageStreamsManager::Out() {
        return *_messageOut;
    }

    LRef<GS_MessageStream> GS_MessageStreamsManager::Err() {
        return *_messageErr;
    }

    LRef<GS_MessageStream> GS_MessageStreamsManager::Log() {
        return *_messageLog;
    }

//    GS_MessageHandler::GS_MessageHandler(LRef<std::ostream> outputStream,
//                                         LRef<GS_SourceManager> sourceManager)
//            : _outputStream(outputStream),
//              _sourceManager(sourceManager) {}
//
//    std::unique_ptr<GS_MessageHandler> GS_MessageHandler::Create(LRef<std::ostream> outputStream,
//                                                                 LRef<GS_SourceManager> sourceManager) {
//        return std::make_unique<GS_MessageHandler>(outputStream,
//                                                   sourceManager);
//    }
//
//    Void GS_MessageHandler::Write(GS_Message message) {
//        auto movedMessage = std::move(message);
//
//        auto &messageText = movedMessage.GetText();
//        auto messageLevel = movedMessage.GetLevel();
//        auto optionalMessageLocationRange = movedMessage.GetLocationRange();
//
//        _outputStream << rang::style::bold;
//
//        switch (messageLevel) {
//            case MessageLevel::Note:
//                _outputStream << rang::fg::blue
//                              << "Note ";
//
//                break;
//            case MessageLevel::Warning:
//                _outputStream << rang::fg::yellow
//                              << "Warning ";
//
//                break;
//            case MessageLevel::Error:
//                _outputStream << rang::fg::red
//                              << "Error ";
//
//                break;
//            case MessageLevel::Fatal:
//                _outputStream << rang::fg::gray
//                              << "Fatal ";
//
//                break;
//        }
//
//        if (optionalMessageLocationRange.has_value()) {
//            auto locationRange = optionalMessageLocationRange.value();
//
//            auto optionalSource = _sourceManager.GetSource(locationRange.GetStartLocation().GetSourceHash());
//
//            if (!optionalSource.has_value()) {
//                UStringStream stringStream;
//
//                stringStream << "Can`t find source in context with source hash '"_us
//                             << locationRange.GetStartLocation().GetSourceHash()
//                             << "' for printing error!"_us;
//
//                auto fatalMessage = GS_Message::Create(stringStream.String(),
//                                                       MessageLevel::Fatal);
//
//                Write(fatalMessage);
//
//                return;
//            }
//
//            auto source = optionalSource.value();
//
//            auto startLineColumnSourceLocation = ToLineColumnSourceLocation(locationRange.GetStartLocation(),
//                                                                            source);
//
//            auto line = startLineColumnSourceLocation.GetLine();
//            auto column = startLineColumnSourceLocation.GetColumn();
//
//            _outputStream << "{ "
//                          << source.GetName().GetName()
//                          << " [ "
//                          << line
//                          << ":"
//                          << column
//                          << " ] "
//                          << " } ";
//        }
//
//        _outputStream << ">> "
//                      << messageText
//                      << std::endl;
//
//        _outputStream << rang::style::reset
//                      << rang::fg::reset;
//    }
//
//    Void GS_MessageHandler::Write(UString text,
//                                  MessageLevel level,
//                                  GSByteSourceRange locationRange) {
//        auto message = GS_Message::Create(std::move(text),
//                                          level,
//                                          locationRange);
//
//        Write(message);
//    }
//
//    Void GS_MessageHandler::Write(UString text,
//                                  MessageLevel level) {
//        auto message = GS_Message::Create(std::move(text),
//                                          level);
//
//        Write(message);
//    }
//
//    LRef<std::ostream> GS_MessageHandler::GetOutputStream() {
//        return _outputStream;
//    }
//
//    LRef<GS_SourceManager> GS_MessageHandler::GetSourceManager() {
//        return _sourceManager;
//    }
//
//    /**
//     * Class for handling messages and writing to output stream
//     */
//    class GS_MessageHandler {
//    public:
//
//        /**
//         *
//         * GS_MessageHandler PUBLIC CONSTRUCTORS
//         *
//         */
//
//        /**
//         * Constructor for message handler
//         * @param outputStream Output stream
//         * @param sourceManager Source manager
//         */
//        GS_MessageHandler(LRef<std::ostream> outputStream,
//                          LRef<GS_SourceManager> sourceManager);
//
//    public:
//
//        /**
//         *
//         * GS_MessageHandler PUBLIC STATIC CREATE METHODS
//         *
//         */
//
//        /**
//         * Creating message handler
//         * @param outputStream Output stream
//         * @param sourceManager Source manager
//         * @return Message handler ptr
//         */
//        static std::unique_ptr<GS_MessageHandler> Create(LRef<std::ostream> outputStream,
//                                                         LRef<GS_SourceManager> sourceManager);
//
//    public:
//
//        /**
//         *
//         * GS_MessageHandler PUBLIC METHODS
//         *
//         */
//
//        /**
//         * Writing message to output stream
//         * @param message Message
//         * @return
//         */
//        Void Write(GS_Message message);
//
//        /**
//         * Writing message to output stream
//         * @param text Message text
//         * @param level Message level
//         * @param locationRange Message byte source location range
//         * @return
//         */
//        Void Write(UString text,
//                   MessageLevel level,
//                   GSByteSourceRange locationRange);
//
//        /**
//         * Writing message to output stream
//         * @param text Message text
//         * @param level Message level
//         * @return
//         */
//        Void Write(UString text,
//                   MessageLevel level);
//
//    public:
//
//        /**
//         *
//         * GS_MessageHandler PUBLIC GETTER METHODS
//         *
//         */
//
//        /**
//         * Getter for output stream
//         * @return Output stream
//         */
//        LRef<std::ostream> GetOutputStream();
//
//        /**
//         * Getter for source manager
//         * @return Source manager
//         */
//        LRef<GS_SourceManager> GetSourceManager();
//
//    private:
//
//        /**
//         *
//         * GS_MessageHandler PRIVATE FIELDS
//         *
//         */
//
//        /**
//         * Output stream
//         */
//        LRef<std::ostream> _outputStream;
//
//        /**
//         * Source manager
//         */
//        LRef<GS_SourceManager> _sourceManager;
//    };
//
//    /**
//     * Message handler ptr type
//     */
//    using GSMessageHandlerPtr = std::unique_ptr<GS_MessageHandler>;

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
