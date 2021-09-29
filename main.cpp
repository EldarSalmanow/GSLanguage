#include <Reader/GS_Reader.h>
#include <Lexer/GS_Lexer.h>
//#include <Parser/GS_Parser.h>
//#include <Parser/Visitors/GS_PrintVisitor.h>
//#include <Semantic/GS_Semantic.h>
//#include <Optimizer/GS_Optimizer.h>
//#include <CodeGenerator/GS_CodeGenerator.h>

using namespace GSLanguageCompiler;

//Starter::GSContextPtr run(GSString filename, Semantic::GSSemanticPassPtrArray semanticPasses, Optimizer::GSOptimizerPassPtrArray optimizerPasses) {
//    auto context = std::make_shared<Starter::GS_Context>();
//
//    auto arguments = std::make_shared<Starter::GS_Arguments>();
//    arguments->setInputFilename(std::move(filename));
//
//    context->setArguments(arguments);
//
//    context->setSemanticPasses(std::move(semanticPasses));
//
//    auto tableOfVariables = std::make_shared<Semantic::GS_TableOfVariables>();
//
//    context->setTableOfVariables(tableOfVariables);
//
//    context->setOptimizerPasses(std::move(optimizerPasses));
//
//    auto llvmContext = std::make_shared<llvm::LLVMContext>();
//
//    context->setLLVMContext(llvmContext);
//
//    auto llvmModule = std::make_shared<llvm::Module>(filename, *llvmContext);
//
//    context->setLLVMModule(llvmModule);
//
//    std::vector<Starter::GSRunnablePtr> runnable;
//
//    runnable.emplace_back(std::make_shared<Reader::GS_Reader>());
//    runnable.emplace_back(std::make_shared<Lexer::GS_Lexer>());
//    runnable.emplace_back(std::make_shared<Parser::GS_Parser>());
//    runnable.emplace_back(std::make_shared<Semantic::GS_Semantic>());
//    runnable.emplace_back(std::make_shared<Optimizer::GS_Optimizer>());
//    runnable.emplace_back(std::make_shared<CodeGenerator::GS_CodeGenerator>());
//
//    for (auto &pass : runnable) {
//        pass->run(context);
//    }
//
//    return context;
//}

//GSVoid debug(Starter::GSContextPtr &context) {
//    for (auto &line : context->getInputCode()) {
//        std::cout << line;
//    }
//
//    std::cout << std::endl;
//
//    for (auto &token : context->getTokens()) {
//        std::cout
//        << "Type: "    << Lexer::tokenTypeToString[token.getType()]
//        << " Data: "   << token.getValue()
//        << " Line: "   << token.getPosition().getLine()
//        << " Column: " << token.getPosition().getColumn()
//        << std::endl;
//    }
//
//    Parser::GS_PrintVisitor visitor;
//
//    context->getRootNode()->accept(&visitor);
//
//    std::cout << std::endl;
//
//    for (auto &[declaration, expression] : context->getTableOfVariables()->getVariables()) {
//        std::cout
//        << "Name: "  << declaration->getName()
//        << " Type: " << Parser::valueTypeToString[declaration->getType()]
//        << std::endl;
//    }
//
//    std::cout << std::endl;
//
//    context->getOptimizedRootNode()->accept(&visitor);
//
//    std::cout << std::endl;
//
//    context->getLLVMModule()->print(llvm::errs(), nullptr);
//}

Reader::GS_Code read(String filename) {
    IFStream stream;

    Reader::GS_Reader reader(std::move(stream), std::move(filename));

    return reader.read();
}

Lexer::GSTokenArray tokenize(Reader::GS_Code code) {
    Lexer::GS_Lexer lexer(std::move(code));

    return lexer.tokenize();
}

int main() {
    auto code = read("../test.gs");

    auto tokens = tokenize(code);

    for (auto &token : tokens) {
        std::cout << Lexer::tokenTypeToString[token.getType()] << std::endl;
    }

//    for (auto &line : code) {
//        for (auto &symbol : line) {
//            auto charSymbol = symbol.getSymbol();
//
//            COut << charSymbol << " : " << (I32) charSymbol << std::endl;
//        }
//    }

//    auto filename = "../test.gs";
//
//    Semantic::GSSemanticPassPtrArray semanticPasses = {
//            std::make_shared<Semantic::GS_TypePlaceholderPass>(),
//            std::make_shared<Semantic::GS_TypeCheckerPass>(),
//            std::make_shared<Semantic::GS_VariablesPlaceholderPass>()
//    };
//
//    Optimizer::GSOptimizerPassPtrArray optimizerPasses = {
//            std::make_shared<Optimizer::GS_ConstantFoldingPass>()
//    };
//
//    auto context = run(filename, semanticPasses, optimizerPasses);
//
//    debug(context);

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
