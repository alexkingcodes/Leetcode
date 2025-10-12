#include "solution.h"

#include <chrono>
#include <cstddef>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX 1
#endif
#include <windows.h>
#include <psapi.h>
#elif defined(__APPLE__)
#include <mach/mach.h>
#elif defined(__linux__)
#include <unistd.h>
#include <cstdio>
#endif
struct TestCase {
    std::vector<int> nums;
    int target{};
};

using SolverFunction = std::function<std::vector<int>(std::vector<int>, int)>;

struct SolverEntry {
    std::string name;
    SolverFunction function;
    std::string timeComplexity;
};

std::string trim(const std::string& input) {
    const std::string::size_type first = input.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
    }
    const std::string::size_type last = input.find_last_not_of(" \t\r\n");
    return input.substr(first, last - first + 1);
}

std::vector<int> parseIntegerList(const std::string& line) {
    std::string cleaned;
    cleaned.reserve(line.size());
    for (char ch : line) {
        if (ch != '[' && ch != ']') {
            cleaned.push_back(ch);
        }
    }

    std::vector<int> values;
    std::stringstream stream(cleaned);
    std::string token;
    while (std::getline(stream, token, ',')) {
        token = trim(token);
        if (!token.empty()) {
            values.push_back(std::stoi(token));
        }
    }
    return values;
}

int parseTargetValue(const std::string& line) {
    const std::string trimmed = trim(line);
    if (trimmed.empty()) {
        throw std::runtime_error("Encountered empty target line in tests.txt.");
    }
    return std::stoi(trimmed);
}

std::vector<TestCase> loadTestCasesFromFile(const std::string& path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open test file: " + path);
    }

    std::vector<TestCase> tests;
    std::string line;
    while (std::getline(input, line)) {
        line = trim(line);
        if (line.empty()) {
            continue;
        }

        if (line.front() != '[') {
            throw std::runtime_error("Expected an array line starting with '[' but found: " + line);
        }

        TestCase testCase;
        testCase.nums = parseIntegerList(line);

        std::string targetLine;
        while (std::getline(input, targetLine)) {
            targetLine = trim(targetLine);
            if (!targetLine.empty()) {
                break;
            }
        }

        if (targetLine.empty()) {
            throw std::runtime_error("Missing target line after array in test file.");
        }
        if (!targetLine.empty() && targetLine.front() == '[') {
            throw std::runtime_error("Detected a second array where a target was expected. Please verify tests.txt formatting.");
        }
        testCase.target = parseTargetValue(targetLine);
        tests.push_back(std::move(testCase));
    }

    return tests;
}

bool isValidTwoSumResult(const TestCase& test, const std::vector<int>& indices) {
    if (indices.size() != 2) {
        return false;
    }

    const int first = indices[0];
    const int second = indices[1];
    if (first < 0 || second < 0) {
        return false;
    }

    const std::size_t size = test.nums.size();
    if (static_cast<std::size_t>(first) >= size || static_cast<std::size_t>(second) >= size) {
        return false;
    }

    if (first == second) {
        return false;
    }

    const int sum = test.nums[static_cast<std::size_t>(first)] +
                   test.nums[static_cast<std::size_t>(second)];
    return sum == test.target;
}

void runSolverOnTests(const SolverEntry& solver,
                      const std::vector<TestCase>& tests) {
    if (tests.empty()) {
        std::cout << "No predefined tests to execute for solver '" << solver.name << "'.\n";
        return;
    }

    std::size_t passed = 0;
    std::size_t failed = 0;

    for (std::size_t index = 0; index < tests.size(); ++index) {
        const TestCase& test = tests[index];
        try {
            std::vector<int> numsCopy = test.nums;
            const std::vector<int> result = solver.function(std::move(numsCopy), test.target);
            if (isValidTwoSumResult(test, result)) {
                ++passed;
            } else {
                ++failed;
                std::cerr << "Solver '" << solver.name << "' failed validation on test #"
                          << index + 1 << ".\n";
            }
        } catch (const std::exception& ex) {
            ++failed;
            std::cerr << "Solver '" << solver.name << "' threw an exception on test #"
                      << index + 1 << ": " << ex.what() << '\n';
        } catch (...) {
            ++failed;
            std::cerr << "Solver '" << solver.name << "' encountered an unknown error on test #"
                      << index + 1 << ".\n";
        }
    }

    std::cout << "Solver '" << solver.name << "' summary: " << passed << " passed, "
              << failed << " failed out of " << tests.size() << " tests.\n";
}

