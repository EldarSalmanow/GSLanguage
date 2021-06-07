cmake_minimum_required(VERSION 3.17)

project(GSLanguage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
        main.cpp)

include_directories(include)

add_subdirectory(include/Debug)
add_subdirectory(include/Starter)
add_subdirectory(include/Reader)
add_subdirectory(include/Lexer)
add_subdirectory(include/Parser)
add_subdirectory(include/CodeGenerator)
add_subdirectory(include/ArgumentsParser)
add_subdirectory(include/CrossPlatform)

target_link_libraries(${PROJECT_NAME}
        GSStarterLibrary
        GSReaderLibrary
        GSLexerLibrary
        GSParserLibrary
        GSCodeGeneratorLibrary
        GSArgumentsParserLibrary
        GSCrossPlatformLibrary
        GSDebugLibrary
        )
