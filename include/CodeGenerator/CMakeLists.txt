project(GSCodeGeneratorLibrary)

set(GS_CODEGENERATOR_SOURCE
        ../../src/CodeGenerator/GS_CodeGenerator.cpp
        ../../src/CodeGenerator/GS_Section.cpp
        ../../src/CodeGenerator/GS_Variable.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Code generator source
        ${GS_CODEGENERATOR_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../CodeGenerator)
