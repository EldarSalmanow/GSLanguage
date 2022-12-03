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
     * Class for containing any messages
     */
    class GS_Message {
    public:

        /**
         * Constructor for message
         * @param text Message text
         * @param level Message level
         * @param location Message location
         */
        GS_Message(UString text,
                   MessageLevel level,
                   std::optional<GS_SourceLocation> location);

    public:

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param location Message location
         * @return Message ptr
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 std::optional<GS_SourceLocation> location);

        /**
         * Creating message
         * @param text Message text
         * @param level Message level
         * @param location Message location
         * @return Message ptr
         */
        static GS_Message Create(UString text,
                                 MessageLevel level,
                                 GS_SourceLocation location);

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
         * Getter for message location
         * @return Message location
         */
        std::optional<GS_SourceLocation> GetLocation() const;

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
         * Message location
         */
        std::optional<GS_SourceLocation> _location;
    };

    /**
     * Message ptr type
     */
    using GSMessagePtr = std::shared_ptr<GS_Message>;

    /**
     * Message ptr array
     */
    using GSMessagePtrArray = std::vector<GSMessagePtr>;

    /**
     * Class for handling messages and writing to output stream
     */
    class GS_MessageHandler {
    public:

        /**
         * Constructor for message handler
         * @param outputStream Output stream
         * @param sourceManager Source manager
         */
        GS_MessageHandler(GSOutStreamPtr outputStream,
                          GSSourceManagerPtr sourceManager);

    public:

        /**
         * Creating message handler
         * @param outputStream Output stream
         * @param sourceManager Source manager
         * @return Message handler ptr
         */
        static std::shared_ptr<GS_MessageHandler> Create(GSOutStreamPtr outputStream,
                                                         GSSourceManagerPtr sourceManager);

    public:

        /**
         * Writing message to output stream
         * @param message Message
         * @return
         */
        Void Write(GS_Message message);

    public:

        /**
         * Getter for output stream
         * @return Output stream
         */
        GSOutStreamPtr GetOutputStream();

        /**
         * Getter for source manager
         * @return Source manager
         */
        GSSourceManagerPtr GetSourceManager();

    private:

        /**
         * Output stream
         */
        GSOutStreamPtr _outputStream;

        /**
         * Source manager
         */
        GSSourceManagerPtr _sourceManager;
    };

    /**
     * Message handler ptr type
     */
    using GSMessageHandlerPtr = std::shared_ptr<GS_MessageHandler>;

}

#endif //GSLANGUAGE_GS_MESSAGE_H
