cmake_minimum_required(VERSION 3.17)

project(GSLanguage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include/Compiler/Lexer)
add_subdirectory(include/Compiler/Parser)
add_subdirectory(include/Compiler/Reader)
add_subdirectory(include/Compiler/Util)
add_subdirectory(include/Starter)


add_executable(${PROJECT_NAME}
        main.cpp
        )

target_link_libraries(${PROJECT_NAME}
        GSStarterLibrary
        GSUtilLibrary
        GSReaderLibrary
        GSLexerLibrary
        GSParserLibrary
        )
