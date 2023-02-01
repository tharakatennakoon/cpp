#include "Solution.h"
#include <gtest/gtest.h>

TEST(TestIsPalindrome, Test1)
{
    string s = "A man, a plan, a canal: Panama";

    bool expected = true;

    Solution solution;

    bool actual = solution.isPalindrome(s);

    EXPECT_EQ(expected, actual);
}

TEST(TestIsPalindrome, Test2)
{
    string s = "A";

    bool expected = true;

    Solution solution;

    bool actual = solution.isPalindrome(s);

    EXPECT_EQ(expected, actual);
}

TEST(TestIsPalindrome, Test3)
{
    string s = ",";

    bool expected = true;

    Solution solution;

    bool actual = solution.isPalindrome(s);

    EXPECT_EQ(expected, actual);
}

TEST(TestIsPalindrome, Test4)
{
    string s = "";

    bool expected = true;

    Solution solution;

    bool actual = solution.isPalindrome(s);

    EXPECT_EQ(expected, actual);
}