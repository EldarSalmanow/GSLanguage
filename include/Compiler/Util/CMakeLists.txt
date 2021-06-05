project(GSUtilLibrary)

set(GS_UTIL_SOURCE
        ../../../src/Compiler/Util/GS_Arguments.cpp
        ../../../src/Compiler/Util/GS_CrossPlatform.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Util source
        ${GS_UTIL_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ../Util)
