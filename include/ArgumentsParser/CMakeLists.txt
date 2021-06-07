project(GSArgumentsParserLibrary)

set(GS_ARGUMENTS_PARSER_SOURCE
        ../../src/ArgumentsParser/GS_Arguments.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Arguments parser source
        ${GS_ARGUMENTS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../ArgumentsParser)
