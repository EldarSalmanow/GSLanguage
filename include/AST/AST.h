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
 * Declarations/GS_ModuleDeclaration.h          - Pass
 * Declarations/GS_ClassDeclaration.h           - Pass
 * Declarations/GS_FunctionDeclaration.h        - Pass
 * Declarations/GS_ImportDeclaration.h          - Pass
 * Statements/GS_VariableDeclarationStatement.h - Pass
 * Statements/GS_AssignmentStatement.h          - Pass
 * Statements/GS_IfStatement.h                  - Pass
 * Statements/GS_ForStatement.h                 - Pass
 * Statements/GS_WhileStatement.h               - Pass
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
#include <AST/Declarations/GS_ModuleDeclaration.h>
#include <AST/Declarations/GS_ClassDeclaration.h>
#include <AST/Declarations/GS_FunctionDeclaration.h>
#include <AST/Declarations/GS_ImportDeclaration.h>

#include <AST/Statements/GS_VariableDeclarationStatement.h>
#include <AST/Statements/GS_AssignmentStatement.h>
#include <AST/Statements/GS_IfStatement.h>
#include <AST/Statements/GS_ForStatement.h>
#include <AST/Statements/GS_WhileStatement.h>
#include <AST/Statements/GS_ReturnStatement.h>
#include <AST/Statements/GS_ExpressionStatement.h>

#include <AST/Expressions/GS_ConstantExpression.h>
#include <AST/Expressions/GS_UnaryExpression.h>
#include <AST/Expressions/GS_BinaryExpression.h>
#include <AST/Expressions/GS_ArrayExpression.h>
#include <AST/Expressions/GS_VariableUsingExpression.h>
#include <AST/Expressions/GS_FunctionCallingExpression.h>
#include <AST/Expressions/GS_IndexExpression.h>

#include <AST/GS_Visitor.h>

#include <AST/GS_Pass.h>

#include <AST/GS_ASTContext.h>

#include <AST/GS_ASTBuilder.h>

namespace GSLanguageCompiler::AST {

    /*
     * Life.gs
     *
     * module Life {
     *
     *     class Person {
     *         constructor(name: String, age: I32) {
     *             self.name = name
     *             self.age = age
     *         }
     *
     *         func get_name(self) {
     *             return self.name
     *         }
     *
     *         func get_age(self) {
     *             return self.age
     *         }
     *
     *         name: String
     *         age: I32
     *     }
     *
     * }
     *
     * main.gs
     *
     * import Life
     *
     * func main() {
     *     var p = Person {"Hi", 12}
     * }
     *
     */

    void g() {
        auto Person_class = GS_ClassDeclaration::Create("Person",
                                                        {
                                                                GS_ClassField::Create("name",
                                                                                      Semantic::GS_StringType::Create()),
                                                                GS_ClassField::Create("age",
                                                                                      Semantic::GS_I32Type::Create())
                                                        },
                                                        {
                                                                GS_ClassMethod::Create("get_name",
                                                                                       {/*...*/}),
                                                                GS_ClassMethod::Create("get_age",
                                                                                       {/*...*/})
                                                        });

        auto Person_class_name_field = Person_class->GetField("name");

        Person_class_name_field.GetName(); // "name"
        Person_class_name_field.GetType(); // String

        auto Life_module = GS_ModuleDeclaration::Create("Life",
                                                        {
            Person_class
                                                        });

        auto Life_unit = GS_TranslationUnitDeclaration::Create("Life",
                                                               {
            Life_module
                                                               });

        auto Life_import = GS_ImportDeclaration::Create("Life");

        auto Main_unit = GS_TranslationUnitDeclaration::Create("main",
                                                               {
            Life_import
                                                               });
    }

}

#endif //GSLANGUAGE_AST_H
