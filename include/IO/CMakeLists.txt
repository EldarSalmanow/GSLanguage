project(GSIOLibrary)

set(IO_DIR ${SOURCE_DIR}/IO)

set(GS_IO_SOURCE
        ${IO_DIR}/GS_Stream.cpp

        ${IO_DIR}/GS_Symbol.cpp

        ${IO_DIR}/GS_Reader.cpp

        ${IO_DIR}/GS_TextStream.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       IO source
        ${GS_IO_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/IO)
