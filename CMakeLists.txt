cmake_minimum_required(VERSION 3.17)

project(GSLanguage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
        main.cpp)

include_directories(include)

add_subdirectory(include/Debug)
add_subdirectory(include/Starter)
add_subdirectory(include/Compiler/Reader)
add_subdirectory(include/Compiler/Lexer)
add_subdirectory(include/Compiler/Parser)
add_subdirectory(include/Compiler/CodeGenerator)
add_subdirectory(include/Compiler/Util)

target_link_libraries(${PROJECT_NAME}
        GSStarterLibrary
        GSReaderLibrary
        GSLexerLibrary
        GSParserLibrary
        GSCodeGeneratorLibrary
        GSUtilLibrary
        GSDebugLibrary
        )
