#include <llvm/IR/IRBuilder.h>

#include <LLVM/GS_LLVMCodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeGenerationVisitor::GS_LLVMCodeGenerationVisitor()
            : GS_CodeGenerationVisitor<Ptr<llvm::Value>>(std::make_shared<GS_LLVMCodeGenerationVisitorContext>()) {
        _builder = std::make_shared<llvm::IRBuilder<>>(_getLLVMVisitorContext()->getContext());
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitTranslationUnitDeclaration(SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto name = translationUnitDeclaration->GetName();
        auto nodes = translationUnitDeclaration->GetNodes();

        _getLLVMVisitorContext()->createModule(name);

        for (auto &node : nodes) {
            visitNode(node);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto name = functionDeclaration->GetName();
        auto body = functionDeclaration->GetBody();

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
        auto name = variableDeclarationStatement->GetName();
        auto type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        auto llvmFunction = _builder->GetInsertBlock()->getParent();

        auto typeName = type->GetName();

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
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        return _builder->CreateStore(visitExpression(lvalueExpression), visitExpression(rvalueExpression));
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitExpressionStatement(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        return visitExpression(expression);
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitConstantExpression(SharedPtr<AST::GS_ConstantExpression> constantExpression) {
        auto value = AST::GSValueCast<AST::GS_LiteralValue>(constantExpression->GetValue());

        auto type = value->GetType();

        auto typeName = type->GetName();

        Ptr<llvm::Type> llvmType;

        if (typeName == U"I32"_us) {
            auto number = value->GetValueWithCast<I32>();

            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(_getLLVMVisitorContext()->getContext()), number);
        } else if (typeName == U"String"_us) {
            auto string = value->GetValueWithCast<UString>();

            return _builder->CreateGlobalStringPtr(string.AsString());
        } else {
            return nullptr;
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) {
        auto operation = unaryExpression->GetUnaryOperation();
        auto expression = unaryExpression->GetExpression();

        switch (operation) {
            case AST::UnaryOperation::Minus:
                return _builder->CreateUnOp(llvm::Instruction::UnaryOps::FNeg, visitExpression(expression));
            default:
                return nullptr;
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) {
        auto operation = binaryExpression->GetBinaryOperation();
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

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
        auto name = variableUsingExpression->GetName();

        auto llvmAllocaInstruction = _findVariableByName(name);

        return _builder->CreateLoad(llvmAllocaInstruction->getAllocatedType(), llvmAllocaInstruction, name.AsString());
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionCallingExpression(SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) {
        auto name = functionCallingExpression->GetName();

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
