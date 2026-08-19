#include "solution.h"

#include <vector>

// 0010. Regular Expression Matching
// https://leetcode.com/problems/regular-expression-matching/

bool Solution::isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    // Empty string matches empty pattern.
    dp[0][0] = true;

    // Patterns like a*, a*b*, a*b*c* can match an empty string.
    for (int j = 2; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            // Normal character or '.'
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }

            // '*'
            else if (p[j - 1] == '*') {
                // Option 1: use zero occurrences of preceding character.
                dp[i][j] = dp[i][j - 2];

                // Option 2: use one or more occurrences.
                char previous = p[j - 2];

                if (previous == '.' || previous == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];
}