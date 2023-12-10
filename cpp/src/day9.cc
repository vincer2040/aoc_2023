#include "aoc.hh"
#include <string>
#include <unordered_set>

static std::vector<int> parse_nums(const std::string& line);
static std::vector<std::vector<int>> get_difs(const std::vector<int>& nums);

int day9p1(const std::string& input) {
    int res = 0;
    std::vector<std::string> split = split_str(input, '\n');
    for (auto& line : split) {
        std::vector<int> nums = parse_nums(line);
        std::vector<std::vector<int>> difs = get_difs(nums);
        int num_to_add = 0;
        int num_add_to = nums.back();
        ssize_t i = difs.size() - 1;
        for (; i != -1; i--) {
            std::vector<int> cur = difs[i];
            int c = cur.back();
            num_to_add += c;
        }
        res += num_to_add + num_add_to;
    }
    return res;
}

int day9p2(const std::string& input) {
    int res = 0;
    std::vector<std::string> split = split_str(input, '\n');
    for (auto& line : split) {
        std::vector<int> nums = parse_nums(line);
        std::vector<std::vector<int>> difs = get_difs(nums);
        int num_to_subtract = 0;
        int num_to_subtract_from = nums.front();
        ssize_t i = difs.size() - 1;
        for (; i != -1; i--) {
            std::vector<int> cur = difs[i];
            int c = cur.front();
            num_to_subtract = c - num_to_subtract;
        }
        res += (num_to_subtract_from - num_to_subtract);
    }
    return res;
}

static std::vector<int> parse_nums(const std::string& line) {
    std::vector<int> res;
    std::vector<std::string> nums = split_str(line, ' ');
    for (auto& num : nums) {
        res.push_back(std::stoi(num));
    }
    return res;
}

static std::vector<int> get_cur_difs(std::vector<int>& cur_nums) {
    size_t i, len = cur_nums.size();
    std::vector<int> res;
    for (i = 1; i < len; ++i) {
        int cur = cur_nums[i];
        int prev = cur_nums[i - 1];
        int n = cur - prev;
        res.push_back(n);
    }
    return res;
}

static std::vector<std::vector<int>> get_difs(const std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    std::vector<int> cur_nums = nums;
    while (true) {
        std::vector<int> difs = get_cur_difs(cur_nums);
        std::unordered_set<int> s;
        for (auto& it : difs) {
            s.insert(it);
        }

        res.push_back(difs);
        cur_nums = difs;
        if (s.size() == 1) {
            break;
        }
    }
    return res;
}
