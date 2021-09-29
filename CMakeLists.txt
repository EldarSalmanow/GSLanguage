cmake_minimum_required(VERSION 3.16)

project(GSLanguage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_DIR   ${PROJECT_SOURCE_DIR})
set(SOURCE_DIR    ${PROJECT_DIR}/src)
set(INCLUDE_DIR   ${PROJECT_DIR}/include)
set(EXTERNAL_DIR  ${PROJECT_DIR}/external)
set(BINARY_DIR    ${PROJECT_DIR}/bin)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

find_package(LLVM REQUIRED CONFIG)

if (LLVM_FOUND)
    message(STATUS "LLVM found!")
else()
    message(FATAL "LLVM not found!")
endif()

add_subdirectory(${EXTERNAL_DIR}/rang)

add_subdirectory(${EXTERNAL_DIR}/GSCrossPlatform)

set(PROJECT_LIBRARIES
#        GSStarterLibrary
        GSReaderLibrary
        GSLexerLibrary
#        GSDebugLibrary
#        GSCodeGeneratorLibrary
#        GSSemanticLibrary
#        GSOptimizerLibrary
#        GSParserLibrary
#        GSExceptionsLibrary
#        GSCrossPlatformLibrary
        )

add_executable(${PROJECT_NAME}
        ${PROJECT_DIR}/main.cpp)

include_directories(${GS_CROSS_PLATFORM_INCLUDE_DIR})

target_link_libraries(${GS_CROSS_PLATFORM_LIBRARY_NAME})

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${RANG_INCLUDE_DIR})
include_directories(${INCLUDE_DIR})

#add_subdirectory(${INCLUDE_DIR}/Debug)
#add_subdirectory(${INCLUDE_DIR}/Starter)
add_subdirectory(${INCLUDE_DIR}/Reader)
add_subdirectory(${INCLUDE_DIR}/Lexer)
#add_subdirectory(${INCLUDE_DIR}/Parser)
#add_subdirectory(${INCLUDE_DIR}/Semantic)
#add_subdirectory(${INCLUDE_DIR}/Optimizer)
#add_subdirectory(${INCLUDE_DIR}/CodeGenerator)
#add_subdirectory(${INCLUDE_DIR}/CrossPlatform)
#add_subdirectory(${INCLUDE_DIR}/Exceptions)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINARY_DIR})
