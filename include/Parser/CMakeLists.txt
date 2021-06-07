project(GSParserLibrary)

set(GS_PARSER_SOURCE
        ../../src/Parser/GS_Parser.cpp
        ../../src/Parser/GS_ExpressionParser.cpp
        ../../src/Parser/GS_VariableParser.cpp
        ../../src/Parser/Values/GS_LiteralTypes.cpp
        ../../src/Parser/Values/GS_Value.cpp
        ../../src/Parser/Values/GS_StringValue.cpp
        ../../src/Parser/Values/GS_IntegerValue.cpp
        ../../src/Parser/Expressions/GS_ValueExpression.cpp
        ../../src/Parser/Expressions/GS_BinaryExpression.cpp
        ../../src/Parser/Expressions/GS_UnaryExpression.cpp
        ../../src/Parser/Statements/GS_VariableDeclarationStatement.cpp
        ../../src/Parser/Statements/GS_AssignmentStatement.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../Parser)
