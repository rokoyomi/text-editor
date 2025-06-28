cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

project(document)

file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        include/
)

enable_testing()

add_executable(${PROJECT_NAME}_test
    test/document_test.cpp
)

target_link_libraries(${PROJECT_NAME}_test
    ${PROJECT_NAME}
    gtest
    pthread
)

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME}_test)
