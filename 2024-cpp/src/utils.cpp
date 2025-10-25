#include "utils.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace utils {
std::vector<std::string> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}
}
