#include <GSCrossPlatform/Defines.h>

#if defined(GS_OS_WINDOWS)

    /**
     * Can`t include in rang.hpp io.h standard header because preprocessor include IO.h project header.
     * Including low-level I/O functions manually from corecrt_io.h
     */
    #include <corecrt_io.h>

#endif

#include <rang.hpp>

#include <Driver/GS_GlobalContext.h>

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

    Bool GS_Message::operator==(ConstLRef<GS_Message> message) const {
        return _text == message.GetText()
            && _level == message.GetLevel()
            && _location == message.GetLocation();
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

    GS_MessageQueue::GS_MessageQueue(GSMessageArray messages)
            : _messages(std::move(messages)) {}

    GS_MessageQueue GS_MessageQueue::Create(GSMessageArray messages) {
        return GS_MessageQueue(std::move(messages));
    }

    GS_MessageQueue GS_MessageQueue::Create() {
        return GS_MessageQueue::Create(GSMessageArray());
    }

    ConstLRef<GS_Message> GS_MessageQueue::AddMessage(GS_Message message) {
        _messages.emplace_back(std::move(message));

        return _messages[_messages.size() - 1];
    }

    Void GS_MessageQueue::Clear() {
        _messages.clear();
    }

    Void GS_MessageQueue::Flush(LRef<GS_MessageStream> messageStream) {
        for (auto &message : _messages) {
            messageStream << message;
        }

        Clear();
    }

    ConstLRef<GSMessageArray> GS_MessageQueue::GetMessages() const {
        return _messages;
    }

    LRef<GS_MessageQueue> GS_MessageQueue::operator<<(ConstLRef<GS_Message> message) {
        AddMessage(message);

        return *this;
    }

    GS_MessageBuilder::GS_MessageBuilder(UString messageText,
                                         MessageLevel messageLevel,
                                         std::optional<GS_SourceLocation> messageLocation)
            : _messageText(std::move(messageText)),
              _messageLevel(messageLevel),
              _messageLocation(messageLocation) {}

    GS_MessageBuilder GS_MessageBuilder::Create(UString messageText,
                                                MessageLevel messageLevel,
                                                std::optional<GS_SourceLocation> messageLocation) {
        return GS_MessageBuilder(std::move(messageText),
                                 messageLevel,
                                 messageLocation);
    }

    GS_MessageBuilder GS_MessageBuilder::Create(UString messageText,
                                                MessageLevel messageLevel,
                                                GS_SourceLocation messageLocation) {
        return GS_MessageBuilder::Create(std::move(messageText),
                                         messageLevel,
                                         std::make_optional(messageLocation));
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

    LRef<GS_MessageBuilder> GS_MessageBuilder::Location(GS_SourceLocation messageLocation) {
        _messageLocation = messageLocation;

        return *this;
    }

    GS_Message GS_MessageBuilder::Message() {
        auto message = GS_Message::Create(_messageText,
                                          _messageLevel,
                                          _messageLocation);

        _messageText = UString();
        _messageLevel = MessageLevel::Error;
        _messageLocation = std::nullopt;

        return message;
    }

    ConstLRef<UString> GS_MessageBuilder::GetMessageText() const {
        return _messageText;
    }

    MessageLevel GS_MessageBuilder::GetMessageLevel() const {
        return _messageLevel;
    }

    std::optional<GS_SourceLocation> GS_MessageBuilder::GetMessageLocation() const {
        return _messageLocation;
    }

    GS_MessageStream::GS_MessageStream(LRef<GSMessageHandler> messageHandler,
                                       LRef<GS_SourceManager> sourceManager)
            : _messageHandler(messageHandler),
              _sourceManager(sourceManager) {}

    GS_MessageStream GS_MessageStream::Create(LRef<GSMessageHandler> messageHandler,
                                              LRef<GS_SourceManager> sourceManager) {
        return GS_MessageStream(messageHandler,
                                sourceManager);
    }

    Void GS_MessageStream::Write(GS_Message message) {
        auto movedMessage = std::move(message);

        auto &messageText = movedMessage.GetText();
        auto messageLevel = movedMessage.GetLevel();
        auto optionalMessageLocation = movedMessage.GetLocation();

        auto [textMessageLevel, messageColor] = [messageLevel] () -> std::tuple<UString, rang::fg> {
            switch (messageLevel) {
                case MessageLevel::Note: {
                    return std::make_tuple("Note",
                                           rang::fg::blue);
                }
                case MessageLevel::Warning: {
                    return std::make_tuple("Warning",
                                           rang::fg::yellow);
                }
                case MessageLevel::Error: {
                    return std::make_tuple("Error",
                                           rang::fg::red);
                }
                case MessageLevel::Fatal: {
                    return std::make_tuple("Fatal",
                                           rang::fg::black);
                }
                default: {
                    return std::make_tuple("<invalid>",
                                           rang::fg::gray);
                }
            }
        }();

        _messageHandler << rang::style::bold << messageColor
                        << " |--------------------------------------------------"_us << std::endl
                        << "/"_us << std::endl
                        << "| "_us << textMessageLevel << rang::fg::reset << ": " << messageText << std::endl;

        if (optionalMessageLocation.has_value()) {
            auto &messageLocation = optionalMessageLocation.value();

            auto sourceHash = messageLocation.GetSourceHash();

            if (sourceHash == InvalidHash) {
                Driver::GlobalContext().Exit();
            }

            auto optionalSource = _sourceManager.GetSource(sourceHash);

            if (!optionalSource.has_value()) {
                Driver::GlobalContext().Exit();
            }

            auto &source = optionalSource.value();

            auto sourceName = source.GetName();
            auto [line, column] = source.GetLineColumnPosition(messageLocation.GetStartPosition());

            auto lineCode = source.GetCodeWhile(source.GetIteratorByPosition(line, 1),
                                                [] (ConstLRef<USymbol> symbol) -> Bool {
                return symbol != '\n';
            });

            _messageHandler << messageColor
                            << "| "_us << "> "_us << rang::fg::reset << sourceName.GetName() << ":" << "[" << line << "." << column << "]" << std::endl
                            << messageColor
                            << "| "_us << rang::fg::reset << lineCode <<  std::endl
                            << messageColor
                            << "| "_us << std::string(column - 2, ' ') /* whitespaces */ << std::string(messageLocation.GetLength(), '^') /* code underscores */ << std::endl << rang::fg::reset;
        }

        _messageHandler << messageColor
                        << "\\"_us << std::endl
                        << " |--------------------------------------------------"_us << std::endl
                        << rang::fg::reset << rang::style::reset;
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

    LRef<GS_MessageStream> GS_MessageStream::operator<<(ConstLRef<GS_MessageBuffer> messageBuffer) {
        for (auto &message : messageBuffer) {
            *this << message;
        }

        return *this;
    }

    LRef<GS_MessageStream> GS_MessageStream::operator<<(ConstLRef<GS_MessageQueue> messageQueue) {
        auto messages = messageQueue.GetMessages();

        for (auto &message : messages) {
            *this << message;
        }

        return *this;
    }

    LRef<GS_MessageStream> GS_MessageStream::operator<<(LRef<GS_MessageBuilder> builder) {
        auto message = builder.Message();

        *this << message;

        return *this;
    }

    GS_MessageStreamManager::GS_MessageStreamManager(GS_MessageStream messageOut,
                                                     GS_MessageStream messageErr,
                                                     GS_MessageStream messageLog)
            : _messageOut(messageOut),
              _messageErr(messageErr),
              _messageLog(messageLog) {}

    std::unique_ptr<GS_MessageStreamManager> GS_MessageStreamManager::Create(GS_MessageStream messageOut,
                                                                             GS_MessageStream messageErr,
                                                                             GS_MessageStream messageLog) {
        return std::make_unique<GS_MessageStreamManager>(messageOut,
                                                         messageErr,
                                                         messageLog);
    }

    std::unique_ptr<GS_MessageStreamManager> GS_MessageStreamManager::Create(LRef<GS_StdIOStreamManager> stdIOStreamManager,
                                                                             LRef<GS_SourceManager> sourceManager) {
        auto &standardOut = stdIOStreamManager.Out();
        auto &standardErr = stdIOStreamManager.Err();
        auto &standardLog = stdIOStreamManager.Log();

        auto messageOut = GS_MessageStream::Create(standardOut,
                                                   sourceManager);
        auto messageErr = GS_MessageStream::Create(standardErr,
                                                   sourceManager);
        auto messageLog = GS_MessageStream::Create(standardLog,
                                                   sourceManager);

        return GS_MessageStreamManager::Create(messageOut,
                                               messageErr,
                                               messageLog);
    }

    LRef<GS_MessageStream> GS_MessageStreamManager::Out() {
        return _messageOut;
    }

    LRef<GS_MessageStream> GS_MessageStreamManager::Err() {
        return _messageErr;
    }

    LRef<GS_MessageStream> GS_MessageStreamManager::Log() {
        return _messageLog;
    }

}
