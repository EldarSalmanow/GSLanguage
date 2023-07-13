#ifndef GSLANGUAGE_AST_H
#define GSLANGUAGE_AST_H

/**
 * This file includes all files from GSLanguageCompiler AST Module
 */

#include <AST/GS_Node.h>

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <AST/GS_Qualifiers.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_ModuleDeclaration.h>
#include <AST/Declarations/GS_ImportDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_IfStatement.h>
#include <AST/Statements/GS_ForStatement.h>
#include <AST/Statements/GS_WhileStatement.h>
#include <AST/Statements/GS_MatchStatement.h>
#include <AST/Statements/GS_ReturnStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_LiteralExpression.h>
#include <AST/Expressions/GS_ArrayExpression.h>
#include <AST/Expressions/GS_RangeExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_IndexExpression.h>
#include <AST/Expressions/GS_CastExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

#include <AST/GS_Visitor.h>

#include <AST/GS_Pass.h>

#include <AST/GS_ASTContext.h>

#include <AST/GS_ASTBuilder.h>

namespace GSLanguageCompiler::AST {

    void f() {
        auto ms = GS_MatchStatement::Create(GS_LiteralExpression::Create(GS_I32Value::Create(1)));

        auto arm = ms->AddArm(GS_MatchArm::Create(GS_LiteralExpression::Create(GS_I32Value::Create(1))));

        arm.AddStatement(GS_ExpressionStatement::Create(GS_FunctionCallingExpression::Create("IO::PrintLn", {GS_LiteralExpression::Create(GS_StringValue::Create("1 value")) })));
    }

}

#endif //GSLANGUAGE_AST_H
