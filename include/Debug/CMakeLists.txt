set(LIBRARY_NAME GSDebugLibrary)

set(GS_DEBUG_SOURCE
        ../../src/Debug/GS_Debug.cpp ../../src/Debug/GS_Timer.cpp)

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Debug source
        ${GS_DEBUG_SOURCE}
)