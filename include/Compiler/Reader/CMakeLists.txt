set(LIBRARY_NAME GSReaderLibrary)

set(GS_READER_SOURCE
        ../../../src/Compiler/Reader/GS_Reader.cpp
        )

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Reader source
        ${GS_READER_SOURCE}
)