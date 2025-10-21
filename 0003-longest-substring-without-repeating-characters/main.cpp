#include "solution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// --- Small helpers -----------------------------------------------------------

// Trim trailing CR from Windows files
static inline void rstrip_cr(std::string &s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
}

// Unescape a subset of C-style escapes used in tests: \" \\ \n \t \r
static std::string unescape(const std::string &s)
{
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (c == '\\' && i + 1 < s.size())
        {
            char n = s[++i];
            switch (n)
            {
            case 'n':
                out.push_back('\n');
                break;
            case 't':
                out.push_back('\t');
                break;
            case 'r':
                out.push_back('\r');
                break;
            case '\\':
                out.push_back('\\');
                break;
            case '"':
                out.push_back('"');
                break;
            default:
                out.push_back('\\');
                out.push_back(n);
                break; // keep unknown escapes
            }
        }
        else
        {
            out.push_back(c);
        }
    }
    return out;
}

// If a line is quoted like "abc", return the inside (with escapes decoded).
// Otherwise return the line as-is (after trimming CR).
static bool parse_test_line(const std::string &line_raw, std::string &out)
{
    std::string line = line_raw;
    rstrip_cr(line);
    // skip blanks and comments
    size_t i = 0;
    while (i < line.size() && isspace(static_cast<unsigned char>(line[i])))
        ++i;
    if (i == line.size() || line[i] == '#')
        return false;

    if (line[i] == '"')
    {
        // find matching ending quote
        size_t j = line.find_last_of('"');
        if (j == std::string::npos || j == i)
        {
            // malformed; treat without quotes
            out = line.substr(i);
            return true;
        }
        std::string inside = line.substr(i + 1, j - i - 1);
        out = unescape(inside);
        return true;
    }

    // not quoted; take the rest of the line
    out = line.substr(i);
    return true;
}

// For pretty printing the input back out (escape control chars and quotes)
static std::string escape_for_print(const std::string &s)
{
    std::string out;
    out.reserve(s.size() + 2);
    out.push_back('"');
    for (char c : s)
    {
        switch (c)
        {
        case '\n':
            out += "\\n";
            break;
        case '\t':
            out += "\\t";
            break;
        case '\r':
            out += "\\r";
            break;
        case '\\':
            out += "\\\\";
            break;
        case '"':
            out += "\\\"";
            break;
        default:
            out.push_back(c);
            break;
        }
    }
    out.push_back('"');
    return out;
}

// --- Main --------------------------------------------------------------------

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Determine source of tests: CLI path -> tests.txt -> stdin
    std::vector<std::string> tests;
    std::string path = (argc >= 2 ? std::string(argv[1]) : "tests.txt");

    auto load_from_stream = [&](std::istream &in)
    {
        std::string line;
        while (std::getline(in, line))
        {
            std::string parsed;
            if (parse_test_line(line, parsed))
            {
                // skip lines that became empty after parsing
                if (!parsed.empty())
                    tests.push_back(parsed);
            }
        }
    };

    bool loaded = false;
    {
        std::ifstream fin(path);
        if (fin.good())
        {
            load_from_stream(fin);
            loaded = true;
        }
    }
    if (!loaded && argc < 2)
    {
        // fallback to stdin if no tests.txt file
        load_from_stream(std::cin);
    }

    if (tests.empty())
    {
        std::cerr << "No tests found. Provide a file (default: tests.txt) with one quoted string per line,\n"
                  << "or pipe lines into stdin.\n";
        return 1;
    }

    Solution sol;
    for (size_t i = 0; i < tests.size(); ++i)
    {
        const std::string &s = tests[i];
        int ans = sol.lengthOfLongestSubstring(s);
        std::cout << "Case " << (i + 1) << ": s = " << escape_for_print(s)
                  << " -> " << ans << '\n';
    }
    return 0;
}
