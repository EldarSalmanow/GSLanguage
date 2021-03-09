set(LIBRARY_NAME GSLexerLibrary)

set(GS_LEXER_SOURCE
        ../../../src/Compiler/Lexer/GS_Lexer.cpp
        ../../../src/Compiler/Lexer/GS_Keywords.cpp
        ../../../src/Compiler/Lexer/GS_Regex.cpp)

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Lexer source
        ${GS_LEXER_SOURCE}
)