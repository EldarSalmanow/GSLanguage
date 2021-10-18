#include <llvm/IR/Verifier.h>

#include <GS_CodeGenVisitor.h>

#include <AST/GS_IncludeNodes.h>

#include <Semantic/GS_TableOfVariables.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeGenVisitor::GS_LLVMCodeGenVisitor() = default;

    GSVoid GS_LLVMCodeGenVisitor::setup(Starter::GSContextPtr &context) {
        _context = context;
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_RootNode *rootNode) {
        _llvmContext = _context->getLLVMContext();
        _llvmModule = _context->getLLVMModule();

        _llvmBuilder = std::make_shared<llvm::IRBuilder<>>(*_llvmContext);

        rootNode->getNode()->accept(this);

        return nullptr;
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_BlockNode *blockNode) {
        auto function = llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getInt32Ty(*_llvmContext), false),
                                               llvm::Function::ExternalLinkage,
                                               "_Fmain4I",
                                               *_llvmModule);

        auto block = llvm::BasicBlock::Create(*_llvmContext, "_entry", function);

        _llvmBuilder->SetInsertPoint(block);

        for (auto &node : blockNode->getNodes()) {
            node->accept(this);
        }

        _llvmBuilder->CreateRet(llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(*_llvmContext), 0));

        llvm::verifyFunction(*function);

//        llvm::legacy::FunctionPassManager functionPassManager(&_module);
//
//        functionPassManager.add(llvm::createInstructionCombiningPass());
//
//        functionPassManager.run(*function);

//        _llvmModule.print(llvm::errs(), nullptr);

        return nullptr;
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_ValueNode *valueNode) {
        auto value = valueNode->getValue();

        switch (value->getType()) {
            case Parser::ValueType::VOID:
                Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                               "Can`t generate void value type!");

                Exceptions::errorHandler.throw_();

                break;
            case Parser::ValueType::INT:
                return llvm::ConstantInt::get(*_llvmContext, llvm::APInt(32, value->getData<GSInt>()));
            case Parser::ValueType::STRING:
                Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                               "Can`t generate string value type!");

                Exceptions::errorHandler.throw_();

                break;
        }

        return nullptr;
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_UnaryNode *unaryNode) {
        auto value = unaryNode->getNode()->accept(this);

        switch (unaryNode->getUnaryOperation()) {
            case Parser::UnaryOperation::MINUS:
                return _llvmBuilder->CreateUnOp(llvm::Instruction::UnaryOps::FNeg, value);
        }

        return nullptr;
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_BinaryNode *binaryNode) {
        auto firstValue = binaryNode->getFirstNode()->accept(this);
        auto secondValue = binaryNode->getSecondNode()->accept(this);

        switch (binaryNode->getBinaryOperation()) {
            case Parser::BinaryOperation::PLUS:
                return _llvmBuilder->CreateAdd(firstValue, secondValue);
            case Parser::BinaryOperation::MINUS:
                return _llvmBuilder->CreateSub(firstValue, secondValue);
            case Parser::BinaryOperation::STAR:
                return _llvmBuilder->CreateMul(firstValue, secondValue);
            case Parser::BinaryOperation::SLASH:
                return _llvmBuilder->CreateSDiv(firstValue, secondValue);
        }

        return nullptr;
    }

    std::map<GSString, llvm::Value*> variableNameToInstruction;

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_AssignmentNode *assignmentNode) {
        auto declaration = assignmentNode->getNode()->accept(this);

        return _llvmBuilder->CreateStore(assignmentNode->getExpression()->accept(this), declaration);
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_VariableDeclarationNode *variableDeclarationNode) {
        llvm::Type *type = nullptr;

        switch (variableDeclarationNode->getType()) {
            case Parser::ValueType::VOID:
                Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                               "Can`t generate variable with void type!");

                Exceptions::errorHandler.throw_();

                break;
            case Parser::ValueType::INT:
                type = llvm::Type::getInt32Ty(*_llvmContext);

                break;
            case Parser::ValueType::STRING:
                 Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                                "Can`t generate variable with string type!");

                 Exceptions::errorHandler.throw_();

                 break;
        }

        auto variable = _llvmBuilder->CreateAlloca(type, nullptr, variableDeclarationNode->getName());

        variableNameToInstruction[variableDeclarationNode->getName()] = variable;

        return variable;
    }

    llvm::Value *GS_LLVMCodeGenVisitor::visit(Parser::GS_VariableUsingNode *variableUsingNode) {
        auto variableName = variableUsingNode->getName();

        auto variableType = _context->getTableOfVariables()->getValueTypeByName(variableName);

        llvm::Type *type = nullptr;

        switch (variableType) {
            case Parser::ValueType::VOID:
                Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                               "Can`t generate variable with void type!");

                Exceptions::errorHandler.throw_();

                break;
            case Parser::ValueType::INT:
                type = llvm::Type::getInt32Ty(*_llvmContext);

                break;
            case Parser::ValueType::STRING:
                Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                               "Can`t generate variable with string type!");

                Exceptions::errorHandler.throw_();

                break;
        }

        return _llvmBuilder->CreateLoad(type, variableNameToInstruction[variableName]);
    }

}
