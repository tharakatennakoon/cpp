#include "Solution.h"
#include <algorithm>
#include <iostream>

vector<vector<int>> Solution::threeSum1(vector<int>& nums)
{
    vector<vector<int>> result;

    std::sort(nums.begin(), nums.end());

    // if all negative || positive || count less than 3
    if (nums[0] > 0 || nums[nums.size() - 1] < 0 || nums.size() < 3)
        return result;
    
    // goto >= 0 index
    int positiveIndex = 0;
    while (nums[positiveIndex] < 0)
    {
        positiveIndex++;
    }

    int i = 0;
    bool movedToPositive = false;
    while (!movedToPositive)
    {
        int num1 = nums[i];

        int j = i + 1;
        while (j < nums.size() - 1)
        {
            int num2 = nums[j];

            if(num1 + num2 > 0)
            {
                break;
            }

            int k = std::max(j + 1, positiveIndex);
            int pos = nums.size() - 1;
            while (pos >= k)
            {
                int num3 = nums[pos];

                if (num3 + num2 + num1 == 0)
                {
                    result.push_back(std::vector{num1, num2, num3});
                    break;
                }
                pos--;
            }

            j++;
            for (;j < nums.size(); j++)
            {
                if (num2 != nums[j])
                {
                    break;
                }
            }
        }

        i++;
        for (;i < nums.size()-1; i++)
        {
            if (num1 != nums[i])
            {
                break;
            }
        }

        if (i >= nums.size() - 2 || nums[i] > 0)
        {
            movedToPositive = true;
        }
    }

    std::cout << " result size " << result.size() << std::endl;

    return result;
}

vector<vector<int>> Solution::threeSum2(vector<int>& nums)
{
    vector<vector<int>> result;

    std::sort(nums.begin(), nums.end());

    // if all negative || positive || count less than 3
    if (nums[0] > 0 || nums[nums.size() - 1] < 0 || nums.size() < 3)
        return result;
    
    // goto >= 0 index
    int positiveIndex = 0;
    while (nums[positiveIndex] < 0)
    {
        positiveIndex++;
    }

    int n1Pos = 0;
    int n3Pos = nums.size() - 1;
    int adjustN1Pos = true;
    while (n1Pos < positiveIndex && n3Pos > positiveIndex)
    {
        int n1 = nums[n1Pos];
        int n3 = nums[n3Pos];
        int tot = n1 + n3;

        int n2Pos = positiveIndex;
        if (tot > 0)
        {
            n2Pos--;

            while (n2Pos > n1Pos)
            {
                if (nums[n2Pos] + tot == 0)
                {
                    result.push_back(std::vector{n1, nums[n2Pos], n3});
                    break;
                }
                else if (nums[n2Pos] + tot < 0)
                {
                    adjustN1Pos = true;
                    break;
                }

                n2Pos--;
            }
        }
        else
        {
            while (n2Pos < n3Pos)
            {
                if (nums[n2Pos] + tot == 0)
                {
                    result.push_back(std::vector{n1, nums[n2Pos], n3});
                    break;
                }
                else if (nums[n2Pos] + tot > 0)
                {
                    adjustN1Pos = false;
                    break;
                }

                n2Pos++;
            }
        }

        while (n1 == nums[n1Pos + 1]) {n1Pos++;}
        while (n3 == nums[n3Pos - 1]) {n3Pos--;}

        if (n1Pos < positiveIndex - 1 && adjustN1Pos)
        {
            n1Pos++;
        }
        else if (n3Pos > positiveIndex + 1 && !adjustN1Pos)
        {
            n3Pos--;
        }
        else
        {
            break;
        }

        if (n1Pos > positiveIndex)
        {
            adjustN1Pos = false;
        }
        else if (n3Pos < positiveIndex)
        {
            adjustN1Pos = true;
        }
        else
        {
            adjustN1Pos = !adjustN1Pos;
        }
    }

    int zeroCount = 0;

    while(nums[positiveIndex] == 0) {zeroCount++; positiveIndex++;}

    if (zeroCount >= 3)
    {
        result.push_back(std::vector{0, 0, 0});
    }
    
    return result;
}