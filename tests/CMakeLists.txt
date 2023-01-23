include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(test_median_of_two_sorted_arrays TestMedianOfTwoSortedArrays.cpp)

target_link_libraries(test_median_of_two_sorted_arrays
PRIVATE
    GTest::GTest
    solution)

add_test(gtest_median_of_two_sorted_arrays test_median_of_two_sorted_arrays)
