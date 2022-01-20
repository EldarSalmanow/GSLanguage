#include <gtest/gtest.h>

#include <Reader/GS_TextStream.h>

using namespace GSLanguageCompiler;

class ReaderTest : public ::testing::Test {
public:

    ReaderTest()
            : _inputStream(nullptr), _reader(nullptr),  _textStream(nullptr) {}

protected:

    Void SetUp() override {
        _inputStream = new UFileStream();

        _reader = new Reader::GS_Reader(_inputStream);

        _textStream = new Reader::GS_TextStream(*_reader);
    }

    Void TearDown() override {
        delete _inputStream;

        delete _reader;

        delete _textStream;
    }

protected:

    String _inputString = "func main() {\nprint(\"Hello, World!\")\n}";

    Reader::StreamT *_inputStream;

    Reader::GS_Reader *_reader;

    Reader::GS_TextStream *_textStream;
};

TEST_F(ReaderTest, Symbols) {
    auto symbol = _textStream->getSymbol();

    for (I32 index = 0; symbol != EOF; ++index, symbol = _textStream->getSymbol()) {
        ASSERT_EQ(_inputString[index], symbol);
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
