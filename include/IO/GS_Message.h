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
         * @param sourceLocation Message byte source location [sourceLocation, sourceLocation + 1] (one symbol)
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
     * Class for containing messages
     */
    class GS_MessageBuffer {
    public:

        /**
         *
         * GS_MessageBuffer PUBLIC TYPES
         *
         */

        /**
         * Iterator type
         */
        using Iterator = GSMessageArray::iterator;

        /**
         * Const iterator type
         */
        using ConstIterator = GSMessageArray::const_iterator;

    public:

        /**
         *
         * GS_MessageBuffer PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message buffer
         * @param messages Messages
         */
        explicit GS_MessageBuffer(GSMessageArray messages);

    public:

        /**
         *
         * GS_MessageBuffer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message buffer
         * @param messages Messages
         * @return Message buffer
         */
        static GS_MessageBuffer Create(GSMessageArray messages);

        /**
         * Creating message buffer
         * @return Message buffer
         */
        static GS_MessageBuffer Create();

    public:

        /**
         *
         * GS_MessageBuffer PUBLIC ITERATOR METHODS
         *
         */

        /**
         * Getting begin message buffer iterator
         * @return Begin message buffer iterator
         */
        Iterator begin();

        /**
         * Getting end message buffer iterator
         * @return End message buffer iterator
         */
        Iterator end();

        /**
         * Getting begin message buffer const iterator
         * @return Begin message buffer const iterator
         */
        ConstIterator begin() const;

        /**
         * Getting end message buffer const iterator
         * @return End message buffer const iterator
         */
        ConstIterator end() const;

        /**
         * Getting begin message buffer const iterator
         * @return Begin message buffer const iterator
         */
        ConstIterator cbegin() const;

        /**
         * Getting end message buffer const iterator
         * @return End message buffer const iterator
         */
        ConstIterator cend() const;

    public:

        /**
         *
         * GS_MessageBuffer PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for messages
         * @return Messages
         */
        ConstLRef<GSMessageArray> GetMessages() const;

    public:

        /**
         *
         * GS_MessageBuffer PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for message buffer
         * @param messageBuffer Message buffer
         * @return Is equal message buffers
         */
        Bool operator==(ConstLRef<GS_MessageBuffer> messageBuffer) const;

        /**
         * Index operator for message buffer
         * @param index Index
         * @return Message by index in messages
         */
        LRef<GS_Message> operator[](ConstLRef<U64> index);

        /**
         * Index operator for message buffer
         * @param index Index
         * @return Message by index in messages
         */
        ConstLRef<GS_Message> operator[](ConstLRef<U64> index) const;

    private:

        /**
         *
         * GS_MessageBuffer PRIVATE FIELDS
         *
         */

        /**
         * Messages
         */
        GSMessageArray _messages;
    };

    /**
     * Class for smart creating messages
     */
    class GS_MessageBuilder {
    public:

        /**
         *
         * GS_MessageBuilder PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message builder
         */
        GS_MessageBuilder();

    public:

        /**
         *
         * GS_MessageBuilder PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message builder
         * @return Message builder
         */
        static GS_MessageBuilder Create();

    public:

        /**
         *
         * GS_MessageBuilder PUBLIC METHODS
         *
         */

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

        /**
         *
         * GS_MessageBuilder PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for message text
         * @return Message text
         */
        ConstLRef<UString> GetMessageText() const;

        /**
         * Getter for message level
         * @return Message level
         */
        MessageLevel GetMessageLevel() const;

        /**
         * Getter for message byte source location range
         * @return Message byte source location range
         */
        ConstLRef<GSByteSourceRange> GetMessageLocationRange() const;

    private:

        /**
         *
         * GS_MessageBuilder PRIVATE FIELDS
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
     * Class for rendering message in output stream
     */
    class GS_MessageRenderer {
    public:

        /**
         *
         * GS_MessageRenderer PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message renderer
         * @param outputStream Output stream
         * @param sourceManager Source manager
         */
        GS_MessageRenderer(LRef<std::ostream> outputStream,
                           LRef<GS_SourceManager> sourceManager);

    public:

        /**
         *
         * GS_MessageRenderer PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message renderer
         * @param outputStream Output stream
         * @param sourceManager Source manager
         * @return Message renderer ptr
         */
        static std::unique_ptr<GS_MessageRenderer> Create(LRef<std::ostream> outputStream,
                                                          LRef<GS_SourceManager> sourceManager);

        /**
         * Creating message renderer
         * @param sourceManager Source manager
         * @return Message renderer ptr
         */
        static std::unique_ptr<GS_MessageRenderer> Create(LRef<GS_SourceManager> sourceManager);

    public:

        /**
         *
         * GS_MessageRenderer PUBLIC METHODS
         *
         */

        /**
         * Render message in output stream
         * @param message Message
         * @return
         */
        Void Render(GS_Message message);

    public:

        // add getters ?

    private:

        /**
         *
         * GS_MessageRenderer PRIVATE FIELDS
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
     * Message renderer ptr type
     */
    using GSMessageRendererPtr = std::unique_ptr<GS_MessageRenderer>; // delete ?

    class GS_MessageStream {
    public:

        GS_MessageStream(GS_MessageRenderer renderer);

    public:

        static GS_MessageStream Create(GS_MessageRenderer renderer);

        static GS_MessageStream Create(LRef<std::ostream> outputStream,
                                       LRef<GS_SourceManager> sourceManager);

        static GS_MessageStream Create(LRef<std::ostream> outputStream);

        static GS_MessageStream Create(LRef<GS_SourceManager> sourceManager);

        static GS_MessageStream Create();

    public:

        Void Write(ConstLRef<GS_Message> message);

    public:

        LRef<GS_MessageStream> operator<<(ConstLRef<GS_Message> message);

        LRef<GS_MessageStream> operator<<(ConstLRef<GS_MessageBuilder> builder);

    private:

        GS_MessageRenderer _renderer;
    };

    class GS_MessageStreamsManager {
    public:

        GS_MessageStreamsManager(GS_MessageStream messageOut,
                                 GS_MessageStream messageErr,
                                 GS_MessageStream messageLog);

    public:

        static std::unique_ptr<GS_MessageStreamsManager> Create(GS_MessageStream messageOut,
                                                                GS_MessageStream messageErr,
                                                                GS_MessageStream messageLog);

        static std::unique_ptr<GS_MessageStreamsManager> Create(LRef<GS_StdIOStreamsManager> stdIOStreamsManager);

        static std::unique_ptr<GS_MessageStreamsManager> Create();

    public:

        LRef<GS_MessageStream> Out();

        LRef<GS_MessageStream> Err();

        LRef<GS_MessageStream> Log();

    private:

        GS_MessageStream _messageOut;

        GS_MessageStream _messageErr;

        GS_MessageStream _messageLog;
    };

    using GSMessageStreamsManagerPtr = std::unique_ptr<GS_MessageStreamsManager>;

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

    using MessageHandler = std::ostream;

    class GS_IOContext {
    public:

        GS_IOContext(GSStdIOStreamsManagerPtr stdIOStreamsManager,
                     GSSourceManagerPtr sourceManager,
                     GSMessageStreamsManagerPtr messageStreamsManager);

    public:

        static std::unique_ptr<GS_IOContext> Create();

    private:

        GSStdIOStreamsManagerPtr _stdIOStreamsManager;

        GSSourceManagerPtr _sourceManager;

        GSMessageStreamsManagerPtr _messageStreamsManager;
    };

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
