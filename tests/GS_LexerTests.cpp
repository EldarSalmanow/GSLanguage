#include <gtest/gtest.h>

#include <Lexer/Lexer.h>

using namespace GSLanguageCompiler;

class LexerTest : public ::testing::Test {
public:

    LexerTest()
            : _inputContent("var a = 10"), _validTokens({
                Lexer::GS_Token::Create(Lexer::TokenType::KeywordVar),
                Lexer::GS_Token::Create(Lexer::TokenType::Identifier, "a"_us),
                Lexer::GS_Token::Create(Lexer::TokenType::SymbolEq),
                Lexer::GS_Token::Create(Lexer::TokenType::LiteralNumber, "10"_us),
                Lexer::GS_Token::Create(Lexer::TokenType::EndOfFile)
            }) {}

protected:

    Void SetUp() override {
        auto context = Driver::GS_Context::Create();

        auto compilationUnit = Driver::GS_CompilationUnit::Create(IO::GS_Source::CreateString(_inputContent), context);

        _tokens = Lexer::GS_Lexer::Create(context).Tokenize(*compilationUnit);
    }

protected:

    UString _inputContent;

    Lexer::GSTokenArray _validTokens;

    Lexer::GSTokenArray _tokens;
};

TEST_F(LexerTest, Tokenizing) {
    ASSERT_EQ(_tokens.size(), _validTokens.size());

    for (U64 index = 0; index < _tokens.size(); ++index) {
        ASSERT_EQ(_tokens[index].GetType(), _validTokens[index].GetType());
        ASSERT_EQ(_tokens[index].GetValue(), _validTokens[index].GetValue());
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
