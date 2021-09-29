project(GSParserLibrary)

set(PARSER_DIR ${SOURCE_DIR}/Parser)

set(GS_PARSER_SOURCE
        ${PARSER_DIR}/GS_Parser.cpp

        ${PARSER_DIR}/Nodes/GS_Node.cpp

        ${PARSER_DIR}/Nodes/GS_RootNode.cpp

        ${PARSER_DIR}/Nodes/GS_BlockNode.cpp

        ${PARSER_DIR}/Nodes/GS_ValueNode.cpp

        ${PARSER_DIR}/Nodes/GS_BinaryNode.cpp
        ${PARSER_DIR}/Nodes/GS_UnaryNode.cpp

        ${PARSER_DIR}/Nodes/GS_AssignmentNode.cpp

        ${PARSER_DIR}/Nodes/GS_VariableDeclarationNode.cpp
        ${PARSER_DIR}/Nodes/GS_VariableUsingNode.cpp

        ${PARSER_DIR}/Visitors/GS_PrintVisitor.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_PARSER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Parser)
