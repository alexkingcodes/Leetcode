#include "solution.h"
using std::max;
using std::vector;
// 0003. Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/

int Solution::lengthOfLongestSubstring(string s)
{
    // TODO: implement
    vector<int> last(256, -1);
    int l = 0;
    int maxLen = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (last[s[i]] >= l)
        {
            l = last[s[i]] + 1;
        }
        last[s[i]] = i;
        maxLen = max(maxLen, i - l + 1);
    }

    return maxLen;
}
