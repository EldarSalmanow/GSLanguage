cmake_minimum_required(VERSION 3.16)
project(GSBCCodeGenLibrary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GS_BC_CODEGEN_PROJECT_DIR   ${PROJECT_SOURCE_DIR})
set(GS_BC_CODEGEN_SOURCE_DIR    ${GS_BC_CODEGEN_PROJECT_DIR}/src     CACHE STRING "BCCodeGen source dir")
set(GS_BC_CODEGEN_INCLUDE_DIR   ${GS_BC_CODEGEN_PROJECT_DIR}/include CACHE STRING "BCCodeGen include directory")
set(GS_BC_CODEGEN_LIBRARY_NAME  GSBCCodeGenLibrary                   CACHE STRING "GCCodeGen library name")

set(GS_BC_CODEGEN_SOURCE
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCNodes.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCOpcodeType.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCVisitors.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCBuilder.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCCompiler.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCWriter.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCReader.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCLowDecompiler.cpp
        ${GS_BC_CODEGEN_SOURCE_DIR}/GS_BCHighDecompiler.cpp)

add_library(
#       Library name
        GSBCCodeGenLibrary
#       Library type
        STATIC
#       BCCodeGen sources
        ${GS_BC_CODEGEN_SOURCE}
)

target_include_directories(GSBCCodeGenLibrary PRIVATE ${GS_BC_CODEGEN_INCLUDE_DIR}/GSBCCodeGen)
