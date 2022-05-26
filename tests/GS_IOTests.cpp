#include <gtest/gtest.h>

#include <IO/IO.h>

using namespace GSLanguageCompiler;

class IOTest : public ::testing::Test {
public:

    IOTest()
            : _textStream(nullptr) {}

protected:

    Void SetUp() override {
        _textStream = new IO::GS_TextStream(_inputString);
    }

    Void TearDown() override {
        delete _textStream;
    }

protected:

    UString _inputString = "func main() {\n\tvar a = 10\n}"_us;

    Ptr<IO::GS_TextStream> _textStream;
};

TEST_F(IOTest, TextStream) {
    for (auto &inputSymbol : _inputString) {
        auto streamSymbol = _textStream->CurrentSymbol();

        ASSERT_EQ(inputSymbol, streamSymbol);

        _textStream->NextSymbol();
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
