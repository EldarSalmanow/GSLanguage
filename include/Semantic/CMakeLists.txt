project(GSSemanticLibrary)

set(SEMANTIC_DIR ${SOURCE_DIR}/Semantic)

set(GS_SEMANTIC_SOURCE
        ${SEMANTIC_DIR}/GS_Semantic.cpp

        ${SEMANTIC_DIR}/GS_SemanticPass.cpp

        ${SEMANTIC_DIR}/GS_TypeCheckerPass.cpp
        ${SEMANTIC_DIR}/GS_TypePlaceholderPass.cpp
        ${SEMANTIC_DIR}/GS_VariablesPlaceholderPass.cpp

        ${SEMANTIC_DIR}/GS_TableOfVariables.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Semantic source
        ${GS_SEMANTIC_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Semantic)