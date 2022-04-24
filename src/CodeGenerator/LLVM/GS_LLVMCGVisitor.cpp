#include <LLVM/GS_LLVMCGVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCGVisitor::GS_LLVMCGVisitor(LRef<GSLLVMCGContextPtr> context)
            : _context(context), _builder(_context->GetContext()) {}

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateNode(LRef<AST::GSNodePtr> node) {
        if (node->IsDeclaration()) {
            auto declaration = ToDeclaration(node);

            return GenerateDeclaration(declaration);
        }

        if (node->IsStatement()) {
            auto statement = ToStatement(node);

            return GenerateStatement(statement);
        }

        if (node->IsExpression()) {
            auto expression = ToExpression(node);

            return GenerateExpression(expression);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateDeclaration(LRef<AST::GSDeclarationPtr> declaration) {
        switch (declaration->GetDeclarationType()) {
            case AST::DeclarationType::TranslationUnitDeclaration: {
                auto translationUnitDeclaration = ToDeclaration<AST::GS_TranslationUnitDeclaration>(declaration);

                return GenerateTranslationUnitDeclaration(translationUnitDeclaration);
            }
            case AST::DeclarationType::FunctionDeclaration: {
                auto functionDeclaration = ToDeclaration<AST::GS_FunctionDeclaration>(declaration);

                return GenerateFunctionDeclaration(functionDeclaration);
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateStatement(LRef<AST::GSStatementPtr> statement) {
        switch (statement->GetStatementType()) {
            case AST::StatementType::VariableDeclarationStatement: {
                auto variableDeclarationStatement = ToStatement<AST::GS_VariableDeclarationStatement>(statement);

                return GenerateVariableDeclarationStatement(variableDeclarationStatement);
            }
            case AST::StatementType::AssignmentStatement: {
                auto assignmentStatement = ToStatement<AST::GS_AssignmentStatement>(statement);

                return GenerateAssignmentStatement(assignmentStatement);
            }
            case AST::StatementType::ExpressionStatement: {
                auto expressionStatement = ToStatement<AST::GS_ExpressionStatement>(statement);

                return GenerateExpressionStatement(expressionStatement);
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateExpression(LRef<AST::GSExpressionPtr> expression) {
        switch (expression->GetExpressionType()) {
            case AST::ExpressionType::ConstantExpression: {
                auto constantExpression = ToExpression<AST::GS_ConstantExpression>(expression);

                return GenerateConstantExpression(constantExpression);
            }
            case AST::ExpressionType::UnaryExpression: {
                auto unaryExpression = ToExpression<AST::GS_UnaryExpression>(expression);

                return GenerateUnaryExpression(unaryExpression);
            }
            case AST::ExpressionType::BinaryExpression: {
                auto binaryExpression = ToExpression<AST::GS_BinaryExpression>(expression);

                return GenerateBinaryExpression(binaryExpression);
            }
            case AST::ExpressionType::VariableUsingExpression: {
                auto variableUsingExpression = ToExpression<AST::GS_VariableUsingExpression>(expression);

                return GenerateVariableUsingExpression(variableUsingExpression);
            }
            case AST::ExpressionType::FunctionCallingExpression: {
                auto functionCallingExpression = ToExpression<AST::GS_FunctionCallingExpression>(expression);

                return GenerateFunctionCallingExpression(functionCallingExpression);
            }
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateTranslationUnitDeclaration(LRef<SharedPtr<AST::GS_TranslationUnitDeclaration>> translationUnitDeclaration) {
        auto name = translationUnitDeclaration->GetName();
        auto nodes = translationUnitDeclaration->GetNodes();

        _context->CreateModule(name);

        for (auto &node : nodes) {
            GenerateNode(node);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateFunctionDeclaration(LRef<SharedPtr<AST::GS_FunctionDeclaration>> functionDeclaration) {
        auto name = functionDeclaration->GetName();
        auto body = functionDeclaration->GetBody();

        auto llvmFunctionType = llvm::FunctionType::get(llvm::Type::getVoidTy(_context->GetContext()), false);

        auto llvmFunction = llvm::Function::Create(llvmFunctionType, llvm::Function::LinkageTypes::ExternalLinkage, name.AsString(), _context->GetModule());

        auto block = llvm::BasicBlock::Create(_context->GetContext(), "entry", llvmFunction);

        _builder.SetInsertPoint(block);

        for (auto &statement : body) {
            GenerateStatement(statement);
        }

        _builder.CreateRetVoid();

        return llvmFunction;
    }

    Vector<std::pair<UString, Ptr<llvm::AllocaInst>>> Variables;

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateVariableDeclarationStatement(LRef<SharedPtr<AST::GS_VariableDeclarationStatement>> variableDeclarationStatement) {
        auto name = variableDeclarationStatement->GetName();
        auto type = variableDeclarationStatement->GetType();
        auto expression = variableDeclarationStatement->GetExpression();

        auto llvmFunction = _builder.GetInsertBlock()->getParent();

        auto typeName = type->GetName();

        Ptr<llvm::Type> llvmType;

        if (typeName == "I32"_us) {
            llvmType = llvm::Type::getInt32Ty(_context->GetContext());
        } else {
            return nullptr;
        }

        auto llvmAllocaInstruction = _builder.CreateAlloca(llvmType);

        Variables.emplace_back(std::make_pair(name, llvmAllocaInstruction));

        return _builder.CreateStore(GenerateExpression(expression), llvmAllocaInstruction);
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateAssignmentStatement(LRef<SharedPtr<AST::GS_AssignmentStatement>> assignmentStatement) {
        auto lvalueExpression = assignmentStatement->GetLValueExpression();
        auto rvalueExpression = assignmentStatement->GetRValueExpression();

        return _builder.CreateStore(GenerateExpression(lvalueExpression), GenerateExpression(rvalueExpression));
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateExpressionStatement(LRef<SharedPtr<AST::GS_ExpressionStatement>> expressionStatement) {
        auto expression = expressionStatement->GetExpression();

        return GenerateExpression(expression);
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateConstantExpression(LRef<SharedPtr<AST::GS_ConstantExpression>> constantExpression) {
        auto value = AST::GSValueCast<AST::GS_LiteralValue>(constantExpression->GetValue());

        auto type = value->GetType();

        auto typeName = type->GetName();

        Ptr<llvm::Type> llvmType;

        if (typeName == "I32"_us) {
            auto number = value->GetValueWithCast<I32>();

            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(_context->GetContext()), number);
        } else if (typeName == "String"_us) {
            auto string = value->GetValueWithCast<UString>();

            return _builder.CreateGlobalStringPtr(string.AsString());
        } else {
            return nullptr;
        }
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateUnaryExpression(LRef<SharedPtr<AST::GS_UnaryExpression>> unaryExpression) {
        auto operation = unaryExpression->GetUnaryOperation();
        auto expression = unaryExpression->GetExpression();

        switch (operation) {
            case AST::UnaryOperation::Minus:
                return _builder.CreateUnOp(llvm::Instruction::UnaryOps::FNeg, GenerateExpression(expression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateBinaryExpression(LRef<SharedPtr<AST::GS_BinaryExpression>> binaryExpression) {
        auto operation = binaryExpression->GetBinaryOperation();
        auto firstExpression = binaryExpression->GetFirstExpression();
        auto secondExpression = binaryExpression->GetSecondExpression();

        switch (operation) {
            case AST::BinaryOperation::Plus:
                return _builder.CreateAdd(GenerateExpression(firstExpression), GenerateExpression(secondExpression));
            case AST::BinaryOperation::Minus:
                return _builder.CreateSub(GenerateExpression(firstExpression), GenerateExpression(secondExpression));
            case AST::BinaryOperation::Star:
                return _builder.CreateMul(GenerateExpression(firstExpression), GenerateExpression(secondExpression));
            case AST::BinaryOperation::Slash:
                return _builder.CreateSDiv(GenerateExpression(firstExpression), GenerateExpression(secondExpression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateVariableUsingExpression(LRef<SharedPtr<AST::GS_VariableUsingExpression>> variableUsingExpression) {
        auto name = variableUsingExpression->GetName();

        Ptr<llvm::AllocaInst> llvmAllocaInstruction;

        for (auto &pair : Variables) {
            if (name == pair.first) {
                llvmAllocaInstruction = pair.second;

                break;
            }
        }

        return _builder.CreateLoad(llvmAllocaInstruction->getAllocatedType(), llvmAllocaInstruction, name.AsString());
    }

    Ptr<llvm::Value> GS_LLVMCGVisitor::GenerateFunctionCallingExpression(LRef<SharedPtr<AST::GS_FunctionCallingExpression>> functionCallingExpression) {
        auto name = functionCallingExpression->GetName();

        auto llvmFunction = _context->GetModule().getFunction(name.AsString());

        if (llvmFunction != nullptr) {
            return _builder.CreateCall(llvmFunction);
        }

        return nullptr;
    }

}
