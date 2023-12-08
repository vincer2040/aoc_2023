#include "aoc.hh"
#include <iostream>
#include <unordered_map>

struct Node {
    std::string left;
    std::string right;
};

static int walk(std::unordered_map<std::string, Node>& graph,
                std::string& cur_location, const std::string& instructions);
static uint64_t walk2(std::unordered_map<std::string, Node>& graph,
                      const std::string& cur_location,
                      const std::string& instructions);
static uint64_t lcm_of_arr(std::vector<uint64_t>& arr);

int day8p1(const std::string& input) {
    std::vector<std::string> split = split_on_string(input, "\n\n");
    std::string instructions = split[0];
    std::vector<std::string> map = split_str(split[1], '\n');
    std::unordered_map<std::string, Node> graph;
    std::string start = "AAA";
    for (auto& row : map) {
        std::vector<std::string> from_tos = split_on_string(row, " = ");
        std::string from = from_tos[0];
        std::vector<std::string> tos = split_on_string(from_tos[1], ", ");
        size_t pos = tos[0].find('(');
        std::string left = tos[0].replace(pos, 1, "");
        pos = tos[1].find(')');
        std::string right = tos[1].replace(pos, 1, "");
        Node n = {left, right};
        graph[from] = n;
    }
    return walk(graph, start, instructions);
}

uint64_t day8p2(const std::string& input) {
    std::vector<std::string> split = split_on_string(input, "\n\n");
    std::string instructions = split[0];
    std::vector<std::string> map = split_str(split[1], '\n');
    std::unordered_map<std::string, Node> graph;
    for (auto& row : map) {
        std::vector<std::string> from_tos = split_on_string(row, " = ");
        std::string from = from_tos[0];
        std::vector<std::string> tos = split_on_string(from_tos[1], ", ");
        size_t pos = tos[0].find('(');
        std::string left = tos[0].replace(pos, 1, "");
        pos = tos[1].find(')');
        std::string right = tos[1].replace(pos, 1, "");
        Node n = {left, right};
        graph[from] = n;
    }

    std::vector<uint64_t> paths;

    for (auto& it : graph) {
        const std::string& key = it.first;
        size_t key_len = key.length();
        if (key[key_len - 1] != 'A') {
            continue;
        }
        uint64_t p = walk2(graph, key, instructions);
        paths.push_back(p);
    }
    return lcm_of_arr(paths);
}

static int walk(std::unordered_map<std::string, Node>& graph,
                std::string& cur_location, const std::string& instructions) {
    int num_steps = 0;
    size_t instruction_idx = 0;
    while (cur_location != "ZZZ") {
        Node& n = graph[cur_location];
        char instruction = instructions[instruction_idx % instructions.size()];
        if (instruction == 'L') {
            cur_location = n.left;
        } else {
            cur_location = n.right;
        }
        num_steps++;
        instruction_idx++;
    }
    return num_steps;
}

static uint64_t walk2(std::unordered_map<std::string, Node>& graph,
                      const std::string& cur_location_s,
                      const std::string& instructions) {
    uint64_t num_steps = 0;
    size_t instruction_idx = 0;
    std::string cur_location = cur_location_s;
    size_t cur_location_len = cur_location.length();
    while (cur_location[cur_location_len - 1] != 'Z') {
        char instruction =
            instructions[instruction_idx % instructions.length()];
        Node& n = graph[cur_location];
        if (instruction == 'L') {
            cur_location = n.left;
            cur_location_len = cur_location.length();
        } else {
            cur_location = n.right;
            cur_location_len = cur_location.length();
        }
        instruction_idx++;
        num_steps++;
    }
    return num_steps;
}

static uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

static uint64_t lcm(uint64_t a, uint64_t b) { return (a * b) / gcd(a, b); }

static uint64_t lcm_of_arr(std::vector<uint64_t>& arr) {
    uint64_t result = arr[0];
    size_t i, len = arr.size();
    for (i = 1; i < len; ++i) {
        result = lcm(result, arr[i]);
    }
    return result;
}
