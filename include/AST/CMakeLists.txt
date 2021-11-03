project(GSASTLibrary)

set(AST_DIR ${SOURCE_DIR}/AST)

set(GS_AST_SOURCE
        ${AST_DIR}/GS_Node.cpp

        ${AST_DIR}/GS_Declaration.cpp
        ${AST_DIR}/GS_Statement.cpp
        ${AST_DIR}/GS_Expression.cpp

        ${AST_DIR}/Declarations/GS_FunctionDeclaration.cpp

        ${AST_DIR}/Statements/GS_VariableDeclarationStatement.cpp
        ${AST_DIR}/Statements/GS_AssignmentStatement.cpp
        ${AST_DIR}/Statements/GS_ExpressionStatement.cpp

        ${AST_DIR}/Expressions/GS_ConstantExpression.cpp
        ${AST_DIR}/Expressions/GS_UnaryExpression.cpp
        ${AST_DIR}/Expressions/GS_BinaryExpression.cpp
        ${AST_DIR}/Expressions/GS_VariableUsingExpression.cpp
        ${AST_DIR}/Expressions/GS_FunctionCallingExpression.cpp

        ${AST_DIR}/GS_Type.cpp

        ${AST_DIR}/GS_Visitor.cpp ../../src/AST/GS_Pass.cpp ../../src/AST/Statements/GS_DeclarationStatement.cpp ../../src/AST/Declarations/GS_VariableDeclaration.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       AST source
        ${GS_AST_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/AST)