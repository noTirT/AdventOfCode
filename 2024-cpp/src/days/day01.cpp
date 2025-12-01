
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <functional>
#include <AoC.hpp>
#include <DayRegistry.hpp>

class Day01 : public AoCDay {
private:
    std::vector<int> left, right;
    std::unordered_map<int, int> freq;

public:
    Answer part1() override {
        for(const auto& line: lines) {
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
        for(size_t i = 0; i< right.size(); ++i) {
            result += std::abs(right[i]-left[i]);
        }
        return result;

    }

    Answer part2() override {
        int result = 0;
        for(size_t i = 0; i<right.size(); ++i)
            result += left[i] * freq[left[i]];
        return result;
    }
};

static DayRegistrar<Day01> registrar(1);
