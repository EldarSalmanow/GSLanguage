project(GSLexerLibrary)

set(GS_LEXER_SOURCE
        ../../src/Lexer/GS_Lexer.cpp
        ../../src/Lexer/GS_Keywords.cpp
        ../../src/Lexer/GS_Regex.cpp
        ../../src/Lexer/GS_Token.cpp
        ../../src/Lexer/GS_Position.cpp
        ../../src/Lexer/GS_Coordinate.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Lexer source
        ${GS_LEXER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../Lexer)
