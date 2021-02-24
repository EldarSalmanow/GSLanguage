set(LIBRARY_NAME GSLexerLibrary)

set(GS_LEXER_HEADERS
        GS_Lexer.h
        GS_Tokenizer.h
        GS_Token.h
        GS_Keywords.h
        GS_Regex.h
        )

set(GS_LEXER_SOURCE
        ../../../src/Compiler/Lexer/GS_Lexer.cpp
        ../../../src/Compiler/Lexer/GS_Keywords.cpp
        ../../../src/Compiler/Lexer/GS_Regex.cpp
        )

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Lexer headers
        ${GS_LEXER_HEADERS}
#       Lexer source
        ${GS_LEXER_SOURCE}
)