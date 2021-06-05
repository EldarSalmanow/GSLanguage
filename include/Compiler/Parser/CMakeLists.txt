project(GSParserLibrary)

set(GS_PARSER_SOURCE
        ../../../src/Compiler/Parser/GS_Parser.cpp
        ../../../src/Compiler/Parser/GS_ExpressionParser.cpp
        ../../../src/Compiler/Parser/GS_VariableParser.cpp
        ../../../src/Compiler/Parser/Values/GS_LiteralTypes.cpp
        ../../../src/Compiler/Parser/Values/GS_Value.cpp
        ../../../src/Compiler/Parser/Values/GS_StringValue.cpp
        ../../../src/Compiler/Parser/Values/GS_IntegerValue.cpp
        ../../../src/Compiler/Parser/Expressions/GS_ValueExpression.cpp
        ../../../src/Compiler/Parser/Expressions/GS_BinaryExpression.cpp
        ../../../src/Compiler/Parser/Expressions/GS_UnaryExpression.cpp
        ../../../src/Compiler/Parser/Statements/GS_VariableDeclarationStatement.cpp
        ../../../src/Compiler/Parser/Statements/GS_AssignmentStatement.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../Parser)
