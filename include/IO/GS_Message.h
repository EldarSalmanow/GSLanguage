#ifndef GSLANGUAGE_GS_MESSAGE_H
#define GSLANGUAGE_GS_MESSAGE_H

#include <optional>

#include <IO/GS_Stream.h>

#include <IO/GS_Source.h>

namespace GSLanguageCompiler::IO {

    /**
     * Level of messages
     */
    enum class MessageLevel {
        Note,
        Warning,
        Error,
        Fatal
    };

    /**
     * Base class for all messages
     */
//    class GS_Message {
//    public:
//
//        /**
//         * Virtual destructor for supporting inheritance
//         */
//        virtual ~GS_Message();
//
//    public:
//
//        /**
//         * Writing message to standard output stream
//         * @param context Context for getting any info for printing message
//         * @return
//         */
//        virtual Void Write(Driver::GSContextPtr context) const = 0;
//    };
//
//    /**
//     * Message ptr type
//     */
//    using GSMessagePtr = std::shared_ptr<GS_Message>;
//
//    /**
//     * Message ptr array type
//     */
//    using GSMessagePtrArray = std::vector<GSMessagePtr>;
//
//    /**
//     * Class for text messages
//     */
//    class GS_TextMessage : public GS_Message {
//    public:
//
//        /**
//         * Constructor for text message
//         * @param text Text of message
//         * @param level Level of message
//         */
//        GS_TextMessage(UString text, MessageLevel level);
//
//    public:
//
//        /**
//         * Creating text message
//         * @param text Text of message
//         * @param level Level of message
//         * @return Text message ptr
//         */
//        static std::shared_ptr<GS_TextMessage> Create(UString text, MessageLevel level);
//
//    public:
//
//        /**
//         * Getter for text of message
//         * @return Text of message
//         */
//        UString GetText() const;
//
//        /**
//         * Getter for level of message
//         * @return Level of message
//         */
//        MessageLevel GetLevel() const;
//
//    public:
//
//        /**
//         * Writing text message to standard output stream
//         * @param context Context for getting any info for printing message
//         * @return
//         */
//        Void Write(Driver::GSContextPtr context) const override;
//
//    private:
//
//        /**
//         * Text of message
//         */
//        UString _text;
//
//        /**
//         * Level of message
//         */
//        MessageLevel _level;
//    };
//
//    /**
//     * Creating and writing text message to standard output stream
//     * @param text Text of message
//     * @param level Level of message
//     * @param context Context for getting any info for printing message
//     * @return
//     */
//    Void WriteTextMessage(UString text, MessageLevel level, Driver::GSContextPtr context);
//
//    /**
//     * Class for located text messages
//     */
//    class GS_LocatedTextMessage : public GS_TextMessage {
//    public:
//
//        /**
//         * Constructor for located text message
//         * @param text Text of message
//         * @param level Level of message
//         * @param location Location of message
//         */
//        GS_LocatedTextMessage(UString text, MessageLevel level, GS_SourceLocation location);
//
//    public:
//
//        /**
//         * Creating located text message
//         * @param text Text of message
//         * @param level Level of message
//         * @param location Location of message
//         * @return Located text message ptr
//         */
//        static std::shared_ptr<GS_LocatedTextMessage> Create(UString text, MessageLevel level, GS_SourceLocation location);
//
//    public:
//
//        /**
//         * Getter for location of message
//         * @return Location of message
//         */
//        GS_SourceLocation GetLocation() const;
//
//    public:
//
//        /**
//         * Writing located text message to standard output stream
//         * @param context Context for getting any info for printing message
//         * @return
//         */
//        Void Write(Driver::GSContextPtr context) const override;
//
//    public:
//
//        /**
//         * Location of message
//         */
//        GS_SourceLocation _location;
//    };
//
//    /**
//     * Creating and writing located text message to standard output stream
//     * @param text Text of message
//     * @param level Level of message
//     * @param location Location of message
//     * @param context Context for getting any info for printing message
//     * @return
//     */
//    Void WriteLocatedTextMessage(UString text, MessageLevel level, GS_SourceLocation location, Driver::GSContextPtr context);

    class Message {
    public:

        Message(UString text, MessageLevel level, std::optional<GS_SourceLocation> location)
                : _text(std::move(text)), _level(level), _location(location) {}

    public:

        static Message Create(UString text, MessageLevel level, std::optional<GS_SourceLocation> location) {
            return Message(std::move(text), level, location);
        }

        static Message Create(UString text, MessageLevel level, GS_SourceLocation location) {
            return Message::Create(std::move(text), level, std::make_optional(location));
        }

        static Message Create(UString text, MessageLevel level) {
            return Message::Create(std::move(text), level, std::nullopt);
        }

    public:

        UString GetText() const {
            return _text;
        }

        MessageLevel GetLevel() const {
            return _level;
        }

        std::optional<GS_SourceLocation> GetLocation() const {
            return _location;
        }

    private:

        UString _text;

        MessageLevel _level;

        std::optional<GS_SourceLocation> _location;
    };

    class GS_MessageHandler {
    public:

        GS_MessageHandler(GSOutStreamPtr outputStream, GSSourceManagerPtr sourceManager);

    public:

        static std::shared_ptr<GS_MessageHandler> Create(GSOutStreamPtr outputStream, GSSourceManagerPtr sourceManager);

    public:

        Void Write(Message message);

    public:

        GSOutStreamPtr GetOutputStream();

        GSSourceManagerPtr GetSourceManager();

    private:

        GSOutStreamPtr _outputStream;

        GSSourceManagerPtr _sourceManager;
    };

    using GSMessageHandlerPtr = std::shared_ptr<GS_MessageHandler>;

}

#endif //GSLANGUAGE_GS_MESSAGE_H
