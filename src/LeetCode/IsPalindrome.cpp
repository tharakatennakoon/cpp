#include "Solution.h"
#include <algorithm>

bool Solution::isPalindrome(string s)
{
    auto it_remove = std::remove_if(s.begin(), s.end(), [](char const &c){
        return !std::isalnum(c);
    });
    s.erase(it_remove, s.end());

    size_t start_pos = 0;
    size_t end_pos = s.length() - 1;
    bool is_palindrome = true;
    for (size_t i = 0; i < s.length()/2; i++, start_pos++, end_pos--)
    {
        if (std::tolower(s[start_pos]) != std::tolower(s[end_pos]))
        {
            is_palindrome = false;
            break;
        }
    }

    return is_palindrome;
}