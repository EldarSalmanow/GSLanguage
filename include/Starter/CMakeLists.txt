project(GSStarterLibrary)

set(STARTER_DIR ${SOURCE_DIR}/Starter)

set(GS_STARTER_SOURCE
        ${STARTER_DIR}/GS_Starter.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Starter source
        ${GS_STARTER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Starter)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GS_BC_CODEGEN_LIBRARY_NAME})
