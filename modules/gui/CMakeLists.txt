cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

project(gui)

file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

# target_link_libraries(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        include/
)
