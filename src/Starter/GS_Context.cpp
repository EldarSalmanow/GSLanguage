#include <GS_Context.h>

namespace GSLanguageCompiler::Starter {

    GS_Arguments::GS_Arguments() = default;

    GSString GS_Arguments::getInputFilename() {
        return _inputFilename;
    }

    GSVoid GS_Arguments::setInputFilename(GSString inputFilename) {
        _inputFilename = std::move(inputFilename);
    }

    GS_Context::GS_Context() = default;

    GSArgumentsPtr GS_Context::getArguments() {
        return _arguments;
    }

    GSVoid GS_Context::setArguments(GSArgumentsPtr arguments) {
        _arguments = std::move(arguments);
    }

    Reader::GSText GS_Context::getInputCode() {
        return _inputText;
    }

    GSVoid GS_Context::setInputCode(Reader::GS_Code inputText) {
        _inputText = std::move(inputText);
    }

    Lexer::GSTokenArray GS_Context::getTokens() {
        return _tokens;
    }

    GSVoid GS_Context::setTokens(Lexer::GSTokenArray tokens) {
        _tokens = std::move(tokens);
    }

    Parser::GSNodePtr GS_Context::getRootNode() {
        return _rootNode;
    }

    GSVoid GS_Context::setRootNode(Parser::GSNodePtr rootNode) {
        _rootNode = std::move(rootNode);
    }

    Semantic::GSSemanticPassPtrArray GS_Context::getSemanticPasses() {
        return _semanticPasses;
    }

    GSVoid GS_Context::setSemanticPasses(Semantic::GSSemanticPassPtrArray semanticPasses) {
        _semanticPasses = std::move(semanticPasses);
    }

    Semantic::GSTableOfVariablesPtr GS_Context::getTableOfVariables() {
        return _tableOfVariables;
    }

    GSVoid GS_Context::setTableOfVariables(Semantic::GSTableOfVariablesPtr tableOfVariables) {
        _tableOfVariables = std::move(tableOfVariables);
    }

    Optimizer::GSOptimizerPassPtrArray GS_Context::getOptimizerPasses() {
        return _optimizerPasses;
    }

    GSVoid GS_Context::setOptimizerPasses(Optimizer::GSOptimizerPassPtrArray optimizerPasses) {
        _optimizerPasses = std::move(optimizerPasses);
    }

    Parser::GSNodePtr GS_Context::getOptimizedRootNode() {
        return _optimizedRootNode;
    }

    GSVoid GS_Context::setOptimizedRootNode(Parser::GSNodePtr optimizedRootNode) {
        _optimizedRootNode = std::move(optimizedRootNode);
    }

    std::shared_ptr<llvm::LLVMContext> GS_Context::getLLVMContext() {
        return _llvmContext;
    }

    GSVoid GS_Context::setLLVMContext(std::shared_ptr<llvm::LLVMContext> llvmContext) {
        _llvmContext = std::move(llvmContext);
    }

    std::shared_ptr<llvm::Module> GS_Context::getLLVMModule() {
        return _llvmModule;
    }

    GSVoid GS_Context::setLLVMModule(std::shared_ptr<llvm::Module> llvmModule) {
        _llvmModule = std::move(llvmModule);
    }

}
