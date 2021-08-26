project(GSExceptionsLibrary)

set(EXCEPTIONS_DIR ${SOURCE_DIR}/Exceptions)

set(GS_EXCEPTIONS_SOURCE
        ${EXCEPTIONS_DIR}/GS_ErrorHandler.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Exceptions source
        ${GS_EXCEPTIONS_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Exceptions)