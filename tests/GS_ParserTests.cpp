#include <gtest/gtest.h>

#include <Parser/Parser.h>

using namespace GSLanguageCompiler;

TEST(ParserTest, Parsing) {
    auto session = Driver::GS_Session::Create();

    auto code = "func main() {\n"
                "   println(\"Hello, World!\")\n"
                "}";

    auto program = Parser::ParseProgramFromString(*session,
                                                  code);
    ASSERT_EQ(program->GetDeclarationType(), AST::DeclarationType::TranslationUnitDeclaration);

    auto nodes = program->GetNodes();
    ASSERT_EQ(nodes.size(), 1);

    auto functionDeclaration = AST::ToDeclaration<AST::GS_FunctionDeclaration>(nodes[0]);
    ASSERT_NE(functionDeclaration, nullptr);
    ASSERT_EQ(functionDeclaration->GetName(), "main"_us);

    auto functionSignature = functionDeclaration->GetSignature();
    ASSERT_EQ(functionSignature.GetParams().size(), 0);
//    ASSERT_EQ(functionSignature.GetReturnType()->GetName(), ""); TODO
    ASSERT_EQ(functionSignature.GetQualifiers().IsExtern(), false);

    auto body = functionDeclaration->GetBody();
    ASSERT_EQ(body.size(), 1);

    auto expressionStatement = AST::ToStatement<AST::GS_ExpressionStatement>(body[0]);
    ASSERT_NE(expressionStatement, nullptr);

    auto functionCallingExpression = AST::ToExpression<AST::GS_FunctionCallingExpression>(expressionStatement->GetExpression());
    ASSERT_NE(functionCallingExpression, nullptr);
    ASSERT_EQ(functionCallingExpression->GetName(), "println"_us);

    auto arguments = functionCallingExpression->GetArguments();
    ASSERT_EQ(arguments.size(), 1);

    auto constantExpression = AST::ToExpression<AST::GS_LiteralExpression>(arguments[0]);
    ASSERT_NE(constantExpression, nullptr);

    auto value = constantExpression->GetValue();
    auto type = value->GetType();
    ASSERT_EQ(type->GetType(), Semantic::TypeType::String);
    ASSERT_EQ(type->GetName(), "String"_us);

    auto stringValue = AST::ToValue<AST::GS_StringValue>(value);
    ASSERT_EQ(stringValue->GetStringValue(), "Hello, World!");
}

I32 main(I32 argc, Ptr<Ptr<C>> argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
