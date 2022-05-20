#include <gtest/gtest.h>

#include <Lexer/Lexer.h>

using namespace GSLanguageCompiler;

class LexerTest : public ::testing::Test {
public:

    LexerTest()
            : _tokenStream(nullptr) {}

protected:

    Void SetUp() override {
        _tokenStream = new Lexer::GS_TokenStream(_inputTokens);
    }

    Void TearDown() override {
        delete _tokenStream;
    }

protected:

    Lexer::GSTokenArray _inputTokens = {
            Lexer::GS_Token::Create(Lexer::TokenType::KeywordVar),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolSpace),
            Lexer::GS_Token::Create(Lexer::TokenType::Identifier, "a"),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolEq),
            Lexer::GS_Token::Create(Lexer::TokenType::LiteralNumber, "10"),
            Lexer::GS_Token::Create(Lexer::TokenType::EndOfFile)
    };

    Lexer::GS_TokenStream *_tokenStream;
};

TEST_F(LexerTest, TokenStream) {
    for (auto &inputToken : _inputTokens) {
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
