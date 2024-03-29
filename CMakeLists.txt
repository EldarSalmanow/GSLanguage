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

if (${MSVC})
    add_compile_options(/utf-8)
endif()

set(EXTERNAL_INCLUDE_DIRS )
set(EXTERNAL_LIBS         )

# LLVM

find_package(LLVM REQUIRED)

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(LLVM_LIBS all)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         ${LLVM_LIBS})

# LLD

find_package(LLD REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${LLD_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         lldCommon lldCOFF)

# GSCrossPlatform

find_package(GSCrossPlatform REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${GSCrossPlatform_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         ${GSCrossPlatform_LIBRARIES})

# GTest

find_package(GTest REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${GTest_INCLUDE_DIRS})
set(EXTERNAL_LIBS         ${EXTERNAL_LIBS}         ${GTest_LIBRARIES})

# rang

find_package(rang REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${rang_INCLUDE_DIRS})

# args (taywee-args)

find_package(args REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${args_INCLUDE_DIRS})

set(PROJECT_LIBS
        GSDriverLibrary
        GSIOLibrary
        GSLexerLibrary
        GSParserLibrary
        GSASTLibrary
        GSOptimizerLibrary
        GSSemanticLibrary
        GSCodeGeneratorLibrary
        GSDebugLibrary)

add_executable(${PROJECT_NAME}
        ${PROJECT_DIR}/main.cpp)

include_directories(${EXTERNAL_INCLUDE_DIRS})

include_directories(${INCLUDE_DIR})

add_subdirectory(${INCLUDE_DIR}/Driver)
add_subdirectory(${INCLUDE_DIR}/IO)
add_subdirectory(${INCLUDE_DIR}/Lexer)
add_subdirectory(${INCLUDE_DIR}/Parser)
add_subdirectory(${INCLUDE_DIR}/AST)
add_subdirectory(${INCLUDE_DIR}/Optimizer)
add_subdirectory(${INCLUDE_DIR}/Semantic)
add_subdirectory(${INCLUDE_DIR}/CodeGenerator)
add_subdirectory(${INCLUDE_DIR}/Debug)

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTERNAL_LIBS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBS})

#add_subdirectory(tests)

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
