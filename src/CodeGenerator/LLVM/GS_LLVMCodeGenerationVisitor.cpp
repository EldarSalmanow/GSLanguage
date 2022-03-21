#include <llvm/IR/IRBuilder.h>

#include <LLVM/GS_LLVMCodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeGenerationVisitor::GS_LLVMCodeGenerationVisitor()
            : GS_CodeGenerationVisitor<Ptr<llvm::Value>>(std::make_shared<GS_LLVMCodeGenerationVisitorContext>()) {
        _builder = std::make_shared<llvm::IRBuilder<>>(_getLLVMVisitorContext()->getContext());
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitTranslationUnitDeclaration(SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto name = translationUnitDeclaration->getName();
        auto nodes = translationUnitDeclaration->getNodes();

        _getLLVMVisitorContext()->createModule(name);

        for (auto &node : nodes) {
            visitNode(node);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto name = functionDeclaration->getName();
        auto body = functionDeclaration->getBody();

        auto llvmFunctionType = llvm::FunctionType::get(llvm::Type::getVoidTy(_getLLVMVisitorContext()->getContext()), false);

        auto llvmFunction = llvm::Function::Create(llvmFunctionType, llvm::Function::LinkageTypes::ExternalLinkage, name.AsString(), _getLLVMVisitorContext()->getModule());

        auto block = llvm::BasicBlock::Create(_getLLVMVisitorContext()->getContext(), "entry", llvmFunction);

        _builder->SetInsertPoint(block);

        for (auto &statement : body) {
            visitStatement(statement);
        }

        _builder->CreateRetVoid();

        return llvmFunction;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitVariableDeclarationStatement(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) {
        auto name = variableDeclarationStatement->getName();
        auto type = variableDeclarationStatement->getType();
        auto expression = variableDeclarationStatement->getExpression();

        auto llvmFunction = _builder->GetInsertBlock()->getParent();

        auto typeName = type->getName();

        Ptr<llvm::Type> llvmType;

        if (typeName == U"I32"_us) {
            llvmType = llvm::Type::getInt32Ty(_getLLVMVisitorContext()->getContext());
        } else {
            return nullptr;
        }

        auto llvmAllocaInstruction = _builder->CreateAlloca(llvmType);

        _variables.emplace_back(std::make_pair(name, llvmAllocaInstruction));

        return _builder->CreateStore(visitExpression(expression), llvmAllocaInstruction);
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitAssignmentStatement(SharedPtr<AST::GS_AssignmentStatement> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->getLValueExpression();
        auto rvalueExpression = assignmentStatement->getRValueExpression();

        return _builder->CreateStore(visitExpression(lvalueExpression), visitExpression(rvalueExpression));
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitExpressionStatement(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->getExpression();

        return visitExpression(expression);
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitConstantExpression(SharedPtr<AST::GS_ConstantExpression> constantExpression) {
        auto value = constantExpression->getValue();

        auto type = value->getType();

        auto typeName = type->getName();

        Ptr<llvm::Type> llvmType;

        if (typeName == U"I32"_us) {
            auto number = value->getValueWithCast<I32>();

            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(_getLLVMVisitorContext()->getContext()), number);
        } else if (typeName == U"String"_us) {
            auto string = value->getValueWithCast<UString>();

            return _builder->CreateGlobalStringPtr(string.AsString());
        } else {
            return nullptr;
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) {
        auto operation = unaryExpression->getUnaryOperation();
        auto expression = unaryExpression->getExpression();

        switch (operation) {
            case AST::UnaryOperation::Minus:
                return _builder->CreateUnOp(llvm::Instruction::UnaryOps::FNeg, visitExpression(expression));
            default:
                return nullptr;
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) {
        auto operation = binaryExpression->getBinaryOperation();
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();

        switch (operation) {
            case AST::BinaryOperation::Plus:
                return _builder->CreateAdd(visitExpression(firstExpression), visitExpression(secondExpression));
            case AST::BinaryOperation::Minus:
                return _builder->CreateSub(visitExpression(firstExpression), visitExpression(secondExpression));
            case AST::BinaryOperation::Star:
                return _builder->CreateMul(visitExpression(firstExpression), visitExpression(secondExpression));
            case AST::BinaryOperation::Slash:
                return _builder->CreateSDiv(visitExpression(firstExpression), visitExpression(secondExpression));
            default:
                return nullptr;
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitVariableUsingExpression(SharedPtr<AST::GS_VariableUsingExpression> variableUsingExpression) {
        auto name = variableUsingExpression->getName();

        auto llvmAllocaInstruction = _findVariableByName(name);

        return _builder->CreateLoad(llvmAllocaInstruction->getAllocatedType(), llvmAllocaInstruction, name.AsString());
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionCallingExpression(SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) {
        auto name = functionCallingExpression->getName();

        auto llvmFunction = _getLLVMVisitorContext()->getModule().getFunction(name.AsString());

        if (llvmFunction != nullptr) {
            return _builder->CreateCall(llvmFunction);
        }

        return nullptr;
    }

    Ptr<llvm::AllocaInst> GS_LLVMCodeGenerationVisitor::_findVariableByName(ConstLRef<UString> name) {
        for (auto &pair : _variables) {
            if (pair.first == name) {
                return pair.second;
            }
        }

        return nullptr;
    }

    SharedPtr<GS_LLVMCodeGenerationVisitorContext> GS_LLVMCodeGenerationVisitor::_getLLVMVisitorContext() {
        return std::reinterpret_pointer_cast<GS_LLVMCodeGenerationVisitorContext>(GS_CodeGenerationVisitor<Ptr<llvm::Value>>::getContext());
    }

}
