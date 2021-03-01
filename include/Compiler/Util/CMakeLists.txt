set(LIBRARY_NAME GSUtilLibrary)

set(GS_UTIL_HEADERS
        GS_Arguments.h
        )

set(GS_UTIL_SOURCE
        ../../../src/Compiler/Util/GS_Arguments.cpp
        )

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Util headers
        ${GS_UTIL_HEADERS}
#       Util source
        ${GS_UTIL_SOURCE}
)