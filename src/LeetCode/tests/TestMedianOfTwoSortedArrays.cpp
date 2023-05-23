#include "Solution.h"
#include <gtest/gtest.h>

TEST(TestMedianOfTwoSortedArrays, Test1)
{
    vector<int> nums1{};
    vector<int> nums2{3};

    double expected = 3;

    Solution s;

    double actual = s.findMedianSortedArrays(nums1, nums2);

    EXPECT_EQ(expected, actual);

    actual = s.findMedianSortedArrays(nums2, nums1);

    EXPECT_EQ(expected, actual);
}

TEST(TestMedianOfTwoSortedArrays, Test2)
{
    vector<int> nums1{2};
    vector<int> nums2{3};

    double expected = 2.5;

    Solution s;

    double actual = s.findMedianSortedArrays(nums1, nums2);

    EXPECT_EQ(expected, actual);

    actual = s.findMedianSortedArrays(nums2, nums1);

    EXPECT_EQ(expected, actual);
}

TEST(TestMedianOfTwoSortedArrays, Test3)
{
    vector<int> nums1{1,3};
    vector<int> nums2{2};

    double expected = 2;

    Solution s;

    double actual = s.findMedianSortedArrays(nums1, nums2);

    EXPECT_EQ(expected, actual);

    actual = s.findMedianSortedArrays(nums2, nums1);

    EXPECT_EQ(expected, actual);
}

TEST(TestMedianOfTwoSortedArrays, Test4)
{
    vector<int> nums1{1,3};
    vector<int> nums2{2,4};

    double expected = 2.5;

    Solution s;

    double actual = s.findMedianSortedArrays(nums1, nums2);

    EXPECT_EQ(expected, actual);

    actual = s.findMedianSortedArrays(nums2, nums1);

    EXPECT_EQ(expected, actual);
}

TEST(TestMedianOfTwoSortedArrays, Test5)
{
    vector<int> nums1{1,1};
    vector<int> nums2{2,4};

    double expected = 1.5;

    Solution s;

    double actual = s.findMedianSortedArrays(nums1, nums2);

    EXPECT_EQ(expected, actual);

    actual = s.findMedianSortedArrays(nums2, nums1);

    EXPECT_EQ(expected, actual);
}