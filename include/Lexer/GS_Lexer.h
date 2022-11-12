#ifndef GSLANGUAGE_GS_LEXER_H
#define GSLANGUAGE_GS_LEXER_H

#include <Driver/Driver.h>

#include <Lexer/GS_Token.h>

namespace GSLanguageCompiler::Lexer {

    class Cursor {
    public:

        explicit Cursor(UString::ConstIterator contentIterator)
                : _contentIterator(contentIterator) {}

    public:

        static Cursor Create(UString::ConstIterator contentIterator) {
            return Cursor(contentIterator);
        }

        static Cursor Create(LRef<UString> content) {
            return Cursor::Create(content.begin());
        }

    public:

        Void EatWhile(Bool (*predicate) (ConstLRef<USymbol>)) {
            while (predicate(Current()) && !IsEof()) {
                Next();
            }
        }

    public:

        USymbol Current() const {
            return *_contentIterator;
        }

        Void Next() {
            ++_contentIterator;
        }

        Void Prev() {
            --_contentIterator;
        }

        Bool IsEof() const {
            // TODO set EOF symbol to '\0' symbol
            return Current().CodePoint() == InvalidCodePoint;
        }

    private:

        UString::ConstIterator _contentIterator;
    };

    class Lexer_ {
    public:

        explicit Lexer_(Cursor cursor)
                : _cursor(cursor) {}

    public:

        static Lexer_ Create(Cursor cursor) {
            return Lexer_(cursor);
        }

        static Lexer_ Create(LRef<UString> content) {
            return Lexer_::Create(Cursor::Create(content));
        }

    public:

        GS_Token GetToken() {
            if (_cursor.Current().IsWhitespace()) {
                _cursor.Next();

                return GS_Token::Create(TokenType::SymbolSpace);
            } else if (_cursor.Current().IsIDStart()) {
                UString string;

                while (_cursor.Current().IsIDContinue() && !_cursor.IsEof()) {
                    string += _cursor.Current();

                    _cursor.Next();
                }



                return GS_Token::Create(TokenType::Identifier, );
            }
        }

    private:

        Cursor _cursor;
    };

    /**
     * Class for tokenizing source code
     */
    class GS_Lexer {
    public:

        /**
         * Constructor for lexer
         * @param session Session
         */
        explicit GS_Lexer(LRef<Driver::GS_Session> session);

    public:

        /**
         * Creating lexer
         * @param session Session
         * @return Lexer
         */
        static GS_Lexer Create(LRef<Driver::GS_Session> session);

    public:

        /**
         * Creating lexer and tokenizing source
         * @param session Session
         * @param source Source
         * @return Tokens
         */
        static GSTokenArray Run(LRef<Driver::GS_Session> session, IO::GSSourcePtr source);

    public:

        /**
         * Tokenizing code from source
         * @param source Source
         * @return Tokens
         */
        GSTokenArray Tokenize(IO::GSSourcePtr source);

    private:

        /**
         * Tokenizing one token
         * @return Token
         */
        GS_Token GetToken();

    private:

        /**
         * Getting current symbol from cursor
         * @return Current symbol value
         */
        USymbol CurrentSymbol();

        /**
         * Setting cursor to next symbol in content
         * @return
         */
        Void NextSymbol();

        /**
         * Setting cursor to previous symbol in content
         * @return
         */
        Void PrevSymbol();

    private:

        /**
         * Creating text message
         * @param message Message
         * @param messageLevel Message level
         * @return
         */
        Void Message(UString message, IO::MessageLevel messageLevel);

        /**
         * Creating located text message
         * @param message Message
         * @param messageLevel Message level
         * @param messageLocation Message location
         * @return
         */
        Void LocatedMessage(UString message, IO::MessageLevel messageLevel, IO::GS_SourceLocation messageLocation);

    private:

        /**
         * Session
         */
        LRef<Driver::GS_Session> _session;

        /**
         * Messages
         */
        IO::GSMessagePtrArray _messages;

        /**
         * Source
         */
        IO::GSSourcePtr _source;

        /**
         * Content
         */
        UString _content;

        /**
         * Content iterator
         */
        UString::Iterator _contentIterator;

        /**
         * Current position in source
         */
        I64 _currentPosition;
    };

}

#endif //GSLANGUAGE_GS_LEXER_H
