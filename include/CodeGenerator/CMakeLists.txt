project(GSCodeGeneratorLibrary)

set(CODEGENERATOR_DIR ${SOURCE_DIR}/CodeGenerator)

set(GS_CODEGENERATOR_SOURCE
        ${CODEGENERATOR_DIR}/GS_Backend.cpp

        ${CODEGENERATOR_DIR}/LLVM/GS_LLVMBackend.cpp
        ${CODEGENERATOR_DIR}/LLVM/GS_LLVMVisitor.cpp

        ${CODEGENERATOR_DIR}/GS_CodeGenerator.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Code generator source
        ${GS_CODEGENERATOR_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/CodeGenerator)

llvm_map_components_to_libnames(LLVM_LIBS core native)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LLVM_LIBS})
