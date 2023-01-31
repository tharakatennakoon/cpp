#include "Solution.h"
#include <unordered_set>
#include <unordered_map>
#include <list>

int Solution::lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> substring_monitor_map;
    int start_pos = -1;
    int substring_length = 0;

    for (int index = 0; index < s.length(); index++)
    {
        auto c = s[index];

        if (substring_monitor_map.count(c) == 0)
        {
            substring_monitor_map[c]=index;
        }
        else
        {
            int c_pos = substring_monitor_map[c];
            substring_monitor_map[c] = index;

            if (start_pos < c_pos)
                start_pos = c_pos;
        }

        int diff = index - start_pos;
        if (diff > substring_length)
            substring_length = diff;
    }

    return substring_length;
}