project(GSCrossPlatformLibrary)

set(GS_CROSS_PLATFORM_SOURCE
        ../../src/CrossPlatform/GS_CrossPlatform.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Cross platform source
        ${GS_CROSS_PLATFORM_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../CrossPlatform)
