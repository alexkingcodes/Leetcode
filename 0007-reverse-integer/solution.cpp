#include "solution.h"

#include <climits>

// 0007. Reverse Integer
// https://leetcode.com/problems/reverse-integer/

int Solution::reverse(int x) {
    int result = 0;

    while (x != 0) {
        int digit = x % 10;
        x /= 10;

        // Check for overflow before:
        // result = result * 10 + digit

        if (result > INT_MAX / 10 ||
            (result == INT_MAX / 10 && digit > 7)) {
            return 0;
        }

        if (result < INT_MIN / 10 ||
            (result == INT_MIN / 10 && digit < -8)) {
            return 0;
        }

        result = result * 10 + digit;
    }

    return result;
}