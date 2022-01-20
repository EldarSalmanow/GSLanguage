add_executable(GSReaderTests GS_ReaderTests.cpp)

target_link_directories(GSReaderTests PRIVATE ${CONAN_LIB_DIRS})

target_link_libraries(GSReaderTests PRIVATE ${CONAN_LIBS})

target_link_libraries(GSReaderTests PRIVATE ${PROJECT_LIBRARIES})

#add_executable(GSLexerTests GS_LexerTests.cpp)
#
#target_link_directories(GSLexerTests PRIVATE ${CONAN_LIB_DIRS})
#
#target_link_libraries(GSLexerTests PRIVATE ${CONAN_LIBS})
#
#target_link_libraries(GSLexerTests PRIVATE ${PROJECT_LIBRARIES})
