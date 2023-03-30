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

add_executable(test_two_sum TestTwoSum.cpp)
target_link_libraries(test_two_sum
PRIVATE
    GTest::GTest
    solution)
add_test(gtest_two_sum test_two_sum)

add_executable(test_add_two_numbers TestAddTwoNumbers.cpp)
target_link_libraries(test_add_two_numbers
PRIVATE
    GTest::GTest
    solution)
add_test(gtest_add_two_numbers test_add_two_numbers)

add_executable(test_length_of_longet_substring TestLengthOfLongestSubstring.cpp)
target_link_libraries(test_length_of_longet_substring
PRIVATE
    GTest::GTest
    solution)
add_test(gtest_length_of_longet_substring test_length_of_longet_substring)

add_executable(test_is_palindrome TestIsPalindrome.cpp)
target_link_libraries(test_is_palindrome
PRIVATE
    GTest::GTest
    solution)
add_test(gtest_is_palindrome test_is_palindrome)

add_executable(test_three_sum TestThreeSum.cpp)
target_link_libraries(test_three_sum
PRIVATE
    GTest::GTest
    solution)
add_test(gtest_three_sum test_three_sum)