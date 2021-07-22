project(GSCrossPlatformLibrary)

set(CROSS_PLATFORM_DIR ${SOURCE_DIR}/CrossPlatform)

set(GS_CROSS_PLATFORM_SOURCE
        ${CROSS_PLATFORM_DIR}/GS_CrossPlatform.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Cross platform source
        ${GS_CROSS_PLATFORM_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/CrossPlatform)
