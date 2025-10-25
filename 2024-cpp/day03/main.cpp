#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <regex>

int main (int argc, char *argv[]) {
    std::ifstream myfile("input.txt");
    if(!myfile) {
        std::cerr << "Failed to read file\n";
        return 1;
    }

    const std::string input = {std::istreambuf_iterator<char>(myfile), std::istreambuf_iterator<char>()};

    const std::regex pattern(R"((do\(\))|(don't\(\))|mul\((\d+),(\d+)\))");;

    long long result = 0, result_2 = 0;
    bool active = true;

    for(auto it = std::sregex_iterator(input.begin(), input.end(), pattern); it != std::sregex_iterator(); ++it) {
        const std::smatch& match = *it;
        const std::string_view token = match[0].str();

        if(match[1].matched) {
            active = true;
        } else if(match[2].matched) {
            active = false;
        } else if(match[3].matched) {
            int a = std::stoi(match[3].str());
            int b = std::stoi(match[4].str());
            result += static_cast<long long>(a) *b;
            if(active) result_2 += static_cast<long long>(a) * b;
        }
    }

    std::cout << "Result for part 1: " << result << "\n";
    std::cout << "Result for part 2: " << result_2 << "\n";

    return 0;
}
