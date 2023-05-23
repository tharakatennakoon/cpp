#include <Solution.h>
#include <gtest/gtest.h>

ListNode* vector_to_list(vector<int> nums)
{
    ListNode* ret = nullptr;
    ListNode* next = nullptr;

    for (int i : nums)
    {
        if (ret != nullptr)
        {
            next->next = new ListNode(i);
            next = next->next;
        }
        else
        {
            ret = new ListNode(i);
            next = ret;
        }
    }

    if (ret == nullptr)
    {
        ret = new ListNode(0);
    }

    return ret;
}

vector<int> list_to_vector(ListNode* l)
{
    vector<int> ret;

    while(l != nullptr)
    {
        ret.push_back(l->val);
        l = l->next;
    }

    return ret;
}

void delete_list(ListNode *l)
{
    while(l != nullptr)
    {
        ListNode* ln = l;
        l = l->next;

        delete(ln); 
    }
}

TEST(TestAddTwoNumbers, Test1)
{
    vector<int> nums1{2,4,3};
    vector<int> nums2{5,6,4};
    vector<int> expected{7,0,8};

    ListNode* l1 = vector_to_list(nums1);
    ListNode* l2 = vector_to_list(nums2);

    Solution s;

    ListNode* lActual = s.addTwoNumbers(l1,l2);

    vector<int> actual = list_to_vector(lActual);

    EXPECT_EQ(expected, actual);

    delete_list(l1);
    delete_list(l2);
    delete_list(lActual);
}

TEST(TestAddTwoNumbers, Test2)
{
    vector<int> nums1{};
    vector<int> nums2{};
    vector<int> expected{0};

    ListNode* l1 = vector_to_list(nums1);
    ListNode* l2 = vector_to_list(nums2);

    Solution s;

    ListNode* lActual = s.addTwoNumbers(l1,l2);

    vector<int> actual = list_to_vector(lActual);

    EXPECT_EQ(expected, actual);

    delete_list(l1);
    delete_list(l2);
    delete_list(lActual);
}

TEST(TestAddTwoNumbers, Test3)
{
    vector<int> nums1    {9,9,9,9,9,9,9,9};
    vector<int> nums2    {9,9,9,9};
    vector<int> expected {8,9,9,9,0,0,0,0,1};

    ListNode* l1 = vector_to_list(nums1);
    ListNode* l2 = vector_to_list(nums2);

    Solution s;

    ListNode* lActual = s.addTwoNumbers(l1,l2);

    vector<int> actual = list_to_vector(lActual);

    EXPECT_EQ(expected, actual);

    delete_list(l1);
    delete_list(l2);
    delete_list(lActual);
}

