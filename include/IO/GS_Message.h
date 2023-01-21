#ifndef GSLANGUAGE_GS_MESSAGE_H
#define GSLANGUAGE_GS_MESSAGE_H

#include <optional>

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
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 std::optional<GSByteSourceRange> locationRange);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param locationRange Message byte source location range
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 GSByteSourceRange locationRange);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param sourceLocation Message byte source location
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 GS_ByteSourceLocation sourceLocation);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @return Message
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

    /**
     * Class for smart creating messages
     */
    class GS_MessageBuilder {
    public:

        /**
         * Constructor for message builder
         */
        GS_MessageBuilder();

    public:

        /**
         * Creating message builder
         * @return Message builder
         */
        static GS_MessageBuilder Create();

    public:

        /**
         * Setting message text in message
         * @param text Message text
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Text(UString text);

        /**
         * Setting message level in message
         * @param level Message level
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Level(MessageLevel level);

        /**
         * Setting message level in message to 'note'
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Note();

        /**
         * Setting message level in message to 'warning'
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Warning();

        /**
         * Setting message level in message to 'error'
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Error();

        /**
         * Setting message level in message to 'fatal'
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Fatal();

        /**
         * Setting message source location range in message
         * @param locationRange Message byte source location range
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Location(GSByteSourceRange locationRange);

        /**
         * Setting message source location range in message to [sourceLocation, sourceLocation + 1] (one symbol)
         * @param sourceLocation Message byte source location
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Location(GS_ByteSourceLocation sourceLocation);

        /**
         * Creating message
         * @return Message
         */
        GS_Message Message();

    public:

        // add getters ?

    private:

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

    class GS_MessageRenderer {
    public:

        GS_MessageRenderer(LRef<std::ostream> outputStream,
                           LRef<GS_SourceManager> sourceManager);

    public:

        static std::unique_ptr<GS_MessageRenderer> Create(LRef<std::ostream> outputStream,
                                                          LRef<GS_SourceManager> sourceManager);

        static std::unique_ptr<GS_MessageRenderer> Create(LRef<GS_SourceManager> sourceManager);

    public:

        Void Render(GS_Message message);

    public:

        // add getters ?

    private:

        LRef<std::ostream> _outputStream;

        LRef<GS_SourceManager> _sourceManager;
    };

    using GSMessageRendererPtr = std::unique_ptr<GS_MessageRenderer>; // delete ?

    Void ErrorExample() {
        auto sourceManager = GS_SourceManager::Create();
        auto messageRenderer = GS_MessageRenderer::Create(*sourceManager);

        sourceManager->AddCustomSource("func main() {\r\n    println(\"Hello, World!\"\r\n}",
                                       "main.gs");

        auto message = GS_MessageBuilder::Create().Text("Missed ')' in function calling expression!")
                                                  .Error()
                                                  .Location(GS_ByteSourceLocation::Create(41))
                                                  .Message();

        messageRenderer->Render(message);
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
