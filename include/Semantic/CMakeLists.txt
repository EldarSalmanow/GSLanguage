project(GSSemanticLibrary)

set(SEMANTIC_DIR ${SOURCE_DIR}/Semantic)

set(GS_SEMANTIC_SOURCE
        ${SEMANTIC_DIR}/GS_Type.cpp

        ${SEMANTIC_DIR}/GS_TableOfSymbols.cpp

        ${SEMANTIC_DIR}/GS_SemanticAnalyzer.cpp

        ${SEMANTIC_DIR}/Passes/GS_SymbolsPlaceholderPass.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Semantic source
        ${GS_SEMANTIC_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Semantic)