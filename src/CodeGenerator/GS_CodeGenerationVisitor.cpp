#include <stack>

#include <AST/GS_IncludeAll.h>

#include <GS_CompilerUnit.h>

#include <GS_CodeGenerationPass.h>

#include <GS_CodeGenerationVisitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    llvm::Type *voidType(LLVM::Context &context) {
        return llvm::Type::getVoidTy(context);
    }

    llvm::Type *i32Type(LLVM::Context &context) {
        return llvm::Type::getInt32Ty(context);
    }

    llvm::Type *toLLVMType(LLVM::Context &context, AST::GSTypePtr &type) {
        auto name = type->getName();

        if (name == "I32") {
            return llvm::Type::getInt32Ty(context);
        } else if (name == "String") {
            return llvm::Type::getInt8PtrTy(context);
        } else {
            return nullptr;
        }
    }

    llvm::Function *createFunction(LLVM::Context &context, LLVM::Module &module, const String &name) {
        return llvm::Function::Create(llvm::FunctionType::get(voidType(context), false),
                                      llvm::Function::ExternalLinkage,
                                      name,
                                      module);
    }

    llvm::BasicBlock *createBlock(LLVM::Context &context, const String &name, llvm::Function *function) {
        return llvm::BasicBlock::Create(context, name, function);
    }

    GS_CodeGenerationVisitor::GS_CodeGenerationVisitor(GS_CodeGenerationPass *pass)
            : _pass(pass) {}

    std::stack<llvm::Value*> ir;

    Void GS_CodeGenerationVisitor::visit(AST::GS_FunctionDeclaration *functionDeclaration) {
        auto name = functionDeclaration->getName();

        auto compilerUnit = _pass->getCompilerUnit();

        auto function = createFunction(compilerUnit->getContext(), compilerUnit->getModule(), name);

        auto block = createBlock(compilerUnit->getContext(), "entry", function);

        compilerUnit->getBuilder().SetInsertPoint(block);

        AST::GS_Visitor::visit(functionDeclaration);

        compilerUnit->getBuilder().CreateRet(nullptr);
    }

    Map<String, llvm::AllocaInst*> variables;

    Void GS_CodeGenerationVisitor::visit(AST::GS_VariableDeclarationStatement *variableDeclarationStatement) {
        auto name = variableDeclarationStatement->getName();
        auto type = variableDeclarationStatement->getType();

        auto compilerUnit = _pass->getCompilerUnit();

        auto llvmType = toLLVMType(compilerUnit->getContext(), type);

        auto allocaInstruction = compilerUnit->getBuilder().CreateAlloca(llvmType);

        variables[name] = allocaInstruction;

        ir.push(allocaInstruction);
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_AssignmentStatement *assignmentStatement) {
        auto statement = assignmentStatement->getStatement();
        auto expression = assignmentStatement->getExpression();

        auto compilerUnit = _pass->getCompilerUnit();

        statement->accept(this);

        auto statementInstruction = ir.top();

        expression->accept(this);

        auto expressionInstruction = ir.top();

        compilerUnit->getBuilder().CreateStore(expressionInstruction, statementInstruction);
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_ExpressionStatement *expressionStatement) {
        auto expression = expressionStatement->getExpression();

        expression->accept(this);
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_ConstantExpression *constantExpression) {
        auto value = constantExpression->getValue();

        auto compilerUnit = _pass->getCompilerUnit();

        auto valueType = value->getType();

        auto typeName = valueType->getName();

        if (typeName == "I32") {
            ir.push(llvm::ConstantInt::get(i32Type(compilerUnit->getContext()), value->getValueWithCast<I32>()));
        } else if (typeName == "String") {
            ir.push(compilerUnit->getBuilder().CreateGlobalString(value->getValueWithCast<String>()));
        }
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_UnaryExpression *unaryExpression) {
        auto operation = unaryExpression->getUnaryOperation();
        auto expression = unaryExpression->getExpression();

        auto compilerUnit = _pass->getCompilerUnit();

        expression->accept(this);

        switch (operation) {
            case AST::UnaryOperation::Minus:
                ir.push(compilerUnit->getBuilder().CreateNeg(ir.top()));
        }
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_BinaryExpression *binaryExpression) {
        auto operation = binaryExpression->getBinaryOperation();
        auto firstExpression = binaryExpression->getFirstExpression();
        auto secondExpression = binaryExpression->getSecondExpression();

        auto compilerUnit = _pass->getCompilerUnit();

        firstExpression->accept(this);

        auto firstExpressionInstruction = ir.top();

        secondExpression->accept(this);

        auto secondExpressionInstruction = ir.top();

        switch (operation) {
            case AST::BinaryOperation::Plus:
                ir.push(compilerUnit->getBuilder().CreateAdd(firstExpressionInstruction, secondExpressionInstruction));
            case AST::BinaryOperation::Minus:
                ir.push(compilerUnit->getBuilder().CreateSub(firstExpressionInstruction, secondExpressionInstruction));
            case AST::BinaryOperation::Star:
                ir.push(compilerUnit->getBuilder().CreateMul(firstExpressionInstruction, secondExpressionInstruction));
            case AST::BinaryOperation::Slash:
                ir.push(compilerUnit->getBuilder().CreateSDiv(firstExpressionInstruction, secondExpressionInstruction));
        }
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_VariableUsingExpression *variableUsingExpression) {
        auto name = variableUsingExpression->getName();

        auto compilerUnit = _pass->getCompilerUnit();

        ir.push(compilerUnit->getBuilder().CreateLoad(variables[name]->getAllocatedType(), variables[name]));
    }

    Void GS_CodeGenerationVisitor::visit(AST::GS_FunctionCallingExpression *functionCallingExpression) {}


}
