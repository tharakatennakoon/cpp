include_directories(includes)

add_library(solution 
    MedianOFTwoSortedArrays.cpp 
    TwoSum.cpp 
    AddTwoNumbers.cpp
    LengthOfLongestSubstring.cpp)

target_include_directories(solution PUBLIC includes)
