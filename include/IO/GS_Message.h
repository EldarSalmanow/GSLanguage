#ifndef GSLANGUAGE_GS_MESSAGE_H
#define GSLANGUAGE_GS_MESSAGE_H

#include <optional>

#include <IO/GS_Source.h>

namespace GSLanguageCompiler::IO {

    // TODO location or location range in message ?
    // TODO update message rendering in message handler

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
     * Class for containing any messages
     */
    class GS_Message {
    public:

        /**
         *
         * GS_Message PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message
         * @param text Message text
         * @param level Message level
         * @param locationRange Message byte source location range
         */
        GS_Message(UString text,
                   MessageLevel level,
                   std::optional<GSByteSourceRange> locationRange);

    public:

        /**
         *
         * GS_Message PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param locationRange Message byte source location range
         * @return Message ptr
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 std::optional<GSByteSourceRange> locationRange);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param locationRange Message byte source location range
         * @return Message ptr
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 GSByteSourceRange locationRange);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @return Message ptr
         */
        static GS_Message Create(UString text,
                                 MessageLevel level);

    public:

        /**
         *
         * GS_Message PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for message text
         * @return Message text
         */
        ConstLRef<UString> GetText() const;

        /**
         * Getter for message level
         * @return Message level
         */
        MessageLevel GetLevel() const;

        /**
         * Getter for message byte source location range
         * @return Message byte source location range
         */
        std::optional<GSByteSourceRange> GetLocationRange() const;

    private:

        /**
         *
         * GS_Message PRIVATE FIELDS
         *
         */

        /**
         * Message text
         */
        UString _text;

        /**
         * Message level
         */
        MessageLevel _level;

        /**
         * Message byte source location range
         */
        std::optional<GSByteSourceRange> _locationRange;
    };

    /**
     * Message array type
     */
    using GSMessageArray = std::vector<GS_Message>;

    Void Write(GS_Message message,
               LRef<GS_SourceManager> sourceManager) {
        auto movedMessage = std::move(message);

        auto &messageText = movedMessage.GetText(); // Missed ')'!
        auto messageLevel = movedMessage.GetLevel(); // Error
        auto messageLocationRange = movedMessage.GetLocationRange().value(); // main.gs hash, 2.26, 2.26

        auto source = sourceManager.GetSource(messageLocationRange.GetStartLocation().GetSourceHash());
        auto code = source->GetCodeInRange(messageLocationRange);

        /**
         *
         * main.gs
         *
         * func main() {
         *     print("Hello, Eldar!"
         * }
         *
         * > main.gs[2:26] >> print("Hello, Eldar!"
         * >                                       ^
         * > Error: Missed ')'!
         *
         */
    }

    /**
     * Class for handling messages and writing to output stream
     */
    class GS_MessageHandler {
    public:

        /**
         *
         * GS_MessageHandler PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message handler
         * @param outputStream Output stream
         * @param sourceManager Source manager
         */
        GS_MessageHandler(LRef<std::ostream> outputStream,
                          LRef<GS_SourceManager> sourceManager);

    public:

        /**
         *
         * GS_MessageHandler PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message handler
         * @param outputStream Output stream
         * @param sourceManager Source manager
         * @return Message handler ptr
         */
        static std::unique_ptr<GS_MessageHandler> Create(LRef<std::ostream> outputStream,
                                                         LRef<GS_SourceManager> sourceManager);

    public:

        /**
         *
         * GS_MessageHandler PUBLIC METHODS
         *
         */

        /**
         * Writing message to output stream
         * @param message Message
         * @return
         */
        Void Write(GS_Message message);

        /**
         * Writing message to output stream
         * @param text Message text
         * @param level Message level
         * @param locationRange Message byte source location range
         * @return
         */
        Void Write(UString text,
                   MessageLevel level,
                   GSByteSourceRange locationRange);

        /**
         * Writing message to output stream
         * @param text Message text
         * @param level Message level
         * @return
         */
        Void Write(UString text,
                   MessageLevel level);

    public:

        /**
         *
         * GS_MessageHandler PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for output stream
         * @return Output stream
         */
        LRef<std::ostream> GetOutputStream();

        /**
         * Getter for source manager
         * @return Source manager
         */
        LRef<GS_SourceManager> GetSourceManager();

    private:

        /**
         *
         * GS_MessageHandler PRIVATE FIELDS
         *
         */

        /**
         * Output stream
         */
        LRef<std::ostream> _outputStream;

        /**
         * Source manager
         */
        LRef<GS_SourceManager> _sourceManager;
    };

    /**
     * Message handler ptr type
     */
    using GSMessageHandlerPtr = std::unique_ptr<GS_MessageHandler>;

}

#endif //GSLANGUAGE_GS_MESSAGE_H
