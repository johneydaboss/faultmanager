cmake_minimum_required(VERSION 3.20)
project(faultmanager C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(faultmanager)

add_executable(faultmanager_app main.c)

target_include_directories(faultmanager_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/faultmanager/src
    ${CMAKE_CURRENT_SOURCE_DIR}/faultmanager/cnf
    ${CMAKE_CURRENT_SOURCE_DIR}/faultmanager/stubs
)

target_link_libraries(faultmanager_app PRIVATE faultmanager)

add_custom_target(distclean
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/CMakeFiles"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/CMakeCache.txt"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/cmake_install.cmake"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_BINARY_DIR}/Makefile"
    COMMENT "Remove generated CMake build metadata from the build directory"
)
