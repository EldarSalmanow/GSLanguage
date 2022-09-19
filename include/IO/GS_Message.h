#ifndef GSLANGUAGE_GS_MESSAGE_H
#define GSLANGUAGE_GS_MESSAGE_H

#include <Driver/GS_Context.h>

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
    class GS_Message {
    public:

        /**
         * Virtual destructor for supporting inheritance
         */
        virtual ~GS_Message();

    public:

        /**
         * Writing message to standard output stream
         * @param context Context for getting any info for printing message
         * @return
         */
        virtual Void Write(Driver::GSContextPtr context) const = 0;
    };

    /**
     * Message ptr type
     */
    using GSMessagePtr = std::shared_ptr<GS_Message>;

    /**
     * Class for text messages
     */
    class GS_TextMessage : public GS_Message {
    public:

        /**
         * Constructor for text message
         * @param text Text of message
         * @param level Level of message
         */
        GS_TextMessage(UString text, MessageLevel level);

    public:

        /**
         * Creating text message
         * @param text Text of message
         * @param level Level of message
         * @return Text message ptr
         */
        static std::shared_ptr<GS_TextMessage> Create(UString text, MessageLevel level);

    public:

        /**
         * Getter for text of message
         * @return Text of message
         */
        UString GetText() const;

        /**
         * Getter for level of message
         * @return Level of message
         */
        MessageLevel GetLevel() const;

    public:

        /**
         * Writing text message to standard output stream
         * @param context Context for getting any info for printing message
         * @return
         */
        Void Write(Driver::GSContextPtr context) const override;

    private:

        /**
         * Text of message
         */
        UString _text;

        /**
         * Level of message
         */
        MessageLevel _level;
    };

    /**
     * Creating and writing text message to standard output stream
     * @param text Text of message
     * @param level Level of message
     * @param context Context for getting any info for printing message
     * @return
     */
    Void WriteTextMessage(UString text, MessageLevel level, Driver::GSContextPtr context);

    /**
     * Class for located text messages
     */
    class GS_LocatedTextMessage : public GS_TextMessage {
    public:

        /**
         * Constructor for located text message
         * @param text Text of message
         * @param level Level of message
         * @param location Location of message
         */
        GS_LocatedTextMessage(UString text, MessageLevel level, IO::GS_SourceLocation location);

    public:

        /**
         * Creating located text message
         * @param text Text of message
         * @param level Level of message
         * @param location Location of message
         * @return Located text message ptr
         */
        static std::shared_ptr<GS_LocatedTextMessage> Create(UString text, MessageLevel level, IO::GS_SourceLocation location);

    public:

        /**
         * Getter for location of message
         * @return Location of message
         */
        IO::GS_SourceLocation GetLocation() const;

    public:

        /**
         * Writing located text message to standard output stream
         * @param context Context for getting any info for printing message
         * @return
         */
        Void Write(Driver::GSContextPtr context) const override;

    public:

        /**
         * Location of message
         */
        IO::GS_SourceLocation _location;
    };

    /**
     * Creating and writing located text message to standard output stream
     * @param text Text of message
     * @param level Level of message
     * @param location Location of message
     * @param context Context for getting any info for printing message
     * @return
     */
    Void WriteLocatedTextMessage(UString text, MessageLevel level, IO::GS_SourceLocation location, Driver::GSContextPtr context);

}

#endif //GSLANGUAGE_GS_MESSAGE_H
