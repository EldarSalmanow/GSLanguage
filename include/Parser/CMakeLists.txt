project(GSParserLibrary)

set(PARSER_DIR ${SOURCE_DIR}/Parser)

set(GS_PARSER_SOURCE
        ${PARSER_DIR}/GS_Parser.cpp
        ${PARSER_DIR}/GS_ExpressionParser.cpp

        ${PARSER_DIR}/Nodes/GS_Value.cpp
        ${PARSER_DIR}/Nodes/GS_IntegerValue.cpp

        ${PARSER_DIR}/Nodes/GS_ValueNode.cpp

        ${PARSER_DIR}/Nodes/GS_BinaryNode.cpp
        ${PARSER_DIR}/Nodes/GS_UnaryNode.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Parser)
