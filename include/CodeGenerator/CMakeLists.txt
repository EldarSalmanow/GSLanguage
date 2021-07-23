project(GSCodeGeneratorLibrary)

set(CODEGENERATOR_DIR ${SOURCE_DIR}/CodeGenerator)

set(GS_CODEGENERATOR_SOURCE
        ${CODEGENERATOR_DIR}/GS_CodeGenerator.cpp
        ${CODEGENERATOR_DIR}/GS_VMImage.cpp
        ${CODEGENERATOR_DIR}/GS_Opcode.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Code generator source
        ${GS_CODEGENERATOR_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/CodeGenerator)
