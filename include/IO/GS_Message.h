#ifndef GSLANGUAGE_GS_MESSAGE_H
#define GSLANGUAGE_GS_MESSAGE_H

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
     * Class for containing information about compiler message
     */
    class GS_Message {
    public:

        /*
         *
         * GS_Message PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message
         * @param text Message text
         * @param level Message level
         * @param locationRange Optional message source location range
         */
        GS_Message(UString text,
                   MessageLevel level,
                   std::optional<GS_SourceRange> locationRange);

    public:

        /*
         *
         * GS_Message PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param locationRange Optional message source location range
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 std::optional<GS_SourceRange> locationRange);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param locationRange Message source location range
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 GS_SourceRange locationRange);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param sourceLocation Message source location [sourceLocation, sourceLocation + 1) (one symbol)
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 GS_SourceLocation sourceLocation);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @return Message
         */
        static GS_Message Create(UString text,
                                 MessageLevel level);

    public:

        /*
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
         * Getter for optional message source location range
         * @return Optional message source location range
         */
        std::optional<GS_SourceRange> GetLocationRange() const;

    public:

        /*
         *
         * GS_Message PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Equality operator for message
         * @param message Message
         * @return Is equal messages
         */
        Bool operator==(ConstLRef<GS_Message> message) const;

    private:

        /*
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
         * Optional message source location range
         */
        std::optional<GS_SourceRange> _locationRange;
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

        /*
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

        /*
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

        /*
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

        /*
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

        /*
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

        /*
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

        /*
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
     * Declaring message stream for message queue
     */
    class GS_MessageStream;

    /**
     * Class for containing and flushing messages
     */
    class GS_MessageQueue {
    public:

        /*
         *
         * GS_MessageQueue PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message queue
         * @param messages Messages
         */
        explicit GS_MessageQueue(GSMessageArray messages);

    public:

        /*
         *
         * GS_MessageQueue PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message queue
         * @param messages Messages
         * @return Message queue
         */
        static GS_MessageQueue Create(GSMessageArray messages);

        /**
         * Creating message queue
         * @return Message queue
         */
        static GS_MessageQueue Create();

    public:

        /*
         *
         * GS_MessageQueue PUBLIC METHODS
         *
         */

        /**
         * Adding message to message queue
         * @param message Message
         * @return Message
         */
        ConstLRef<GS_Message> AddMessage(GS_Message message);

        /**
         * Clearing queue
         * @return Void return
         */
        Void Clear();

        /**
         * Flush messages to message stream and clear it
         * @param messageStream Message stream
         * @return Void return
         */
        Void Flush(LRef<GS_MessageStream> messageStream);

    public:

        /*
         *
         * GS_MessageQueue PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for messages
         * @return Messages
         */
        ConstLRef<GSMessageArray> GetMessages() const;

    public:

        /*
         *
         * GS_MessageQueue PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Stream operator for adding message to message queue
         * @param message Message
         * @return Message queue
         */
        LRef<GS_MessageQueue> operator<<(ConstLRef<GS_Message> message);

    private:

        /*
         *
         * GS_MessageQueue PRIVATE FIELDS
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

        /*
         *
         * GS_MessageBuilder PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message builder
         * @param messageText Message text
         * @param messageLevel Message level
         * @param messageLocationRange Optional message source location range
         */
        GS_MessageBuilder(UString messageText,
                          MessageLevel messageLevel,
                          std::optional<GS_SourceRange> messageLocationRange);

    public:

        /*
         *
         * GS_MessageBuilder PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message builder
         * @param messageText Message text
         * @param messageLevel Message level
         * @param messageLocationRange Optional message source location range
         * @return Message builder
         */
        static GS_MessageBuilder Create(UString messageText,
                                        MessageLevel messageLevel,
                                        std::optional<GS_SourceRange> messageLocationRange);

        /**
         * Creating message builder
         * @param messageText Message text
         * @param messageLevel Message level
         * @param messageLocationRange Message source location range
         * @return Message builder
         */
        static GS_MessageBuilder Create(UString messageText,
                                        MessageLevel messageLevel,
                                        GS_SourceRange messageLocationRange);

        /**
         * Creating message builder
         * @param messageText Message text
         * @param messageLevel Message level
         * @param messageSourceLocation Message source location [sourceLocation, sourceLocation + 1) (one symbol)
         * @return Message builder
         */
        static GS_MessageBuilder Create(UString messageText,
                                        MessageLevel messageLevel,
                                        GS_SourceLocation messageSourceLocation);

        /**
         * Creating message builder
         * @param messageText Message text
         * @param messageLevel Message level
         * @return Message builder
         */
        static GS_MessageBuilder Create(UString messageText,
                                        MessageLevel messageLevel);

        /**
         * Creating message builder
         * @return Message builder
         */
        static GS_MessageBuilder Create();

    public:

        /*
         *
         * GS_MessageBuilder PUBLIC METHODS
         *
         */

        /**
         * Setting message text in message
         * @param messageText Message text
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Text(UString messageText);

        /**
         * Setting message level in message
         * @param messageLevel Message level
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Level(MessageLevel messageLevel);

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
         * @param messageLocationRange Message source location range
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Location(GS_SourceRange messageLocationRange);

        /**
         * Setting message source location range in message to [sourceLocation, sourceLocation + 1) (one symbol)
         * @param messageSourceLocation Message source location
         * @return Message builder
         */
        LRef<GS_MessageBuilder> Location(GS_SourceLocation messageSourceLocation);

        /**
         * Creating message
         * @return Message
         */
        GS_Message Message();

    public:

        /*
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
         * Getter for optional message source location range
         * @return Optional message source location range
         */
        std::optional<GS_SourceRange> GetMessageLocationRange() const;

    private:

        /*
         *
         * GS_MessageBuilder PRIVATE FIELDS
         *
         */

        /**
         * Message text
         */
        UString _messageText;

        /**
         * Message level
         */
        MessageLevel _messageLevel;

        /**
         * Optional message source location range
         */
        std::optional<GS_SourceRange> _messageLocationRange;
    };

    /**
     * Message handler type
     */
    using GSMessageHandler = OutputStream;

    /**
     * Class for rendering and writing compiler messages in message handler
     */
    class GS_MessageStream {
    public:

        /*
         *
         * GS_MessageStream PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message stream
         * @param messageHandler Message handler
         * @param sourceManager Source manager
         */
        GS_MessageStream(LRef<GSMessageHandler> messageHandler,
                         LRef<GS_SourceManager> sourceManager);

    public:

        /*
         *
         * GS_MessageStream PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message stream
         * @param messageHandler Message handler
         * @param sourceManager Source manager
         * @return Message stream
         */
        static GS_MessageStream Create(LRef<GSMessageHandler> messageHandler,
                                       LRef<GS_SourceManager> sourceManager);

    public:

        /*
         *
         * GS_MessageStream PUBLIC METHODS
         *
         */

        /**
         * Writing message in message handler
         * @param message Message
         * @return Void return
         * @todo Rewrite
         */
        Void Write(GS_Message message);

    public:

        /*
         *
         * GS_MessageStream PUBLIC GETTER METHODS
         *
         */

        /**
         * Getter for message handler
         * @return Message handler
         */
        LRef<GSMessageHandler> GetMessageHandler();

        /**
         * Getter for source manager
         * @return Source manager
         */
        LRef<GS_SourceManager> GetSourceManager();

    public:

        /*
         *
         * GS_MessageStream PUBLIC OPERATOR METHODS
         *
         */

        /**
         * Stream operator for writing message in message handler
         * @param message Message
         * @return Message stream
         */
        LRef<GS_MessageStream> operator<<(ConstLRef<GS_Message> message);

        /**
         * Stream operator for writing message buffer in message handler
         * @param messageBuffer Message buffer
         * @return Message stream
         */
        LRef<GS_MessageStream> operator<<(ConstLRef<GS_MessageBuffer> messageBuffer);

        /**
         * Stream operator for writing message queue in message handler
         * @param messageQueue Message queue
         * @return Message stream
         */
        LRef<GS_MessageStream> operator<<(ConstLRef<GS_MessageQueue> messageQueue);

        /**
         * Stream operator for writing message from message builder in message handler
         * @param builder Message builder
         * @return Message stream
         */
        LRef<GS_MessageStream> operator<<(LRef<GS_MessageBuilder> builder);

    private:

        /*
         *
         * GS_MessageStream PRIVATE FIELDS
         *
         */

        /**
         * Message handler
         */
        LRef<GSMessageHandler> _messageHandler;

        /**
         * Source manager
         */
        LRef<GS_SourceManager> _sourceManager;
    };

    /**
     * Class for containing and managing message streams
     */
    class GS_MessageStreamManager {
    public:

        /*
         *
         * GS_MessageStreamManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for message stream manager
         * @param messageOut Output message stream
         * @param messageErr Error message stream
         * @param messageLog Logger message stream
         */
        GS_MessageStreamManager(GS_MessageStream messageOut,
                                GS_MessageStream messageErr,
                                GS_MessageStream messageLog);

    public:

        /*
         *
         * GS_MessageStreamManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating message stream manager
         * @param messageOut Output message stream
         * @param messageErr Error message stream
         * @param messageLog Logger message stream
         * @return Message stream manager ptr
         */
        static std::unique_ptr<GS_MessageStreamManager> Create(GS_MessageStream messageOut,
                                                               GS_MessageStream messageErr,
                                                               GS_MessageStream messageLog);

        /**
         * Creating message stream manager
         * @param stdIOStreamManager Standard IO stream manager
         * @param sourceManager Source manager
         * @return Message stream manager ptr
         */
        static std::unique_ptr<GS_MessageStreamManager> Create(LRef<GS_StdIOStreamManager> stdIOStreamManager,
                                                               LRef<GS_SourceManager> sourceManager);

    public:

        /*
         *
         * GS_MessageStreamManager PUBLIC METHODS
         *
         */

        /**
         * Getting output message stream
         * @return Output message stream
         */
        LRef<GS_MessageStream> Out();

        /**
         * Getting error message stream
         * @return Error message stream
         */
        LRef<GS_MessageStream> Err();

        /**
         * Getting logger message stream
         * @return Logger message stream
         */
        LRef<GS_MessageStream> Log();

    private:

        /*
         *
         * GS_MessageStreamManager PRIVATE FIELDS
         *
         */

        /**
         * Output message stream
         */
        GS_MessageStream _messageOut;

        /**
         * Error message stream
         */
        GS_MessageStream _messageErr;

        /**
         * Logger message stream
         */
        GS_MessageStream _messageLog;
    };

    /**
     * Message stream manager ptr type
     */
    using GSMessageStreamManagerPtr = std::unique_ptr<GS_MessageStreamManager>;

}

#endif //GSLANGUAGE_GS_MESSAGE_H
