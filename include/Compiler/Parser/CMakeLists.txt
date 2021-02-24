set(LIBRARY_NAME GSParserLibrary)

set(GS_PARSER_HEADERS
        GS_Parser.h
        GS_Expression.h
        )

set(GS_PARSER_SOURCE
        ../../../src/Compiler/Parser/GS_Parser.cpp
        )

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