#include "aoc.hh"
#include <cstdlib>
#include <unordered_set>

struct point {
    uint64_t y;
    uint64_t x;
};

static uint64_t solve(const std::string& input, uint64_t num_times);
static std::vector<uint64_t> row_expansions(const std::string& input);
static std::vector<uint64_t> col_expansions(const std::string& input);
static std::vector<point> find_galaxies(const std::string& input);
static uint64_t dist(point& a, point& b);

uint64_t day11p1(const std::string& input) { return solve(input, 1); }

uint64_t day11p2(const std::string& input) { return solve(input, 1000000); }

static uint64_t solve(const std::string& input, uint64_t num_times) {
    uint64_t res = 0;
    std::vector<uint64_t> row_exps = row_expansions(input);
    std::vector<uint64_t> col_exps = col_expansions(input);
    std::vector<point> galaxies = find_galaxies(input);
    size_t i, len = galaxies.size();
    for (i = 0; i < len; ++i) {
        point& p = galaxies[i];
        uint64_t new_y;
        uint64_t new_x;
        uint64_t row_exp = row_exps[p.y];
        uint64_t col_exp = col_exps[p.x];
        if (num_times == 1) {
            new_y = p.y + row_exp;
            new_x = p.x + col_exp;
        } else {
            new_y = p.y + (row_exp * (num_times - 1));
            new_x = p.x + (col_exp * (num_times - 1));
        }

        point new_point = {new_y, new_x};
        galaxies[i] = new_point;
    }

    for (i = 0; i < len; ++i) {
        uint64_t c = 0;
        point p = galaxies[i];
        size_t x;
        for (x = i + 1; x < len; ++x) {
            point pi = galaxies[x];
            uint64_t d = dist(p, pi);
            c += d;
        }
        res += c;
    }
    return res;
}

static std::vector<uint64_t> row_expansions(const std::string& input) {
    std::vector<uint64_t> res;
    std::vector<std::string> lines = split_str(input, '\n');
    uint64_t num_expansions = 0;
    for (auto& line : lines) {
        std::unordered_set<char> set;
        for (auto& c : line) {
            set.insert(c);
        }
        if (set.size() == 1) {
            num_expansions++;
        }
        res.push_back(num_expansions);
    }
    return res;
}

static std::vector<uint64_t> col_expansions(const std::string& input) {
    std::vector<uint64_t> res;
    std::vector<std::string> lines = split_str(input, '\n');
    size_t i, len = lines[0].length();
    uint64_t num_expansions = 0;
    for (i = 0; i < len; ++i) {
        std::unordered_set<char> set;
        for (auto& line : lines) {
            char ch = line[i];
            set.insert(ch);
        }
        if (set.size() == 1) {
            num_expansions++;
        }
        res.push_back(num_expansions);
    }
    return res;
}

static std::vector<point> find_galaxies(const std::string& input) {
    std::vector<point> res;
    std::vector<std::string> lines = split_str(input, '\n');
    size_t i, len = lines.size();
    size_t j, jlen = lines[0].length();
    for (i = 0; i < len; ++i) {
        std::string& line = lines[i];
        for (j = 0; j < jlen; ++j) {
            char ch = line[j];
            if (ch == '#') {
                point p = {i, j};
                res.push_back(p);
            }
        }
    }
    return res;
}

static uint64_t dist(point& a, point& b) {
    uint64_t y = abs((int)(a.y - b.y));
    uint64_t x = abs((int)(a.x - b.x));
    return y + x;
}
