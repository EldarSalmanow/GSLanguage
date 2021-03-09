set(LIBRARY_NAME GSDebugLibrary)

set(GS_DEBUG_SOURCE
        ../../src/Debug/GS_Debug.cpp)

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Parser source
        ${GS_DEBUG_SOURCE}
)