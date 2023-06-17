#include <gtest/gtest.h>

#include <IO/IO.h>

using namespace GSLanguageCompiler;

TEST(StdIOStreamManagerTest, DefaultStream) {
    auto stdIOStreamManager = IO::GS_StdIOStreamManager::Create();

    EXPECT_EQ(&stdIOStreamManager->In(),  &std::cin);
    EXPECT_EQ(&stdIOStreamManager->Out(), &std::cout);
    EXPECT_EQ(&stdIOStreamManager->Err(), &std::cerr);
    EXPECT_EQ(&stdIOStreamManager->Log(), &std::clog);
}

TEST(ReaderTest, Reading) {
    auto input = "func main() {\n"
                 "    println(\"Hello, World!\")\n"
                 "}"_us;

    std::stringstream inputStream(input.AsUTF8());

    auto reader = IO::GS_Reader::Create(inputStream);

    auto output = reader.Read();

    ASSERT_EQ(output.Size(), input.Size());

    for (U64 index = 0; index < output.Size(); ++index) {
        EXPECT_EQ(output[index], input[index]);
    }
}

TEST(SourceTest, ByteSourceLocationComparing) {
    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create();
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create();

        EXPECT_EQ(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1);

        EXPECT_EQ(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1, 123);

        EXPECT_EQ(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create();

        EXPECT_NE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create();
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1);

        EXPECT_NE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(2);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1);

        EXPECT_NE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(2, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1);

        EXPECT_NE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(2, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1, 234);

        EXPECT_NE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1, 234);

        EXPECT_NE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create();
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create();

        EXPECT_EQ((byteSourceLocation1 <=> byteSourceLocation2), std::partial_ordering::unordered);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create();

        EXPECT_EQ((byteSourceLocation1 <=> byteSourceLocation2), std::partial_ordering::unordered);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(1);

        EXPECT_GE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_GE(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(2);

        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(2);

        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(2, 234);

        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
    }

    {
        auto byteSourceLocation1 = IO::GS_SourceLocation::Create(1, 123);
        auto byteSourceLocation2 = IO::GS_SourceLocation::Create(2, 123);

        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LE(byteSourceLocation1, byteSourceLocation2);
        EXPECT_LT(byteSourceLocation1, byteSourceLocation2);
    }
}

TEST(SourceTest, GetCodeInRange) {
//    {
//        auto sourceBuffer = IO::GS_SourceBuffer::Create("func main() {\n"
//                                                        "    1 + 1\n"
//                                                        "\n"
//                                                        "    var string String = input()\n"
//                                                        "}");
//
//        auto code = sourceBuffer.GetCodeInRange(IO::GSSourceRange::Create(IO::GS_SourceLocation::Create(19),
//                                                                          IO::GS_SourceLocation::Create(24)));
//
//        ASSERT_EQ(code, "1 + 1"_us);
//    }
//
//    {
//        auto sourceBuffer = IO::GS_SourceBuffer::Create("func main() {\n"
//                                                        "    1 + 1\n"
//                                                        "\n"
//                                                        "    var string String = input()\n"
//                                                        "}");
//
//        auto code = sourceBuffer.GetCodeInRange(IO::GSLineColumnSourceRange::Create(IO::GS_LineColumnSourceLocation::Create(2, 5),
//                                                                                    IO::GS_LineColumnSourceLocation::Create(2, 10)));
//
//        ASSERT_EQ(code, "1 + 1"_us);
//    }
}

// TODO: update
TEST(MessageTest, S) {
//    auto SS = IO::GS_StdIOStreamManager::Create();
//    auto SM = IO::GS_SourceManager::Create();
//    auto MSM = IO::GS_MessageStreamManager::Create(*SS,
//                                                   *SM);
//
//    auto &source_ = SM->AddCustomSource("func main() {\n"
//                                        "    println(\"Hello, World!\"\n"
//                                        "}",
//                                        "test.gs");
//
//    auto SH = SM->GetCustomSource("test.gs")->GetHash();
//
//    MSM->Out() << IO::GS_MessageBuilder::Create().Text("Missed ')' in function calling expression!")
//            .Error()
//            .Location(IO::ToSourceLocation<IO::GS_SourceLocation>(IO::GS_LineColumnSourceLocation::Create(2, 28, SH), source_))
//            .Message();
//    MSM->Out() << IO::GS_MessageBuilder::Create().Text("Missed ')' in function calling expression!")
//            .Note()
//            .Location(IO::ToSourceLocation<IO::GS_SourceLocation>(IO::GS_LineColumnSourceLocation::Create(2, 28, SH), source_))
//            .Message();
//    MSM->Out() << IO::GS_MessageBuilder::Create().Text("Missed ')' in function calling expression!")
//            .Warning()
//            .Location(IO::ToSourceLocation<IO::GS_SourceLocation>(IO::GS_LineColumnSourceLocation::Create(2, 28, SH), source_))
//            .Message();
//    MSM->Out() << IO::GS_MessageBuilder::Create().Text("Missed ')' in function calling expression!")
//            .Fatal()
//            .Location(IO::ToSourceLocation<IO::GS_SourceLocation>(IO::GS_LineColumnSourceLocation::Create(2, 28, SH), source_))
//            .Message();
}

I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
