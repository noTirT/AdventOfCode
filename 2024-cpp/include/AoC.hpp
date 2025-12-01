#pragma once
#include <format>
#include <iostream>
#include <fstream>
#include <variant>
#include <vector>
#include <string>
#include <chrono>
#include <utils.hpp>

using Answer = std::variant<int64_t, std::string>;

class AoCDay {
public:
    virtual ~AoCDay() = default;
    virtual Answer part1() = 0;
    virtual Answer part2() = 0;

    void run(int day_number) {
        std::string filename = std::format("inputs/day{:02}.txt", day_number);

        lines = utils::read_lines(filename);

        std::cout << "--- Solution ---" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        auto solution1 = part1();
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Result for part 1: ";
        std::visit([](auto&& arg) {
            std::cout << arg;
        },solution1) ;
        std::cout << std::endl;
        print_time(start, end, "Part 1");

        start = std::chrono::high_resolution_clock::now();
        auto solution2 = part2();
        std::cout << "Result for part 2: ";
        std::visit([](auto&& arg) {
            std::cout << arg;
        },solution2) ;
        std::cout << std::endl;
        end = std::chrono::high_resolution_clock::now();
        print_time(start, end, "Part 2");
    }
protected:
    std::vector<std::string> lines;

private:
    void print_time(auto start, auto end, const std::string& label) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << label << " time: " << duration.count() << "µs" << std::endl;
    }
};

#define AOC_MAIN(DayClass) \
    int main(int argc, char* argv[]){ \
        DayClass solution; \
        solution.run(argc, argv); \
        return 0; \
    }
