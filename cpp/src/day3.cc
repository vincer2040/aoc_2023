#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

static std::vector<std::vector<char>> make_matrix(const std::string& input);
static bool is_special(char ch);
static bool is_gear(char ch);

struct dir {
    int dy;
    int dx;
};

struct pos {
    size_t y;
    size_t x;
    pos() : y(0), x(0) {}
    pos(size_t y, size_t x) : y(y), x(x) {}
    bool operator==(const pos& check) const {
        return y == check.y && x == check.x;
    }
};

struct pos_hash {
    size_t operator()(const pos& p) const {
        return std::hash<size_t>()(p.y) ^ std::hash<size_t>()(p.x);
    }
};

struct num {
    int val;
    std::vector<pos> positions;
};

dir dirs[] = {
    {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1},
};

size_t dirs_len = sizeof dirs / sizeof dirs[0];

int day3p1(const std::string& input) {
    int res = 0;
    std::vector<std::vector<char>> matrix = make_matrix(input);
    size_t i, num_rows = matrix.size();
    std::vector<num> nums;
    std::vector<pos> special;
    for (i = 0; i < num_rows; ++i) {
        auto& row = matrix[i];
        size_t j = 0, row_len = row.size();
        while (j < row_len) {
            char ch = row[j];
            if (isdigit(ch)) {
                int num_val = 0;
                std::vector<pos> positions;
                while (j < row_len && isdigit(row[j])) {
                    pos p = {i, j};
                    num_val = (num_val * 10) + (row[j] - '0');
                    positions.push_back(p);
                    j++;
                }
                num n = {num_val, positions};
                nums.push_back(n);
                continue;
            }
            if (is_special(ch)) {
                pos p = {i, j};
                special.push_back(p);
            }
            j++;
        }
    }

    for (auto& num : nums) {
        std::vector<pos> positions = num.positions;
        for (auto& p : positions) {
            size_t i;
            for (i = 0; i < dirs_len; ++i) {
                dir d = dirs[i];
                pos check = pos();
                check.y = p.y + d.dy;
                check.x = p.x + d.dx;
                if (std::find(special.begin(), special.end(), check) !=
                    special.end()) {
                    res += num.val;
                    goto next_num;
                }
            }
        }
    next_num:
        continue;
    }
    return res;
}

int day3p2(const std::string& input) {
    int res = 0;
    std::vector<std::vector<char>> matrix = make_matrix(input);
    size_t i, num_rows = matrix.size();
    std::vector<num> nums;
    std::vector<pos> gears;
    std::unordered_map<pos, std::vector<int>, pos_hash> map;
    for (i = 0; i < num_rows; ++i) {
        auto& row = matrix[i];
        size_t j = 0, row_len = row.size();
        while (j < row_len) {
            char ch = row[j];
            if (isdigit(ch)) {
                int num_val = 0;
                std::vector<pos> positions;
                while (j < row_len && isdigit(row[j])) {
                    pos p = {i, j};
                    num_val = (num_val * 10) + (row[j] - '0');
                    positions.push_back(p);
                    j++;
                }
                num n = {num_val, positions};
                nums.push_back(n);
                continue;
            }
            if (is_gear(ch)) {
                pos p = {i, j};
                gears.push_back(p);
            }
            j++;
        }
    }

    for (auto& num : nums) {
        std::vector<pos> positions = num.positions;
        for (auto& p : positions) {
            size_t i;
            for (i = 0; i < dirs_len; ++i) {
                dir d = dirs[i];
                pos check = pos();
                check.y = p.y + d.dy;
                check.x = p.x + d.dx;
                if (std::find(gears.begin(), gears.end(), check) !=
                    gears.end()) {
                    if (map.count(check) > 0) {
                        map[check].push_back(num.val);
                    } else {
                        std::vector<int> new_val;
                        new_val.push_back(num.val);
                        map[check] = new_val;
                    }
                    goto next_num;
                }
            }
        }
    next_num:
        continue;
    }

    for (const auto& pair : map) {
        std::vector<int> vals = pair.second;
        if (vals.size() == 2) {
            int a1 = vals[0];
            int a2 = vals[1];
            res += (a1 * a2);
        }
    }
    return res;
}

static std::vector<std::vector<char>> make_matrix(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::vector<char>> res;
    std::string line;
    while (std::getline(iss, line, '\n')) {
        std::vector<char> row;
        for (auto ch : line) {
            row.push_back(ch);
        }
        res.push_back(row);
    }
    return res;
}

static bool is_special(char ch) { return !isdigit(ch) && ch != '.'; }

static bool is_gear(char ch) { return ch == '*'; }
