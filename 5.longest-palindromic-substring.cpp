/*
 * @lc app=leetcode id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        std::vector<std::vector<int>> char_pos;
        char_pos.resize(128);
        for (int loc = 0; loc < s.size(); ++loc)
        {
            char_pos[s[loc]].push_back(loc);
        }
        int max_length = 0, start_loc = 0;
        for (auto &&char_value : char_pos)
        {
            for(int loc_index = 0; !char_value.empty() && loc_index < char_value.size() - 1; ++ loc_index)
            {
                int shift = 1;
                int length = char_value[loc_index + 1] - char_value[loc_index];
                while (true)
                {
                    int first_available = char_value[loc_index + shift];
                    if(loc_index + shift + 1 < char_value.size() && char_value[loc_index + shift + 1] == first_available + 1)
                    {
                        shift++;
                    }
                    else
                    {
                        length = length + shift - 1;
                        break;
                    }
                }
                
                if(length > max_length)
                {
                    max_length = length;
                    start_loc = char_value[loc_index];
                }
            }
        }
        return s.substr(start_loc, max_length+1);
    }
};
// @lc code=end

int main()
{
    Solution s;
    std::cout << s.longestPalindrome("aaaa");
}