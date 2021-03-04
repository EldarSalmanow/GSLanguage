set(LIBRARY_NAME GSParserLibrary)

set(GS_PARSER_HEADERS
        GS_Parser.h
        Expressions/GS_Expression.h
        Statements/GS_VariableStatement.h GS_IncludeStatements.h Values/GS_Value.h Values/GS_IntegerValue.h Values/LiteralTypes.h)

set(GS_PARSER_SOURCE
        ../../../src/Compiler/Parser/GS_Parser.cpp
        ../../../src/Compiler/Parser/Values/GS_LiteralTypes.cpp)

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Parser headers
        ${GS_PARSER_HEADERS}
#       Parser source
        ${GS_PARSER_SOURCE}
)