project(GSLexerLibrary)

set(LEXER_DIR ${SOURCE_DIR}/Lexer)

set(GS_LEXER_SOURCE
        ${LEXER_DIR}/GS_Lexer.cpp
        ${LEXER_DIR}/GS_Keywords.cpp
        ${LEXER_DIR}/GS_Regex.cpp
        ${LEXER_DIR}/GS_Token.cpp
        ${LEXER_DIR}/GS_Position.cpp
        ${LEXER_DIR}/GS_Coordinate.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Lexer source
        ${GS_LEXER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Lexer)
