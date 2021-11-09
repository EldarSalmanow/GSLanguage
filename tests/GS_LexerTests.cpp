#include <gtest/gtest.h>

#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>

using namespace GSLanguageCompiler;

Reader::GS_Code makeCodeFromString(const String &string) {
    std::stringstream stream(string);

    Reader::GS_Reader reader(&stream);

    return reader.read();
}

Lexer::GSTokenArray tokenize(Reader::GS_Code code) {
    Lexer::GS_Lexer lexer(std::move(code));

    return lexer.tokenize();
}

inline String STRING_CODE = "var a = 10\n";

inline Reader::GS_Code CODE = makeCodeFromString(STRING_CODE);

inline Lexer::GSTokenArray TOKENS = tokenize(CODE);

inline Lexer::GSTokenArray VALID_TOKENS = {
        Lexer::GS_Token(Lexer::TokenType::KeywordVar, Lexer::GS_Position("var a = 10\n", 1, 1)),
        Lexer::GS_Token(Lexer::TokenType::Identifier, "a", Lexer::GS_Position("var a = 10\n", 1, 5)),
        Lexer::GS_Token(Lexer::TokenType::SymbolEq, Lexer::GS_Position("var a = 10\n", 1, 7)),
        Lexer::GS_Token(Lexer::TokenType::LiteralNumber, "10", Lexer::GS_Position("var a = 10\n", 1, 9)),
        Lexer::GS_Token(Lexer::TokenType::EndOfFile, Lexer::GS_Position()),
};

TEST(Lexer, TokenTypes) {
    for (I32 index = 0; index < TOKENS.size(); ++index) {
        ASSERT_EQ(TOKENS[index].getType(), VALID_TOKENS[index].getType());
    }
}

TEST(Lexer, Values) {
    for (I32 index = 0; index < TOKENS.size(); ++index) {
        ASSERT_EQ(TOKENS[index].getValue(), VALID_TOKENS[index].getValue());
    }
}

String tokenTypeToString(const Lexer::TokenType &type)  {
    switch (type) {
        case Lexer::TokenType::EndOfFile:
            return "EndOfFile";
        case Lexer::TokenType::Identifier:
            return "Identifier";
        case Lexer::TokenType::LiteralNumber:
            return "LiteralNumber";
        case Lexer::TokenType::KeywordVar:
            return "KeywordVar";
        case Lexer::TokenType::KeywordFunc:
            return "KeywordFunc";
        case Lexer::TokenType::SymbolLeftParen:
            return "SymbolLeftParen";
        case Lexer::TokenType::SymbolRightParen:
            return "SymbolRightParen";
        case Lexer::TokenType::SymbolLeftBrace:
            return "SymbolLeftBrace";
        case Lexer::TokenType::SymbolRightBrace:
            return "SymbolRightBrace";
        case Lexer::TokenType::SymbolDoubleQuotes:
            return "SymbolDoubleQuotes";
        case Lexer::TokenType::SymbolColon:
            return "SymbolColon";
        case Lexer::TokenType::SymbolComma:
            return "SymbolComma";
        case Lexer::TokenType::SymbolPlus:
            return "SymbolPlus";
        case Lexer::TokenType::SymbolMinus:
            return "SymbolMinus";
        case Lexer::TokenType::SymbolStar:
            return "SymbolStar";
        case Lexer::TokenType::SymbolSlash:
            return "SymbolSlash";
        case Lexer::TokenType::SymbolEq:
            return "SymbolEq";
    }

    return "<invalid token type>";
}

TEST(Lexer, Positions) {
    for (I32 index = 0; index < TOKENS.size(); ++index) {
//        auto tokenPosition = TOKENS[index].getPosition();

        auto token = TOKENS[index];

        std::cout
        << "TokenType: " << tokenTypeToString(token.getType())
        << " Value: " << token.getValue()
        << " Position:"
        << " Code: " << token.getPosition().getCode()
        << " Line: " << token.getPosition().getLine()
        << " Column: " << token.getPosition().getColumn()
        << std::endl;
//        auto validTokenPosition = VALID_TOKENS[index].getPosition();

//        ASSERT_EQ(tokenPosition.getCode(), validTokenPosition.getCode());
//        ASSERT_EQ(tokenPosition.getLine(), validTokenPosition.getLine());
//        ASSERT_EQ(tokenPosition.getColumn(), validTokenPosition.getColumn());
    }
}

I32 main() {
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
