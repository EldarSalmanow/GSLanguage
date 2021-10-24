#ifndef GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
#define GSLANGUAGE_GS_CODEGENERATIONVISITOR_H

#include <AST/GS_Visitor.h>

namespace GSLanguageCompiler::CodeGenerator {

    class GS_CodeGenerationPass;

    class GS_CompilerUnit;

    class GS_CodeGenerationVisitor : public AST::GS_Visitor {
    public:

        explicit GS_CodeGenerationVisitor(GS_CodeGenerationPass *pass);

    public:

        Void visit(AST::GS_FunctionDeclaration *functionDeclaration) override;

        Void visit(AST::GS_VariableDeclarationStatement *variableDeclarationStatement) override;

        Void visit(AST::GS_AssignmentStatement *assignmentStatement) override;

        Void visit(AST::GS_ExpressionStatement *expressionStatement) override;

        Void visit(AST::GS_ConstantExpression *constantExpression) override;

        Void visit(AST::GS_UnaryExpression *unaryExpression) override;

        Void visit(AST::GS_BinaryExpression *binaryExpression) override;

        Void visit(AST::GS_VariableUsingExpression *variableUsingExpression) override;

        Void visit(AST::GS_FunctionCallingExpression *functionCallingExpression) override;

    private:

        GS_CodeGenerationPass *_pass;
    };

}

#endif //GSLANGUAGE_GS_CODEGENERATIONVISITOR_H
