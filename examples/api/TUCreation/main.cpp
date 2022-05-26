#include <AST/AST.h>

#include <Debug/Debug.h>

/**
 * Simple example of creating translation unit with AST builder
 * @return Translation unit declaration ptr
 */
AST::GSTranslationUnitDeclarationPtr CreateUnit() {
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

I32 main(I32 argc, Ptr<Ptr<C8>> argv) {
    // create translation unit
    auto unit = CreateUnit();

    // dump AST node to console
    Debug::DumpAST(unit);

    return 0;
}
