cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "json_wrapper")
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Werror
    -Wextra
    -Wpedantic
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g
        -O0
    )
else()
    add_compile_options(
        -O3
    )
endif()

set(SRC_DIR
    ${PROJECT_SOURCE_DIR}/src
)

set(SRC_LIST
    ${SRC_DIR}/json_parser.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_LIST}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        RapidJSON
)
