project(GSASTLibrary)

set(AST_DIR ${SOURCE_DIR}/AST)

set(GS_AST_SOURCE
        ${AST_DIR}/GS_Node.cpp

        ${AST_DIR}/GS_Declaration.cpp
        ${AST_DIR}/GS_Statement.cpp
        ${AST_DIR}/GS_Expression.cpp

        ${AST_DIR}/Declarations/GS_TranslationUnitDeclaration.cpp
        ${AST_DIR}/Declarations/GS_ModuleDeclaration.cpp
        ${AST_DIR}/Declarations/GS_ImportDeclaration.cpp
        ${AST_DIR}/Declarations/GS_FunctionDeclaration.cpp

        ${AST_DIR}/Statements/GS_VariableDeclarationStatement.cpp
        ${AST_DIR}/Statements/GS_AssignmentStatement.cpp
        ${AST_DIR}/Statements/GS_IfStatement.cpp
        ${AST_DIR}/Statements/GS_ForStatement.cpp
        ${AST_DIR}/Statements/GS_WhileStatement.cpp
        ${AST_DIR}/Statements/GS_MatchStatement.cpp
        ${AST_DIR}/Statements/GS_ReturnStatement.cpp
        ${AST_DIR}/Statements/GS_ExpressionStatement.cpp

        ${AST_DIR}/Expressions/GS_LiteralExpression.cpp
        ${AST_DIR}/Expressions/GS_ArrayExpression.cpp
        ${AST_DIR}/Expressions/GS_RangeExpression.cpp
        ${AST_DIR}/Expressions/GS_UnaryExpression.cpp
        ${AST_DIR}/Expressions/GS_BinaryExpression.cpp
        ${AST_DIR}/Expressions/GS_IndexExpression.cpp
        ${AST_DIR}/Expressions/GS_CastExpression.cpp
        ${AST_DIR}/Expressions/GS_VariableUsingExpression.cpp
        ${AST_DIR}/Expressions/GS_FunctionCallingExpression.cpp

        ${AST_DIR}/GS_Visitor.cpp

        ${AST_DIR}/GS_Pass.cpp

        ${AST_DIR}/GS_ASTContext.cpp

        ${AST_DIR}/GS_ASTBuilder.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       AST source
        ${GS_AST_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/AST)