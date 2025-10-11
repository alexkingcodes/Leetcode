# 0001. Two Sum

- **Link**: [Two Sum](https://leetcode.com/problems/two-sum/)
- **Difficulty**: Easy
- **Acceptance**: 56.4%
- **Tags**: Array, Hash Table
- **Paid Only?** No

## Description

<details>
<summary><strong>Problem Description (expand)</strong></summary>

<p>Given an array of integers <code>nums</code>&nbsp;and an integer <code>target</code>, return <em>indices of the two numbers such that they add up to <code>target</code></em>.</p>

<p>You may assume that each input would have <strong><em>exactly</em> one solution</strong>, and you may not use the <em>same</em> element twice.</p>

<p>You can return the answer in any order.</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> nums = [2,7,11,15], target = 9
<strong>Output:</strong> [0,1]
<strong>Explanation:</strong> Because nums[0] + nums[1] == 9, we return [0, 1].
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> nums = [3,2,4], target = 6
<strong>Output:</strong> [1,2]
</pre>

<p><strong class="example">Example 3:</strong></p>

<pre>
<strong>Input:</strong> nums = [3,3], target = 6
<strong>Output:</strong> [0,1]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>2 &lt;= nums.length &lt;= 10<sup>4</sup></code></li>
	<li><code>-10<sup>9</sup> &lt;= nums[i] &lt;= 10<sup>9</sup></code></li>
	<li><code>-10<sup>9</sup> &lt;= target &lt;= 10<sup>9</sup></code></li>
	<li><strong>Only one valid answer exists.</strong></li>
</ul>

<p>&nbsp;</p>
<strong>Follow-up:&nbsp;</strong>Can you come up with an algorithm that is less than <code>O(n<sup>2</sup>)</code><font face="monospace">&nbsp;</font>time complexity?

</details>

<!-- Plain-text fallback (quick search) -->

```
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 
Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].


Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]


Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]


 
Constraints:


	2 <= nums.length <= 104
	-109 <= nums[i] <= 109
	-109 <= target <= 109
	Only one valid answer exists.


 
Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
```

## Approach (notes)

- Intuition:
- Data structures:
- Time/Space:

## Similar Questions

- [3Sum](https://leetcode.com/problems/3sum/) — Medium
- [4Sum](https://leetcode.com/problems/4sum/) — Medium
- [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) — Medium
- [Two Sum III - Data structure design](https://leetcode.com/problems/two-sum-iii-data-structure-design/) — Easy
- [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) — Medium
- [Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/) — Easy
- [Two Sum Less Than K](https://leetcode.com/problems/two-sum-less-than-k/) — Easy
- [Max Number of K-Sum Pairs](https://leetcode.com/problems/max-number-of-k-sum-pairs/) — Medium
- [Count Good Meals](https://leetcode.com/problems/count-good-meals/) — Medium
- [Count Number of Pairs With Absolute Difference K](https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/) — Easy
- [Number of Pairs of Strings With Concatenation Equal to Target](https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/) — Medium
- [Find All K-Distant Indices in an Array](https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/) — Easy
- [First Letter to Appear Twice](https://leetcode.com/problems/first-letter-to-appear-twice/) — Easy
- [Number of Excellent Pairs](https://leetcode.com/problems/number-of-excellent-pairs/) — Hard
- [Number of Arithmetic Triplets](https://leetcode.com/problems/number-of-arithmetic-triplets/) — Easy
- [Node With Highest Edge Score](https://leetcode.com/problems/node-with-highest-edge-score/) — Medium
- [Check Distances Between Same Letters](https://leetcode.com/problems/check-distances-between-same-letters/) — Easy
- [Find Subarrays With Equal Sum](https://leetcode.com/problems/find-subarrays-with-equal-sum/) — Easy
- [Largest Positive Integer That Exists With Its Negative](https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/) — Easy
- [Number of Distinct Averages](https://leetcode.com/problems/number-of-distinct-averages/) — Easy
- [Count Pairs Whose Sum is Less than Target](https://leetcode.com/problems/count-pairs-whose-sum-is-less-than-target/) — Easy

## Solutions

<!-- Add your code files in this folder, reference them here -->

```text
two_sum.py
two_sum.cpp
```