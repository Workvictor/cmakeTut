cmake_minimum_required(VERSION 3.0.0)
project(test1 VERSION 0.1.0)

set(RELEASE_DIR "release")
set(SRC_DIR "src")
set(VCPKG_LIBRARY_LINKAGE static)

if(NOT BINARY_NAME)
    set(BINARY_NAME testCmake)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RELEASE_DIR})
file(COPY ${SRC_DIR}/res DESTINATION ${RELEASE_DIR})

project(${BINARY_NAME})

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.c)

find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)

add_executable(${BINARY_NAME} ${SRC_FILES})

target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2_image)
target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2_gfx)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
