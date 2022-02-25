#include <llvm/IR/IRBuilder.h>

#include <LLVM/GS_LLVMCodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    Ptr<llvm::Type> GenerateType(AST::GSTypePtr type, LRef<llvm::LLVMContext> context) {
        auto typeName = type->getName();

        if (typeName == U"Void") {
            return llvm::Type::getVoidTy(context);
        } else if (typeName == U"I32") {
            return llvm::Type::getInt32Ty(context);
        } else if (typeName == U"String") {
            return llvm::Type::getInt8PtrTy(context);
        }

        return nullptr;
    }
    
    Ptr<llvm::Constant> GenerateValue(AST::GSValuePtr value, LRef<llvm::IRBuilder<>> builder) {
        auto type = value->getType();
        
        auto typeName = type->getName();

        auto &context = builder.getContext();

        if (typeName == U"I32") {
            return llvm::ConstantInt::get(GenerateType(type, context), value->getValueWithCast<I32>());
        } else if (typeName == U"String") {
            return builder.CreateGlobalStringPtr(value->getValueWithCast<UString>().asString());
        }

        return nullptr;
    }
    
    GS_LLVMCodeGenerationVisitor::GS_LLVMCodeGenerationVisitor()
            : _unit(std::make_shared<GS_LLVMCompilerUnit>()), _builder(_unit->getContext()) {}

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitNode(ConstLRef<AST::GSNodePtr> node) {
        if (node->isDeclaration()) {
            auto declaration = std::reinterpret_pointer_cast<AST::GS_Declaration>(node);

            return visitDeclaration(declaration);
        }

        if (node->isStatement()) {
            auto statement = std::reinterpret_pointer_cast<AST::GS_Statement>(node);

            return visitStatement(statement);
        }

        if (node->isExpression()) {
            auto expression = std::reinterpret_pointer_cast<AST::GS_Expression>(node);

            return visitExpression(expression);
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitDeclaration(ConstLRef<AST::GSDeclarationPtr> declaration) {
        switch (declaration->getDeclarationType()) {
            case AST::DeclarationType::TranslationUnitDeclaration:
                return visitTranslationUnitDeclaration(std::reinterpret_pointer_cast<AST::GS_TranslationUnitDeclaration>(declaration));
            case AST::DeclarationType::FunctionDeclaration:
                return visitFunctionDeclaration(std::reinterpret_pointer_cast<AST::GS_FunctionDeclaration>(declaration));
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitStatement(ConstLRef<AST::GSStatementPtr> statement) {
        switch (statement->getStatementType()) {
            case AST::StatementType::VariableDeclarationStatement:
                return visitVariableDeclarationStatement(std::reinterpret_pointer_cast<AST::GS_VariableDeclarationStatement>(statement));
            case AST::StatementType::AssignmentStatement:
                return visitAssignmentStatement(std::reinterpret_pointer_cast<AST::GS_AssignmentStatement>(statement));
            case AST::StatementType::ExpressionStatement:
                return visitExpressionStatement(std::reinterpret_pointer_cast<AST::GS_ExpressionStatement>(statement));
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitExpression(ConstLRef<AST::GSExpressionPtr> expression) {
        switch (expression->getExpressionType()) {
            case AST::ExpressionType::ConstantExpression:
                return visitConstantExpression(std::reinterpret_pointer_cast<AST::GS_ConstantExpression>(expression));
            case AST::ExpressionType::UnaryExpression:
                return visitUnaryExpression(std::reinterpret_pointer_cast<AST::GS_UnaryExpression>(expression));
            case AST::ExpressionType::BinaryExpression:
                return visitBinaryExpression(std::reinterpret_pointer_cast<AST::GS_BinaryExpression>(expression));
            case AST::ExpressionType::VariableUsingExpression:
                return visitVariableUsingExpression(std::reinterpret_pointer_cast<AST::GS_VariableUsingExpression>(expression));
            case AST::ExpressionType::FunctionCallingExpression:
                return visitFunctionCallingExpression(std::reinterpret_pointer_cast<AST::GS_FunctionCallingExpression>(expression));
        }
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitTranslationUnitDeclaration(SharedPtr<AST::GS_TranslationUnitDeclaration> translationUnitDeclaration) {
        auto nodes = translationUnitDeclaration->getNodes();

        _unit->createModule(translationUnitDeclaration->getName());

        for (auto &node : nodes) {
            this->visitNode(node);
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) {
        auto name = functionDeclaration->getName();
        auto body = functionDeclaration->getBody();

        if (!_unit->hasModule()) {
            return nullptr;
        }

        auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(_builder.getContext()), false);

        auto function = llvm::Function::Create(functionType, llvm::Function::LinkageTypes::ExternalLinkage, name.asString(), _unit->getModule());

        auto block = llvm::BasicBlock::Create(_unit->getContext(), "entry", function);

        _builder.SetInsertPoint(block);

        for (auto &statement : body) {
            this->visitStatement(statement);
        }

        _builder.CreateRetVoid();

        return function;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitVariableDeclarationStatement(SharedPtr<AST::GS_VariableDeclarationStatement> variableDeclarationStatement) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitAssignmentStatement(SharedPtr<AST::GS_AssignmentStatement> assignmentStatement) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitExpressionStatement(SharedPtr<AST::GS_ExpressionStatement> expressionStatement) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitConstantExpression(SharedPtr<AST::GS_ConstantExpression> constantExpression) {
        auto value = constantExpression->getValue();

        return GenerateValue(value, _builder);
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) {
        auto expression = unaryExpression->getExpression();
        auto operation = unaryExpression->getUnaryOperation();

        switch (operation) {
            case AST::UnaryOperation::Minus:
                return _builder.CreateUnOp(llvm::Instruction::UnaryOps::FNeg, this->visitExpression(expression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) {
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();
        auto operation = binaryExpression->getBinaryOperation();

        switch (operation) {
            case AST::BinaryOperation::Plus:
                return _builder.CreateAdd(this->visitExpression(firstExpression), this->visitExpression(secondExpression));
            case AST::BinaryOperation::Minus:
                return _builder.CreateSub(this->visitExpression(firstExpression), this->visitExpression(secondExpression));
            case AST::BinaryOperation::Star:
                return _builder.CreateMul(this->visitExpression(firstExpression), this->visitExpression(secondExpression));
            case AST::BinaryOperation::Slash:
                return _builder.CreateSDiv(this->visitExpression(firstExpression), this->visitExpression(secondExpression));
        }

        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitVariableUsingExpression(SharedPtr<AST::GS_VariableUsingExpression> variableUsingExpression) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionCallingExpression(SharedPtr<AST::GS_FunctionCallingExpression> functionCallingExpression) {
        return nullptr;
    }

    GSCompilerUnitPtr GS_LLVMCodeGenerationVisitor::getCompilerUnit() {
        return _unit;
    }

}
