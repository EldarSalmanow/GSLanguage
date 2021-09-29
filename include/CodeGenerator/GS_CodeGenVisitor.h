#ifndef GSLANGUAGE_GS_CODEGENVISITOR_H
#define GSLANGUAGE_GS_CODEGENVISITOR_H

#include <llvm/IR/IRBuilder.h>
//#include <llvm/IR/LegacyPassManager.h>
//#include <llvm/Transforms/InstCombine/InstCombine.h>
//#include <llvm/Transforms/Scalar.h>

#include <Parser/Visitors/GS_Visitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_LLVMCodeGenVisitor : public Parser::GS_Visitor<llvm::Value*> {
    public:

        GS_LLVMCodeGenVisitor();

    public:

        GSVoid setup(Starter::GSContextPtr &context) override;

        llvm::Value *visit(Parser::GS_RootNode *rootNode) override;

        llvm::Value *visit(Parser::GS_BlockNode *blockNode) override;

        llvm::Value *visit(Parser::GS_ValueNode *valueNode) override;

        llvm::Value *visit(Parser::GS_UnaryNode *unaryNode) override;

        llvm::Value *visit(Parser::GS_BinaryNode *binaryNode) override;

        llvm::Value *visit(Parser::GS_AssignmentNode *assignmentNode) override;

        llvm::Value *visit(Parser::GS_VariableDeclarationNode *variableDeclarationNode) override;

        llvm::Value *visit(Parser::GS_VariableUsingNode *variableUsingNode) override;

    private:

        std::shared_ptr<llvm::LLVMContext> _llvmContext;

        std::shared_ptr<llvm::Module> _llvmModule;

        std::shared_ptr<llvm::IRBuilder<>> _llvmBuilder;
    };

}

#endif //GSLANGUAGE_GS_CODEGENVISITOR_H
