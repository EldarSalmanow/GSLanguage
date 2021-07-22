project(GSArgumentsParserLibrary)

set(ARGUMENTS_PARSER_DIR ${SOURCE_DIR}/ArgumentsParser)

set(GS_ARGUMENTS_PARSER_SOURCE
        ${ARGUMENTS_PARSER_DIR}/GS_Arguments.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Arguments parser source
        ${GS_ARGUMENTS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/ArgumentsParser)
