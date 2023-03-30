#include "Solution.h"
#include <algorithm>

vector<vector<int>> Solution::threeSum(vector<int>& nums)
{
    vector<vector<int>> result;

    std::sort(nums.begin(), nums.end());

    // if all negative || positive || count less than 3
    if (nums[0] > 0 || nums[nums.size() - 1] < 0 || nums.size() < 3)
        return result;

    // int negative_start_pos = 0;
    // int positive_start_pos = 0;
    // int zero_start_pos = -1;

    // for (int i = 0; i < nums.size(); i++)
    // {
    //     if (nums[i] == 0)
    //     {
    //         zero_start_pos = i;
    //         break;
    //     }
    // }

    // for (int i = max(zero_start_pos,0); i < nums.size(); i++)
    // {
    //     if (nums[i] > 0)
    //     {
    //         positive_start_pos = i;
    //         break;
    //     }
    // }

    // for (int i = 0; i < positive_start_pos;)
    // {
    //     int num1 = nums[i];

    //     for (int j = i + 1; j < positive_start_pos;)
    //     {
    //         int num2 = nums[j];
    //         int sum = num1 + num2;

    //         int startpos = zero_start_pos < 0 ? positive_start_pos : zero_start_pos;
    //         for (int k = max(j, startpos); k < nums.size(); k++)
    //         {
    //             int num3 = nums[k];
    //             if (sum + num3 == 0)
    //             {
    //                 result.push_back(std::vector{num1, num2, num3});
    //                 break;
    //             }
    //         }

    //         for (int k = j + 1; j < positive_start_pos; k++)
    //         {
    //             if (num2 != nums[k])
    //             {
    //                 j = k;
    //                 break;
    //             }
    //         }
    //     }

    //     for (int j = i + 1; i < positive_start_pos; j++)
    //     {
    //         if (num1 != nums[j])
    //         {
    //             i = j;
    //             break;
    //         }
    //     }
    // }

    // if (zero_start_pos != -1 && positive_start_pos == 0)
    // {
    //     if (nums.size() - zero_start_pos > 2)
    //     {
    //         result.push_back(std::vector{0, 0, 0});
    //     }
    // }

    int zero_start_pos = 0;
    while(nums[zero_start_pos++] < 0);

    int positive_start_pos = zero_start_pos;
    while(nums[positive_start_pos++] > 0);

    int first_num_pos = 0;
    int third_num_pos = nums.size() - 1;
    bool end_search = false;

    while (first_num_pos < positive_start_pos || !end_search)
    {
        int num1 = nums[first_num_pos];

        int second_num_pos = first_num_pos + 1;
        while (second_num_pos < nums.size() - 1 || !end_search)
        {
            int num2 = nums[second_num_pos];
            int sum = num1 + num2;

            while (third_num_pos > second_num_pos)
            {
                int num3 = nums[third_num_pos--];
                sum += num3;

                if (sum < 0)
                {
                    end_search = true;
                    break;
                }
                else if (sum)
                {

                }
            }
        }
    }


    return result;
}