set(LIBRARY_NAME GSStarterLibrary)

set(GS_STARTER_SOURCE
        ../../src/Starter/GS_Starter.cpp
        )

add_library(
#       Library name
        ${LIBRARY_NAME}
#       Library type
        STATIC
#       Starter source
        ${GS_STARTER_SOURCE}
)