#include "solution.h"

// 0005. Longest Palindromic Substring
// https://leetcode.com/problems/longest-palindromic-substring/

string Solution::longestPalindrome(string s) {
    int n = s.size();

    int bestStart = 0;
    int bestLength = 1;

    for (int i = 0; i < n; i++) {
        // Odd-length palindrome: center at i
        int left = i;
        int right = i;

        while (left >= 0 && right < n && s[left] == s[right]) {
            int length = right - left + 1;

            if (length > bestLength) {
                bestStart = left;
                bestLength = length;
            }

            left--;
            right++;
        }

        // Even-length palindrome: center between i and i + 1
        left = i;
        right = i + 1;

        while (left >= 0 && right < n && s[left] == s[right]) {
            int length = right - left + 1;

            if (length > bestLength) {
                bestStart = left;
                bestLength = length;
            }

            left--;
            right++;
        }
    }

    return s.substr(bestStart, bestLength);
}