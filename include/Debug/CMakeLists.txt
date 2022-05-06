project(GSDebugLibrary)

set(DEBUG_DIR ${SOURCE_DIR}/Debug)

set(GS_DEBUG_SOURCE
        ${DEBUG_DIR}/GS_Dumper.cpp

        ${DEBUG_DIR}/GS_ASTDumper.cpp

        ${DEBUG_DIR}/GS_TableOfSymbolsDumper.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Debug source
        ${GS_DEBUG_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Debug)
