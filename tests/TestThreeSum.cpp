#include "Solution.h"
#include <gtest/gtest.h>

// TEST(TestThreeSum, Test1)
// {
//     vector<int> nums{-1,-1,-4};
//     vector<vector<int>> expected{};
    
//     Solution solution;

//     vector<vector<int>> actual = solution.threeSum(nums);

//     EXPECT_EQ(expected, actual);
// }

// TEST(TestThreeSum, Test2)
// {
//     vector<int> nums{1, 1, 4};
//     vector<vector<int>> expected{};
    
//     Solution solution;

//     vector<vector<int>> actual = solution.threeSum(nums);

//     EXPECT_EQ(expected, actual);
// }

// TEST(TestThreeSum, Test3)
// {
//     vector<int> nums{-1,0,1,2,-1,-4};
//     vector<vector<int>> expected{
//         {-1,-1, 2}, 
//         {-1, 0, 1}};
    
//     Solution solution;

//     vector<vector<int>> actual = solution.threeSum(nums);

//     EXPECT_EQ(expected, actual);
// }

// TEST(TestThreeSum, Test4)
// {
//     vector<int> nums{-1,0,0,0,1,2,-1,-4};
//     vector<vector<int>> expected{
//         {-1,-1, 2}, 
//         {-1, 0, 1},
//         { 0, 0, 0}};
    
//     Solution solution;

//     vector<vector<int>> actual = solution.threeSum(nums);

//     EXPECT_EQ(expected, actual);
// }

// TEST(TestThreeSum, Test5)
// {
//     vector<int> nums{0,0,0};
//     vector<vector<int>> expected{
//         { 0, 0, 0}};
    
//     Solution solution;

//     vector<vector<int>> actual = solution.threeSum(nums);

//     EXPECT_EQ(expected, actual);
// }

TEST(TestThreeSum, Test6)
{
    vector<int> nums{1,1,-2};
    vector<vector<int>> expected{
        { -2, 1, 1}};
    
    Solution solution;

    vector<vector<int>> actual = solution.threeSum(nums);

    EXPECT_EQ(expected, actual);
}