#include "Solution.h"
#include <gtest/gtest.h>

TEST(TestMedianOfTwoSortedArrays, Test1)
{
    vector<int> nums1{2,7,11,15};
    int target = 9;

    vector<int> expected {0,1};

    Solution s;

    vector<int> actual = s.twoSum(nums1, target);

    EXPECT_EQ(expected, actual);
}

TEST(TestMedianOfTwoSortedArrays, Test2)
{
    vector<int> nums1{3,2,4};
    int target = 6;

    vector<int> expected {1,2};

    Solution s;

    vector<int> actual = s.twoSum(nums1, target);

    EXPECT_EQ(expected, actual);
}

TEST(TestMedianOfTwoSortedArrays, Test3)
{
    vector<int> nums1{3,3};
    int target = 6;

    vector<int> expected {0,1};

    Solution s;

    vector<int> actual = s.twoSum(nums1, target);

    EXPECT_EQ(expected, actual);
}