#ifndef GSLANGUAGE_AST_H
#define GSLANGUAGE_AST_H

/**
 * This file includes all files from GSLanguageCompiler AST Module
 */

#include <AST/GS_ASTContext.h>

#include <AST/GS_ASTBuilder.h>

#include <AST/GS_Node.h>

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_ConstantExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

#include <AST/GS_Type.h>

#include <AST/GS_Visitor.h>

#include <AST/GS_Pass.h>

#endif //GSLANGUAGE_AST_H
