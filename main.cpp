#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
#include <Parser/GS_Parser.h>
#include <CodeGenerator/GS_CompilerUnit.h>
#include <CodeGenerator/GS_CodeGenerationPass.h>

using namespace GSLanguageCompiler;

Reader::GS_Code read(const String &filename) {
    IFStream stream;
    stream.open(filename);

    Reader::GS_Reader reader(std::move(stream));

    return reader.read();
}

Lexer::GSTokenArray tokenize(Reader::GS_Code code) {
    Lexer::GS_Lexer lexer(std::move(code));

    return lexer.tokenize();
}

AST::GSDeclarationPtrArray parse(Lexer::GS_TokenStream stream) {
    Parser::GS_Parser parser(stream);

    return parser.parse();
}

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/GS_TranslationUnit.h>

I32 main() {
    auto globalScope = std::make_shared<AST::GS_Scope>(nullptr);

    auto functionScope = std::make_shared<AST::GS_Scope>(globalScope);

    auto expression = std::make_shared<AST::GS_ConstantExpression>(std::make_shared<AST::GS_I32Value>(1));

    AST::GSStatementPtrArray body = {
            std::make_shared<AST::GS_VariableDeclarationStatement>("a", std::make_shared<AST::GS_I32Type>(), expression, functionScope)
    };

    AST::GSNodePtrArray nodes = {
            std::make_shared<AST::GS_FunctionDeclaration>("a", body)
    };

    AST::GS_TranslationUnit translationUnit(nodes, nullptr);

    try {
        auto code = read("../test.gs");

        auto tokens = tokenize(code);

        auto tokenIterator = tokens.begin();

        auto tokenStream = Lexer::GS_TokenStream(tokenIterator);

        auto ast = parse(tokenStream);

        CodeGenerator::GS_CompilerUnit compilerUnit("GSModule");

        CodeGenerator::GS_CodeGenerationPass pass(&compilerUnit);

        pass.runForDeclarations(ast);

        compilerUnit.getModule().print(llvm::errs(), nullptr);
    } catch (std::exception &exception) {
        std::cerr << exception.what() << std::endl;

        return 1;
    }

    return 0;
}

//#include <Starter/GS_Starter.h>

/**
 * Main function in GSLanguageCompiler
 * @param argc Arguments count
 * @param argv Arguments array
 * @return Status number for operation system
 */
//GSInt main(GSInt argc, GSChar *argv[]) {
//    return Starter::GS_Starter::start(argc, argv);
//}
