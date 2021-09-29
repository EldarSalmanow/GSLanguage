project(GSReaderLibrary)

set(READER_DIR ${SOURCE_DIR}/Reader)

set(GS_READER_SOURCE
#        ${READER_DIR}/GS_ReaderRunner.cpp
        ${READER_DIR}/GS_Reader.cpp
        ${READER_DIR}/GS_Code.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Reader source
        ${GS_READER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Reader)
