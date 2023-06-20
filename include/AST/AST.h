#ifndef GSLANGUAGE_AST_H
#define GSLANGUAGE_AST_H

/**
 * This file includes all files from GSLanguageCompiler AST Module
 */

/*
 *
 * AUDIT                                        - Pass
 *
 * CMakeLists.txt                               - Pass
 * AST.h                                        - Pass
 * GS_Node.h                                    - Pass
 * GS_Declaration.h                             - Pass
 * GS_Statement.h                               - Pass
 * GS_Expression.h                              - Pass
 * GS_Qualifiers.h                              - Pass
 * Declarations/GS_TranslationUnitDeclaration.h - Pass
 * Declarations/GS_FunctionDeclaration.h        - Pass
 * Statements/GS_VariableDeclarationStatement.h - Pass
 * Statements/GS_AssignmentStatement.h          - Pass
 * Statements/GS_ExpressionStatement.h          - Pass
 * Expressions/GS_ConstantExpression.h          - Pass
 * Expressions/GS_UnaryExpression.h             - Pass
 * Expressions/GS_BinaryExpression.h            - Pass
 * Expressions/GS_ArrayExpression.h             - Pass
 * Expressions/GS_VariableUsingExpression.h     - Pass
 * Expressions/GS_FunctionCallingExpression.h   - Pass
 * GS_Visitor.h                                 - Pass
 * GS_Pass.h                                    - Pass
 * GS_ASTContext.h                              - Pass
 * GS_ASTBuilder.h                              - Pass
 *
 */

#include <AST/GS_Node.h>

#include <AST/GS_Declaration.h>
#include <AST/GS_Statement.h>
#include <AST/GS_Expression.h>

#include <AST/GS_Qualifiers.h>

#include <AST/Declarations/GS_TranslationUnitDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_ConstantExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_ArrayExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>

#include <AST/GS_Visitor.h>

#include <AST/GS_Pass.h>

#include <AST/GS_ASTContext.h>

#include <AST/GS_ASTBuilder.h>

#endif //GSLANGUAGE_AST_H
