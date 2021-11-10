#include <gtest/gtest.h>

#include <Reader/GS_Reader.h>

using namespace GSLanguageCompiler;

class ReaderTest : public ::testing::Test {
public:

    ReaderTest()
            : _code(nullptr) {}

protected:

    Void SetUp() override {
        std::stringstream stream(_inputString);

        auto reader = new Reader::GS_Reader(&stream);

        _code = new Reader::GS_Code(reader->read());
    }

    Void TearDown() override {
        delete _code;
    }

protected:

    String _inputString = "func main() {\nprint(\"Hello, World!\")\n}";

    Reader::GS_Code *_code;
};

TEST_F(ReaderTest, Size) {
    I32 codeSize = 0;

    for (auto &line : *_code) {
        for (auto &symbol : line) {
            ++codeSize;
        }
    }

    ASSERT_EQ(_inputString.size(), codeSize);
}

TEST_F(ReaderTest, Symbols) {
    String codeAsString;

    for (auto &line : *_code) {
        for (auto &symbol : line) {
            codeAsString += symbol.getSymbol();
        }
    }

    ASSERT_EQ(_inputString, codeAsString);
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
