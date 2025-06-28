cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

project(HoshiEditor)
enable_testing()

add_subdirectory(modules/document)
add_subdirectory(modules/gui)

# add_subdirectory(src)

file(GLOB_RECURSE HEADERS "src/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    document
    gui
)
