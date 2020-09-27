cmake_minimum_required(VERSION 3.0.0)
project(test1 VERSION 0.1.0)

set(VCPKG_LIBRARY_LINKAGE static)

if(NOT BINARY_NAME)
    set(BINARY_NAME TestCmake)
endif()

project(${BINARY_NAME})

file(GLOB_RECURSE fileCollection "src/*.c")

find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)

add_executable(${BINARY_NAME} ${fileCollection})

target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2_image)
target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2_gfx)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
