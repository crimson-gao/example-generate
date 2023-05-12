cmake_minimum_required(VERSION 3.0)
project(example)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES "src/*.cc")
message("test" ${SOURCES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(codegen ${SOURCES})