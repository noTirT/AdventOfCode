#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class Day11 : public AoCDay {
private:
  bool has_even_digit_num(long long i) {
    return std::to_string(i).length() % 2 == 0;
  }

  std::vector<std::string> halve_string(std::string s) {
    size_t mid = s.length() / 2;

    return {s.substr(0, mid), s.substr(mid)};
  }

public:
  Answer part1() override {
    std::vector<long long> stones;
    for (const auto &line : lines) {
      std::istringstream iss(line);
      long long level;

      while (iss >> level) {
        stones.push_back(level);
      }
    }

    for (int i = 0; i < 25; ++i) {
      std::vector<long long> next_stones;
      for (long long num : stones) {
        if (num == 0) {
          next_stones.push_back(1);
        } else if (has_even_digit_num(num)) {
          auto halves = halve_string(std::to_string(num));
          next_stones.push_back(std::stoll(halves[0]));
          next_stones.push_back(std::stoll(halves[1]));
        } else {
          next_stones.push_back(num * 2024);
        }
      }
      stones = next_stones;
    }

    return (long long)stones.size();
  }

  Answer part2() override {
    std::map<long long, long long> stone_counts;
    for (const auto &line : lines) {
      std::istringstream iss(line);
      long long level;

      while (iss >> level) {
        stone_counts[level]++;
      }
    }

    for (int i = 0; i < 75; ++i) {
      std::map<long long, long long> next_counts;
      for (auto const &[stone, count] : stone_counts) {
        if (stone == 0) {
          next_counts[1] += count;
        } else if (has_even_digit_num(stone)) {
          auto halves = halve_string(std::to_string(stone));
          next_counts[std::stoll(halves[0])] += count;
          next_counts[std::stoll(halves[1])] += count;
        } else {
          next_counts[stone * 2024] += count;
        }
      }
      stone_counts = next_counts;
    }

    long long total = 0;
    for (auto const &[stone, count] : stone_counts) {
      total += count;
    }

    return total;
  }
};

static DayRegistrar<Day11> registrar(11);
