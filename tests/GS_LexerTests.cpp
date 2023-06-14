#include <gtest/gtest.h>

#include <Lexer/Lexer.h>

using namespace GSLanguageCompiler;

TEST(LexerTest, Tokenizing) {
    auto session = Driver::GS_Session::Create();

    auto code = "func main() {\n"
                "    println(\"Hello, World!\")\n"
                "}"_us;

    Lexer::GSTokenArray validTokens = {
            Lexer::GS_Token::Create(Lexer::TokenType::KeywordFunc),
            Lexer::GS_Token::Create(Lexer::TokenType::Identifier, "main"_us),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolLeftParen),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolRightParen),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolLeftBrace),
            Lexer::GS_Token::Create(Lexer::TokenType::Identifier, "println"),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolLeftParen),
            Lexer::GS_Token::Create(Lexer::TokenType::LiteralString, "Hello, World!"),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolRightParen),
            Lexer::GS_Token::Create(Lexer::TokenType::SymbolRightBrace),
            Lexer::GS_Token::Create(Lexer::TokenType::EndOfFile)
    };

    auto source = session->AddStringSource(code);

    auto lexer = Lexer::GS_Lexer::Create(*session,
                                         source);

    auto tokens = lexer.Tokenize().GetTokens();

    ASSERT_EQ(tokens.size(), validTokens.size());

    for (U64 index = 0; index < tokens.size(); ++index) {
        EXPECT_EQ(tokens[index].GetType(), validTokens[index].GetType());
        EXPECT_EQ(tokens[index].GetValue(), validTokens[index].GetValue());
//        EXPECT_EQ(tokens[index].GetLocationRange(), validTokens[index].GetLocationRange());
    }
}

I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
