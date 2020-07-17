/*
 * @lc app=leetcode id=4 lang=cpp
 *
 * [4] Median of Two Sorted Arrays
 */

#include <vector>
#include <iostream>
using namespace std;
// @lc code=start
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int size1 = nums1.size(), size2 = nums2.size();
        int all_size = size1 + size2;
        int *output = new int[all_size];

        int median_loc = all_size / 2;
        bool median_two_nums = !(all_size % 2);

        int loc1 = 0, loc2 = 0, output_loc = 0;
        while (!(loc1 == size1 && loc2 == size2))
        {
            bool add = false;
            if (!add && loc1 == size1)
            {
                output[output_loc] = nums2[loc2];
                output_loc++;
                loc2++;
                add = true;
            }
            if (!add && loc2 == size2)
            {
                output[output_loc] = nums1[loc1];
                output_loc++;
                loc1++;
                add = true;
            }
            if (!add && nums1[loc1] <= nums2[loc2])
            {
                output[output_loc] = nums1[loc1];
                output_loc++;
                loc1++;
                add = true;
            }
            else if (!add)
            {
                output[output_loc] = nums2[loc2];
                output_loc++;
                loc2++;
                add = true;
            }
            if (output_loc - 1 == median_loc && !median_two_nums)
            {
                double return_val = output[output_loc - 1];
                delete[] output;
                return return_val;
            }
            if (output_loc - 1 == median_loc && median_two_nums)
            {
                double return_val = (double(output[output_loc - 1]) + output[output_loc-2])/2;
                delete[] output;
                return return_val;
            }
        }

        delete[] output;
        return 0;
    }
};
// @lc code=end

int main()
{
    Solution s;
    std::vector<int> nums1({1, 2}), nums2({3,4});
    std::cout << s.findMedianSortedArrays(nums1, nums2) << std::endl;
}