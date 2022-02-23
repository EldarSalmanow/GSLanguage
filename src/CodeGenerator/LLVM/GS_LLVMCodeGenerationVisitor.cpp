#include <llvm/IR/IRBuilder.h>

#include <LLVM/GS_LLVMCodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    GS_LLVMCodeGenerationVisitor::GS_LLVMCodeGenerationVisitor() = default;

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

    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitFunctionDeclaration(SharedPtr<AST::GS_FunctionDeclaration> functionDeclaration) {
        return nullptr;
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

    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitUnaryExpression(SharedPtr<AST::GS_UnaryExpression> unaryExpression) {
        return nullptr;
    }

    Ptr<llvm::Value> GS_LLVMCodeGenerationVisitor::visitBinaryExpression(SharedPtr<AST::GS_BinaryExpression> binaryExpression) {
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

    llvm::Type *GS_LLVMCodeGenerationVisitor::getType(AST::GSTypePtr type) {
        auto name = type->getName();

        if (name == U"I32") {
            return getI32Type();
        } else if (name == U"String") {
            return getStringType();
        } else if (name == U"Void") {
            return getVoidType();
        }

        return nullptr;
    }

    static llvm::LLVMContext context;

    llvm::Type *GS_LLVMCodeGenerationVisitor::getI32Type() {
        return llvm::Type::getInt32Ty(context);
    }

    llvm::Type *GS_LLVMCodeGenerationVisitor::getStringType() {
        return nullptr;
    }

    llvm::Type *GS_LLVMCodeGenerationVisitor::getVoidType() {
        return nullptr;
    }

}
