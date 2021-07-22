project(GSOptimizerLibrary)

set(OPTIMIZER_DIR ${SOURCE_DIR}/Optimizer)

set(GS_OPTIMIZER_SOURCE
        ${OPTIMIZER_DIR}/GS_Optimizer.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Optimizer source
        ${GS_OPTIMIZER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Optimizer)