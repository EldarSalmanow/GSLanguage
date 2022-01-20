#include <gtest/gtest.h>

#include <Reader/GS_TextStream.h>
#include <Lexer/GS_TokenStream.h>

using namespace GSLanguageCompiler;

class LexerTest : public ::testing::Test {
public:

    LexerTest()
            : _inputStream(nullptr), _reader(nullptr), _textStream(nullptr), _lexer(nullptr), _tokenStream(nullptr) {}

protected:

    Void SetUp() override {
        _inputStream = new std::stringstream("var a = 10");

        _reader = new Reader::GS_Reader(_inputStream);

        _textStream = new Reader::GS_TextStream(*_reader);

        _lexer = new Lexer::GS_Lexer(*_textStream);

        _tokenStream = new Lexer::GS_TokenStream(*_lexer);
    }

    Void TearDown() override {
        delete _inputStream;

        delete _reader;

        delete _textStream;

        delete _lexer;

        delete _tokenStream;
    }

protected:

    Reader::StreamT _inputStream;

    Reader::GS_Reader *_reader;

    Reader::GS_TextStream *_textStream;

    Lexer::GS_Lexer *_lexer;

    Lexer::GS_TokenStream *_tokenStream;

    Lexer::GSTokenArray _validTokens = {
            Lexer::GS_Token(Lexer::TokenType::KeywordVar),
            Lexer::GS_Token(Lexer::TokenType::SymbolSpace),
            Lexer::GS_Token(Lexer::TokenType::Identifier, "a"),
            Lexer::GS_Token(Lexer::TokenType::SymbolSpace),
            Lexer::GS_Token(Lexer::TokenType::SymbolEq),
            Lexer::GS_Token(Lexer::TokenType::SymbolSpace),
            Lexer::GS_Token(Lexer::TokenType::LiteralNumber, "10"),
            Lexer::GS_Token(Lexer::TokenType::EndOfFile)
    };
};

TEST_F(LexerTest, Valid) {
    Lexer::GS_Token token = _tokenStream->getToken();

    for (I32 index = 0; token.getType() != Lexer::TokenType::EndOfFile ; ++index, token = _tokenStream->getToken()) {
        ASSERT_EQ(token.getType(), _validTokens[index].getType());
        ASSERT_EQ(token.getValue(), _validTokens[index].getValue());
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
