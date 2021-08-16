cmake_minimum_required(VERSION 3.15)

project(lien_parallel LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

set(SOURCES
    "src/parallel.cpp"
    "src/task_queue.cpp"
)

add_library(lien_parallel ${SOURCES})

set_target_properties(lien_parallel PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(lien_parallel PUBLIC include)
target_link_libraries(lien_parallel Threads::Threads)