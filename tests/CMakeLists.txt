add_executable(GSIOTests GS_IOTests.cpp)

target_link_libraries(GSIOTests PRIVATE ${EXTERNAL_LIBS})

target_link_libraries(GSIOTests PRIVATE ${PROJECT_LIBS})

add_executable(GSLexerTests GS_LexerTests.cpp)

target_link_libraries(GSLexerTests PRIVATE ${EXTERNAL_LIBS})

target_link_libraries(GSLexerTests PRIVATE ${PROJECT_LIBS})
