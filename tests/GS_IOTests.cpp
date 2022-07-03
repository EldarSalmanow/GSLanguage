#include <gtest/gtest.h>

#include <IO/IO.h>

using namespace GSLanguageCompiler;

class IOTest : public ::testing::Test {
public:

    IOTest()
            : _validString("func main() {\n\tvar a = 10\n}"_us) {}

protected:

    Void SetUp() override {
        _string = IO::GS_Reader(IO::GS_InStringStream::Create(_validString)).Read();
    }

protected:

    UString _validString;

    UString _string;
};

TEST_F(IOTest, Reading) {
    ASSERT_EQ(_string.Size(), _validString.Size());

    for (U64 index = 0; index < _string.Size(); ++index) {
        ASSERT_EQ(_string[index], _validString[index]);
    }
}

I32 main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
