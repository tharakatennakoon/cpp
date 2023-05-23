#include "Solution.h"
#include <gtest/gtest.h>

TEST(TestLengthOfLongestSubstring, Test1)
{
    string sIn = "abcabcbb";

    int expected = 3;

    Solution s;

    int actual = s.lengthOfLongestSubstring(sIn);

    EXPECT_EQ(expected, actual);
}

TEST(TestLengthOfLongestSubstring, Test2)
{
    string sIn = "bbbb";

    int expected = 1;

    Solution s;

    int actual = s.lengthOfLongestSubstring(sIn);

    EXPECT_EQ(expected, actual);
}

TEST(TestLengthOfLongestSubstring, Test3)
{
    string sIn = "pwwkew";

    int expected = 3;

    Solution s;

    int actual = s.lengthOfLongestSubstring(sIn);

    EXPECT_EQ(expected, actual);
}

TEST(TestLengthOfLongestSubstring, Test4)
{
    string sIn = "aaabbcbed";

    int expected = 4;

    Solution s;

    int actual = s.lengthOfLongestSubstring(sIn);

    EXPECT_EQ(expected, actual);
}

TEST(TestLengthOfLongestSubstring, Test5)
{
    string sIn = "11";

    int expected = 1;

    Solution s;

    int actual = s.lengthOfLongestSubstring(sIn);

    EXPECT_EQ(expected, actual);
}

TEST(TestLengthOfLongestSubstring, Test6)
{
    string sIn = "abbac";

    int expected = 3;

    Solution s;

    int actual = s.lengthOfLongestSubstring(sIn);

    EXPECT_EQ(expected, actual);
}