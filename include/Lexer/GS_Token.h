#ifndef GSLANGUAGE_GS_TOKEN_H
#define GSLANGUAGE_GS_TOKEN_H

#include <GSCrossPlatform/GS_CrossPlatform.h>

#include <Lexer/GS_Keywords.h>

namespace GSLanguageCompiler::Lexer {

    class GS_Token {
    public:

        explicit GS_Token(TokenType type);

    public:

        TokenType getTokenType() const;

    private:

        TokenType _type;
    };

    class GS_ValueToken : public GS_Token {
    public:

        GS_ValueToken(TokenType type, UString value);

    public:

        UString getValue() const;

    private:

        UString _value;
    };

    /**
     * Token ptr type
     */
    using GSTokenPtr = SharedPtr<GS_Token>;

    /**
     * Token ptr array type
     */
    using GSTokenPtrArray = Vector<GSTokenPtr>;

    /**
     * Token ptr array iterator type
     */
    using GSTokenPtrArrayIterator = GSTokenPtrArray::iterator;

}

#endif //GSLANGUAGE_GS_TOKEN_H
