#include <gtest/gtest.h>

#include <Lexer/Lexer.h>

using namespace GSLanguageCompiler;

class LexerTest : public ::testing::Test {
public:

    LexerTest()
            : _textStream(nullptr), _tokenStream(nullptr) {}

protected:

    Void SetUp() override {
        _textStream = new IO::GS_TextStream(IO::GS_TextStream::Create("var a = 10"));

        _tokenStream = new Lexer::GS_TokenStream(Lexer::GS_Lexer::Create(*_textStream).CreateStream());
    }

    Void TearDown() override {
        delete _textStream;

        delete _tokenStream;
    }

protected:

    Lexer::GSTokenArray _validTokens = {
            Lexer::GS_Token::Create(Lexer::TokenType::KeywordVar),
            Lexer::GS_Token::Create(Lexer::TokenType::Identifier, "a"_us),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolEq),
            Lexer::GS_Token::Create(Lexer::TokenType::LiteralNumber, "10"_us),
            Lexer::GS_Token::Create(Lexer::TokenType::EndOfFile)
    };

    Ptr<IO::GS_TextStream> _textStream;

    Ptr<Lexer::GS_TokenStream> _tokenStream;
};

TEST_F(LexerTest, Tokenizing) {
    for (auto &inputToken : _validTokens) {
        auto streamToken = _tokenStream->CurrentToken();

        ASSERT_EQ(inputToken.GetType(), streamToken.GetType());
        ASSERT_EQ(inputToken.GetValue(), streamToken.GetValue());

        _tokenStream->NextToken();
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
