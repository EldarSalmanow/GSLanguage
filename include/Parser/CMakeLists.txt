project(GSParserLibrary)

set(PARSER_DIR ${SOURCE_DIR}/Parser)

set(GS_PARSER_SOURCE
        ${PARSER_DIR}/GS_Parser.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Parser)
