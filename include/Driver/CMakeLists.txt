project(GSDriverLibrary)

set(DRIVER_DIR ${SOURCE_DIR}/Driver)

set(GS_DRIVER_SOURCE
        ${DRIVER_DIR}/GS_Arguments.cpp

        ${DRIVER_DIR}/GS_Session.cpp
        ${DRIVER_DIR}/GS_SessionsManager.cpp

        ${DRIVER_DIR}/GS_Compiler.cpp

        ${DRIVER_DIR}/GS_GlobalContext.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Driver source
        ${GS_DRIVER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Driver)
