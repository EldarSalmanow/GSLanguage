project(GSSemanticLibrary)

set(SEMANTIC_DIR ${SOURCE_DIR}/Semantic)

set(GS_SEMANTIC_SOURCE
        ${SEMANTIC_DIR}/GS_TableOfSymbols.cpp ../../src/Semantic/Passes/GS_VariablesPlaceholderPass.cpp ../../src/Semantic/Visitors/GS_VariablesPlaceholderVisitor.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Semantic source
        ${GS_SEMANTIC_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Semantic)