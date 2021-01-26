cmake_minimum_required(VERSION 3.17)

project(GSLanguage VERSION 0.1 LANGUAGES CXX)

#include_directories("C:\\Users\\Ruslan\\Desktop\\EldarFiles\\CXX\\googletest-master\\googletest\\include")
#include_directories("C:\\Users\\Ruslan\\Desktop\\EldarFiles\\CXX\\boost")

set(CMAKE_CXX_STANDARD 20)

add_executable(GSLanguage
#       Lexer headers
        include/Compiler/Lexer/GS_Lexer.h
        include/Compiler/Lexer/GS_Token.h
        include/Compiler/Lexer/GS_Keywords.h
        include/Compiler/Lexer/GS_Regex.h
#       Parser headers
        include/Compiler/Parser/GS_Parser.h
        include/Compiler/Parser/GS_Expression.h
        include/Compiler/Parser/GS_Statement.h
#       Reader headers
        include/Compiler/Reader/GS_Reader.h
#       Logging headers
#        include/Compiler/Logging/Logger.h
#       Util headers
        include/Compiler/Util/GS_Arguments.h
#       Exceptions headers
        include/Exceptions/GS_IException.h
        include/Exceptions/GS_Exception.h
        include/Exceptions/GS_LexerException.h
        include/Exceptions/GS_ParserException.h
        include/Exceptions/GS_ReaderException.h
        include/Exceptions/GS_ArgumentException.h
#       Testing headers
        test/Tests.h
#       Lexer sources
        src/Compiler/Lexer/GS_Lexer.cpp
        src/Compiler/Lexer/GS_Keywords.cpp
        src/Compiler/Lexer/GS_Regex.cpp
#       Parser sources
        src/Compiler/Parser/GS_Parser.cpp
#       Reader source
        src/Compiler/Reader/GS_Reader.cpp
#       Logging source
#        src/Compiler/Logging/Logger.cpp
#       Util source
        src/Compiler/Util/GS_Arguments.cpp
#       Main file
        main.cpp)

#add_executable(Test
##       Tests files
#        test/test.cpp)
