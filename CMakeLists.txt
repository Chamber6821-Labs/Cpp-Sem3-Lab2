cmake_minimum_required(VERSION 3.26)
project(Sem3_Lab1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(reactions-src)

add_executable(Sem3_Lab1 main.cpp task.cpp task.h)
target_link_libraries(Sem3_Lab1 Reactions::Reactions)

add_executable(brainhack brainhack.cpp brainhack.h)
target_link_libraries(brainhack Reactions::Reactions)

include(FetchContent)
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)
FetchContent_GetProperties(doctest)
add_executable(brainhack_test brainhack.test.cpp)
target_link_libraries(brainhack_test PRIVATE doctest_with_main)



