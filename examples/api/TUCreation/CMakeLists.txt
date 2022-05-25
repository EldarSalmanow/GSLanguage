cmake_minimum_required(VERSION 3.16)

project(TUCreation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO add GSCompiler project for working with compiler API

find_package(GSCompiler REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

# ...
