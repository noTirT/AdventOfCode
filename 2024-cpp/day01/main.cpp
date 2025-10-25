#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <ranges>
#include <functional>

int main() {
    std::ifstream myfile("input.txt");
    if(!myfile) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::vector<int> left, right;
    std::unordered_map<int, int> freq;

    for(std::string line; std::getline(myfile, line);) {
        std::istringstream iss(line);
        int a,b;

        if(iss >> a >> b) {
            left.push_back(a);
            right.push_back(b);
            ++freq[b];
        }
    }

    std::sort(left.begin(), left.end(), std::greater{});
    std::sort(right.begin(), right.end(), std::greater{});

    int result = 0;
    int result_2 = 0;

    for(size_t i = 0; i< right.size(); ++i) {
        result += std::abs(right[i]-left[i]);
        result_2 += left[i] * freq[left[i]];
    }


    std::cout << "The result is: " << result << '\n';
    std::cout << "The result for 2 is: " << result_2 << std::endl;
    return 0;
}
