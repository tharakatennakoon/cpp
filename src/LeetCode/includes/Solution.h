#include <vector>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // https://leetcode.com/problems/median-of-two-sorted-arrays/
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);

    // https://leetcode.com/problems/two-sum/
    vector<int> twoSum(vector<int>& nums, int target);

    // https://leetcode.com/problems/add-two-numbers/
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

    // https://leetcode.com/problems/longest-substring-without-repeating-characters/
    int lengthOfLongestSubstring(string s);
};