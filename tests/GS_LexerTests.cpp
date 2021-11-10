#include <gtest/gtest.h>

#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>

using namespace GSLanguageCompiler;

class LexerTest : public ::testing::Test {
public:

    LexerTest()
            : _code(nullptr) {}

protected:

    Void SetUp() override {
        _code = new Reader::GS_Code(_makeCodeFromString(_inputString));

        Lexer::GS_Lexer lexer(*_code);

        _tokens = lexer.tokenize();
    }

    Void TearDown() override {
        delete _code;
    }

private:

    Reader::GS_Code _makeCodeFromString(String input) {
        std::stringstream stream(std::move(input));

        Reader::GS_Reader reader(&stream);

        return reader.read();
    }

protected:

    String _inputString = "var a = 10";

    Reader::GS_Code *_code;

    Lexer::GSTokenArray _tokens;

    Lexer::GSTokenArray _validTokens = {
            Lexer::GS_Token(Lexer::TokenType::KeywordVar, Lexer::GS_Position("var a = 10", 1, 1)),
            Lexer::GS_Token(Lexer::TokenType::Identifier, "a", Lexer::GS_Position("var a = 10", 1, 5)),
            Lexer::GS_Token(Lexer::TokenType::SymbolEq, Lexer::GS_Position("var a = 10", 1, 7)),
            Lexer::GS_Token(Lexer::TokenType::LiteralNumber, "10", Lexer::GS_Position("var a = 10", 1, 9)),
            Lexer::GS_Token(Lexer::TokenType::EndOfFile, Lexer::GS_Position())
    };
};

TEST_F(LexerTest, Size) {
    ASSERT_EQ(_validTokens.size(), _tokens.size());
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
