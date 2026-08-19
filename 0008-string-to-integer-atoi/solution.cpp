#include "solution.h"

#include <climits>

// 0008. String to Integer (atoi)
// https://leetcode.com/problems/string-to-integer-atoi/

int Solution::myAtoi(string s) {
    int i = 0;
    int n = s.size();

    while (i < n && s[i] == ' ') {
        i++;
    }

    bool negative = false;

    if (i < n && (s[i] == '+' || s[i] == '-')) {
        negative = (s[i] == '-');
        i++;
    }

    // Accumulate as a negative number to safely represent INT_MIN.
    int result = 0;

    // Lowest allowed accumulated value.
    int limit = negative ? INT_MIN : -INT_MAX;

    while (i < n && s[i] >= '0' && s[i] <= '9') {
        int digit = s[i] - '0';

        // Check whether result * 10 would go below the limit.
        if (result < limit / 10) {
            return negative ? INT_MIN : INT_MAX;
        }

        result *= 10;

        // Check whether subtracting the digit would go below limit.
        if (result < limit + digit) {
            return negative ? INT_MIN : INT_MAX;
        }

        result -= digit;
        i++;
    }

    return negative ? result : -result;
}