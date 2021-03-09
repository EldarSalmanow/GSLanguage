set(LIBRARY_NAME GSParserLibrary)

set(GS_PARSER_SOURCE
        ../../../src/Compiler/Parser/GS_Parser.cpp
        ../../../src/Compiler/Parser/Values/GS_LiteralTypes.cpp)

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_PARSER_SOURCE}
)