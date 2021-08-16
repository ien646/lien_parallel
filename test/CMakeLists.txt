include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2
  GIT_TAG c4e3767e265808590986d5db6ca1b5532a7f3d13 # v2.13.7
)
FetchContent_MakeAvailable(catch2)

SET(SOURCES
    src/main.cpp
    src/parallel.cpp
    src/parallel_benchmarks.cpp
)

add_executable(lien_parallel_tests ${SOURCES})
target_link_libraries(lien_parallel_tests lien_parallel Catch2::Catch2)