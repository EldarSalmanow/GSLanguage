project(GSDriverLibrary)

set(DRIVER_DIR ${SOURCE_DIR}/Driver)

set(GS_DRIVER_SOURCE
        ${DRIVER_DIR}/GS_Compiler.cpp

        ${DRIVER_DIR}/GS_SessionsManager.cpp
        ${DRIVER_DIR}/GS_Session.cpp
        ${DRIVER_DIR}/GS_SessionContext.cpp

        ${DRIVER_DIR}/GS_TranslationUnitsManager.cpp
        ${DRIVER_DIR}/GS_TranslationUnit.cpp
        ${DRIVER_DIR}/GS_TranslationUnitConfig.cpp

        ${DRIVER_DIR}/GS_Toolchains.cpp)

add_library(
#       Library name
        ${PROJECT_NAME}
#       Library type
        STATIC
#       Driver source
        ${GS_DRIVER_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/Driver)
