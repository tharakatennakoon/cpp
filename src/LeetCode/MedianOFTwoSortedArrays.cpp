#include "Solution.h"

double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    int num1_pos = 0, num2_pos = 0;
    int num = 0, pre_num = 0;
    int nums1_size = nums1.size();
    int nums2_size = nums2.size();

    int total_size = nums1_size + nums2_size;
    int itr_count = total_size / 2;

    for(int i = 0; i <= itr_count; i++)
    {
        pre_num = num;

        if (num1_pos < nums1_size && num2_pos < nums2_size)
        {
            int n1 = nums1[num1_pos];
            int n2 = nums2[num2_pos];

            if (n1 < n2)
            {
                num = n1;
                num1_pos++;
            }
            else
            {
                num = n2;
                num2_pos++;
            }
        }
        else if (num1_pos < nums1_size)
        {
            num = nums1[num1_pos++];
        }
        else
        {
            num = nums2[num2_pos++];
        }
    }

    if (total_size % 2 != 0 || total_size < 2)
    {
        return num;
    }
    else
    {
        return (double) (num + pre_num) / 2;
    }
}