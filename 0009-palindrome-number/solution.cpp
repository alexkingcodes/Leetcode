#include "solution.h"

// 0009. Palindrome Number
// https://leetcode.com/problems/palindrome-number/

bool Solution::isPalindrome(int x) {
    // Negative numbers are not palindromes.
    // Numbers ending in 0 are not palindromes unless the number is 0.
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int reversedHalf = 0;

    // Only reverse half of the number.
    while (x > reversedHalf) {
        reversedHalf = reversedHalf * 10 + x % 10;
        x /= 10;
    }

    // Even number of digits:
    //   1221 -> x = 12, reversedHalf = 12
    //
    // Odd number of digits:
    //   121 -> x = 1, reversedHalf = 12
    // Ignore the middle digit with / 10.
    return x == reversedHalf || x == reversedHalf / 10;
}