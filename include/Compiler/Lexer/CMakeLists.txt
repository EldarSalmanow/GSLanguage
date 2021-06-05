project(GSLexerLibrary)

set(GS_LEXER_SOURCE
        ../../../src/Compiler/Lexer/GS_Lexer.cpp
        ../../../src/Compiler/Lexer/GS_Keywords.cpp
        ../../../src/Compiler/Lexer/GS_Regex.cpp
        ../../../src/Compiler/Lexer/GS_Token.cpp
        ../../../src/Compiler/Lexer/GS_Position.cpp
        ../../../src/Compiler/Lexer/GS_Coordinate.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Lexer source
        ${GS_LEXER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../Lexer)
