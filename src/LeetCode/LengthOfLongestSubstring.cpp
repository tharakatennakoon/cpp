#include "Solution.h"
#include <unordered_set>
#include <unordered_map>
#include <list>

int Solution::lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> substring_monitor_map;
    int start_pos = -1;
    size_t substring_length = 0;

    for (size_t index = 0; index < s.length(); index++)
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

            start_pos = max(start_pos, c_pos);
        }

        substring_length = max(index-start_pos, substring_length);
    }

    return substring_length;
}