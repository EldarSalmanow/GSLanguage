project(GSInterpreterLibrary)

set(INTERPRETER_DIR ${SOURCE_DIR}/Interpreter)

set(GS_INTERPRETER_SOURCE
        ${INTERPRETER_DIR}/GS_Interpreter.cpp ../../src/Interpreter/GS_TableOfSymbols.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Interpreter source
        ${GS_INTERPRETER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Interpreter)