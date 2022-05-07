#include <Driver/Driver.h>

using namespace GSLanguageCompiler;

/**
 * Entry point for GSLanguageCompiler
 * @return Compiler result
 */
I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    return Driver::GS_Compiler::Start(argc, argv);
}

#include <AST/AST.h>

/**
 * Simple example of creating translation unit with AST builder
 * @return Translation unit declaration ptr
 */
AST::GSTranslationUnitDeclarationPtr CreateUnit() {
    // TODO create 'examples' dir and add this example

    /**
     *
     * main.gs
     *
     * func main() {
     *
     * }
     *
     */

    // create AST builder
    auto Builder = AST::GS_ASTBuilder::Create();

    // create 'main' translation unit declaration
    auto Unit = Builder->CreateTranslationUnitDeclaration("main");

    // create 'main' function signature
    auto FunctionSignature = Builder->CreateFunctionSignature(Builder->CreateI32Type());

    // create 'main' function
    auto Function = Builder->CreateFunctionDeclaration("main", FunctionSignature);

    // adding 'main' function to translation unit declaration
    Unit->AddNode(Function);

    // return translation unit declaration
    return Unit;
}
