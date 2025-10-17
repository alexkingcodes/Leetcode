#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "solution.h"

static std::vector<int> parseLineToVector(const std::string& line) {
    // expects a line like: [2,4,3]
    std::vector<int> out;
    std::string s = line;
    // strip leading/trailing whitespace
    auto l = s.find_first_not_of(" \t\r\n");
    auto r = s.find_last_not_of(" \t\r\n");
    if (l == std::string::npos) return out;
    s = s.substr(l, r - l + 1);

    // must start with '[' and end with ']'
    if (s.size() < 2 || s.front() != '[' || s.back() != ']') return out;

    std::string inner = s.substr(1, s.size() - 2);
    std::stringstream ss(inner);
    std::string tok;
    while (std::getline(ss, tok, ',')) {
        // trim token
        auto tl = tok.find_first_not_of(" \t\r\n");
        auto tr = tok.find_last_not_of(" \t\r\n");
        if (tl == std::string::npos) continue;
        tok = tok.substr(tl, tr - tl + 1);
        if (!tok.empty()) out.push_back(std::stoi(tok));
    }
    return out;
}

static ListNode* buildList(const std::vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

static void freeList(ListNode* head) {
    while (head) {
        ListNode* n = head->next;
        delete head;
        head = n;
    }
}

static void printList(const ListNode* head) {
    std::cout << "[";
    const ListNode* p = head;
    bool first = true;
    while (p) {
        if (!first) std::cout << ",";
        std::cout << p->val;
        first = false;
        p = p->next;
    }
    std::cout << "]";
}


int main(int argc, char** argv) {
    const char* file = (argc > 1) ? argv[1] : "tests.txt";
    std::ifstream in(file);
    if (!in) {
        std::cerr << "Failed to open " << file << "\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        // skip empty/whitespace-only lines
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        lines.push_back(line);
    }

    if (lines.size() % 2 != 0) {
        std::cerr << "tests.txt must contain an even number of lines (pairs of inputs).\n";
        return 1;
    }

    Solution sol;

    for (size_t i = 0; i < lines.size(); i += 2) {
        auto v1 = parseLineToVector(lines[i]);
        auto v2 = parseLineToVector(lines[i + 1]);

        ListNode* l1 = buildList(v1);
        ListNode* l2 = buildList(v2);

        ListNode* sum = sol.addTwoNumbers(l1, l2);

        std::cout << "Input A: " << lines[i]     << "\n";
        std::cout << "Input B: " << lines[i + 1] << "\n";
        std::cout << "Output : ";
        printList(sum);
        std::cout << "\n\n";

        freeList(l1);
        freeList(l2);
        freeList(sum); // safe even if nullptr
    }

    return 0;
}
