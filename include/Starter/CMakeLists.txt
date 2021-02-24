set(LIBRARY_NAME GSStarterLibrary)

set(GS_STARTER_HEADERS
        GS_Starter.h
        )

set(GS_STARTER_SOURCE
        ../../src/Starter/GS_Starter.cpp
        )

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Starter headers
        ${GS_STARTER_HEADERS}
#       Starter source
        ${GS_STARTER_SOURCE}
)