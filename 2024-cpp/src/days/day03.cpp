#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <regex>

class Day03 : public AoCDay {

private:
    const std::regex pattern = std::regex(R"((do\(\))|(don't\(\))|mul\((\d+),(\d+)\))");

public:
    Answer part1() override {
        long long result = 0;

        for(auto it = std::sregex_iterator(lines[0].begin(), lines[0].end(), pattern); it != std::sregex_iterator(); ++it) {
            const std::smatch& match = *it;

            if(match[3].matched) {
                int a = std::stoi(match[3].str());
                int b = std::stoi(match[4].str());
                result += static_cast<long long>(a) *b;
            }
        }

        return result;
    }

    Answer part2() override {
        long long result = 0;
        bool active = true;

        for(auto it = std::sregex_iterator(lines[0].begin(), lines[0].end(), pattern); it != std::sregex_iterator(); ++it) {
            const std::smatch& match = *it;

            if(match[1].matched) {
                active = true;
            } else if(match[2].matched) {
                active = false;
            } else if(match[3].matched) {
                int a = std::stoi(match[3].str());
                int b = std::stoi(match[4].str());
                if(active) result += static_cast<long long>(a) * b;
            }
        }
        return result;
    }
};

static DayRegistrar<Day03> registrar(3);