std::size_t getCurrentResidentSetSize() {
#if defined(_WIN32)
    PROCESS_MEMORY_COUNTERS counters{};
    if (GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters)) != 0) {
        return static_cast<std::size_t>(counters.WorkingSetSize);
    }
    return 0;
#elif defined(__APPLE__)
    task_basic_info info{};
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), TASK_BASIC_INFO,
                  reinterpret_cast<task_info_t>(&info), &infoCount) == KERN_SUCCESS) {
        return static_cast<std::size_t>(info.resident_size);
    }
    return 0;
#elif defined(__linux__)
    FILE* file = std::fopen("/proc/self/statm", "r");
    if (file == nullptr) {
        return 0;
    }

    long rssPages = 0;
    if (std::fscanf(file, "%*s%ld", &rssPages) != 1) {
        std::fclose(file);
        return 0;
    }
    std::fclose(file);
    const long pageSize = sysconf(_SC_PAGESIZE);
    if (pageSize <= 0) {
        return 0;
    }
    return static_cast<std::size_t>(rssPages) * static_cast<std::size_t>(pageSize);
#else
    return 0;
#endif
}

void benchmarkExecutionTime(const SolverEntry& solver,
                            const std::vector<TestCase>& tests,
                            std::size_t iterations) {
    if (tests.empty() || iterations == 0) {
        std::cout << "Skipping time benchmark for solver '" << solver.name
                  << "' (no tests or iterations specified).\n";
        return;
    }

    const auto start = std::chrono::steady_clock::now();
    try {
        for (std::size_t iteration = 0; iteration < iterations; ++iteration) {
            for (const auto& test : tests) {
                std::vector<int> numsCopy = test.nums;
                volatile std::vector<int> result =
                    solver.function(std::move(numsCopy), test.target);
                (void)result;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Time benchmark for solver '" << solver.name
                  << "' aborted due to exception: " << ex.what() << '\n';
        return;
    } catch (...) {
        std::cerr << "Time benchmark for solver '" << solver.name
                  << "' aborted due to an unknown error.\n";
        return;
    }
    const auto stop = std::chrono::steady_clock::now();

    const auto totalDuration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    const std::size_t totalRuns = iterations * tests.size();
    const double averagePerRun =
        static_cast<double>(totalDuration) / static_cast<double>(totalRuns);

    std::cout << "Time benchmark for '" << solver.name << "': " << totalDuration
              << " microseconds total (~" << std::fixed << std::setprecision(2)
              << averagePerRun << " microseconds per run).\n";
}

void benchmarkMemoryUsage(const SolverEntry& solver,
                          const std::vector<TestCase>& tests,
                          std::size_t iterations) {
    if (tests.empty() || iterations == 0) {
        std::cout << "Skipping memory benchmark for solver '" << solver.name
                  << "' (no tests or iterations specified).\n";
        return;
    }

    const std::size_t before = getCurrentResidentSetSize();
    try {
        for (std::size_t iteration = 0; iteration < iterations; ++iteration) {
            for (const auto& test : tests) {
                std::vector<int> numsCopy = test.nums;
                volatile std::vector<int> result =
                    solver.function(std::move(numsCopy), test.target);
                (void)result;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Memory benchmark for solver '" << solver.name
                  << "' aborted due to exception: " << ex.what() << '\n';
        return;
    } catch (...) {
        std::cerr << "Memory benchmark for solver '" << solver.name
                  << "' aborted due to an unknown error.\n";
        return;
    }
    const std::size_t after = getCurrentResidentSetSize();

    if (before == 0 || after == 0) {
        std::cout << "Memory benchmark for '" << solver.name
                  << "': unable to determine RSS on this platform.\n";
        return;
    }

    const std::size_t difference = (after > before) ? (after - before) : 0;
    const double differenceKB = static_cast<double>(difference) / 1024.0;
    std::cout << "Memory benchmark for '" << solver.name << "': +" << differenceKB
              << " KiB after " << iterations * tests.size() << " executions.\n";
}

void printTimeComplexitySummary(const std::vector<SolverEntry>& solvers) {
    if (solvers.empty()) {
        std::cout << "\nNo solvers provided; skipping Big O summary.\n";
        return;
    }

    std::cout << "\nAsymptotic time complexity summary (Big O):\n";
    for (const SolverEntry& solver : solvers) {
        std::cout << " - " << solver.name << ": " << solver.timeComplexity << '\n';
    }
}

std::vector<TestCase> generateRandomizedTests(std::size_t testCount,
                                              std::size_t minSize,
                                              std::size_t maxSize,
                                              int minValue,
                                              int maxValue,
                                              unsigned int seed = std::random_device{}()) {
    if (minSize < 2) {
        throw std::invalid_argument("Minimum array size for generated tests must be at least 2.");
    }
    if (minSize > maxSize) {
        throw std::invalid_argument("Minimum array size cannot exceed maximum array size.");
    }
    if (minValue > maxValue) {
        throw std::invalid_argument("Minimum value cannot exceed maximum value.");
    }

    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::size_t> sizeDistribution(minSize, maxSize);
    std::uniform_int_distribution<int> valueDistribution(minValue, maxValue);

    std::vector<TestCase> tests;
    tests.reserve(testCount);

    for (std::size_t i = 0; i < testCount; ++i) {
        std::size_t currentSize = sizeDistribution(rng);
        if (currentSize < 2) {
            currentSize = 2;
        }

        TestCase test;
        test.nums.resize(currentSize);
        for (int& value : test.nums) {
            value = valueDistribution(rng);
        }

        std::uniform_int_distribution<std::size_t> indexDistribution(0, currentSize - 1);
        std::size_t firstIndex = indexDistribution(rng);
        std::size_t secondIndex = indexDistribution(rng);
        while (secondIndex == firstIndex) {
            secondIndex = indexDistribution(rng);
        }

        test.target = test.nums[firstIndex] + test.nums[secondIndex];
        tests.push_back(std::move(test));
    }

    return tests;
}

int main() {
    try {
        const std::vector<TestCase> predefinedTests = loadTestCasesFromFile("tests.txt");
        const std::vector<TestCase> randomizedTests =
            generateRandomizedTests(/*testCount=*/10, /*minSize=*/2, /*maxSize=*/100,
                                    /*minValue=*/-1000, /*maxValue=*/1000);

        Solution solution;
        const std::vector<SolverEntry> solvers = {
            {"Solution::twoSum",
             [&solution](std::vector<int> nums, int target) {
                 return solution.twoSum(nums, target);
             },
             "O(n)"}
        };

        for (const SolverEntry& solver : solvers) {
            runSolverOnTests(solver, predefinedTests);
        }

        std::cout << "\nRunning randomized test suite...\n";
        for (const SolverEntry& solver : solvers) {
            runSolverOnTests(solver, randomizedTests);
        }

        constexpr std::size_t benchmarkIterations = 100;
        std::cout << "\nBenchmarking time complexity proxies...\n";
        for (const SolverEntry& solver : solvers) {
            benchmarkExecutionTime(solver, randomizedTests, benchmarkIterations);
        }

        std::cout << "\nBenchmarking memory usage proxies...\n";
        for (const SolverEntry& solver : solvers) {
            benchmarkMemoryUsage(solver, randomizedTests, benchmarkIterations);
        }

        printTimeComplexitySummary(solvers);

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Fatal error: unknown exception occurred.\n";
    }
    return 1;
}
