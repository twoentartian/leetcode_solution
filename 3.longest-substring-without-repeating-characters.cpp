/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// @lc code=start
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int alphabets[128];
        for (int i = 32; i < 128; i++)
        {
            alphabets[i] = 0;
        }
        int length = 0;
        int rem = 1;
        int maxLength = 0;
        int i = 1;
        int ascii = 0;
        int temp = 0;
        for (char &x : s)
        {
            ascii = int(x);
            if (alphabets[ascii] > 0)
            {
                length = i - rem;
                maxLength = length > maxLength ? length : maxLength;
                temp = alphabets[ascii] + 1;
                rem = temp > rem ? temp : rem;
            }
            alphabets[ascii] = i;
            i++;
        }
        if ((i - rem) > maxLength)
        {
            maxLength = (i - rem);
        }
        return maxLength;
    }
};

// @lc code=end

int main()
{
    Solution s;
    std::cout << s.lengthOfLongestSubstring("aab") << std::endl;
}