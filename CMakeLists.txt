cmake_minimum_required(VERSION 3.16)

project(GSLanguage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BINARY_NAME  ${PROJECT_NAME})
set(PROJECT_DIR  ${PROJECT_SOURCE_DIR})
set(INCLUDE_DIR  ${PROJECT_DIR}/include)
set(SOURCE_DIR   ${PROJECT_DIR}/src)
set(EXTERNAL_DIR ${PROJECT_DIR}/external)
set(BINARY_DIR   ${PROJECT_DIR}/bin)

message(STATUS "GSLanguage")
message(STATUS "    BinaryName:  ${BINARY_NAME}")
message(STATUS "    ProjectDir:  ${PROJECT_DIR}")
message(STATUS "    IncludeDir:  ${INCLUDE_DIR}")
message(STATUS "    SourceDir:   ${SOURCE_DIR}")
message(STATUS "    BinaryDir:   ${BINARY_DIR}")

find_package(LLVM REQUIRED)

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

add_definitions(${LLVM_DEFINITIONS_LIST})

include(${EXTERNAL_DIR}/conanbuildinfo.cmake)

set(PROJECT_LIBRARIES
        GSReaderLibrary
        GSLexerLibrary
        GSASTLibrary
#        GSCodeGeneratorLibrary
#        GSSemanticLibrary
#        GSParserLibrary
        )

add_executable(${PROJECT_NAME}
        ${PROJECT_DIR}/main.cpp)

include_directories(${LLVM_INCLUDE_DIRS})

include_directories(${CONAN_INCLUDE_DIRS})

include_directories(${INCLUDE_DIR})

add_subdirectory(${INCLUDE_DIR}/Reader)
add_subdirectory(${INCLUDE_DIR}/Lexer)
add_subdirectory(${INCLUDE_DIR}/AST)
#add_subdirectory(${INCLUDE_DIR}/Parser)
#add_subdirectory(${INCLUDE_DIR}/Semantic)
#add_subdirectory(${INCLUDE_DIR}/CodeGenerator)

add_subdirectory(tests)

target_link_directories(${PROJECT_NAME} PRIVATE ${CONAN_LIB_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
