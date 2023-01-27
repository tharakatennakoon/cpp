#include "Solution.h"
#include <unordered_map>

vector<int> Solution::twoSum(vector<int>& nums, int target)
{
    std::unordered_map<int,int> mDif;
    vector<int> ret;
    
    int size = nums.size();
    
    for (int i = 0; i < size; i++)
    {
        std::unordered_map<int,int>::iterator it = mDif.find(nums[i]);
        
        if (it == mDif.end())
        {
            mDif[target - nums[i]] = i;
        }
        else
        {
            ret.push_back(it->second);
            ret.push_back(i);
            
            return ret;
        }
    }
    
    return ret;
}