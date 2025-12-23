#pragma once
#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <utils.hpp>
#include <variant>
#include <vector>

using Answer = std::variant<int64_t, std::string>;

class AoCDay {
public:
  virtual ~AoCDay() = default;
  virtual void setup() {};
  virtual Answer part1() = 0;
  virtual Answer part2() = 0;

  void run(int day_number, bool test_run) {
    std::string filename =
        test_run ? std::format("examples/day{:02}.txt", day_number)
                 : std::format("inputs/day{:02}.txt", day_number);

    lines = utils::read_lines(filename);
    is_test_run = test_run;

    std::cout << "--- Running setup ... ---" << std::endl;

    setup();

    std::cout << "--- Solution for day " << day_number << " ---" << std::endl;

    measure_and_print("Part 1", [this]() { return part1(); });
    measure_and_print("Part 2", [this]() { return part2(); });
  }

protected:
  std::vector<std::string> lines;
  bool is_test_run;

private:
  void print_time(auto start, auto end, const std::string &label) {
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << label << " time: " << duration.count() << "µs" << std::endl;
  }

  std::string format_duration(std::chrono::microseconds duration) {
    double micros = static_cast<double>(duration.count());

    if (micros < 1000.0) {
      return std::format("{:.0f}µs", micros);
    } else if (micros < 1000000.0) {
      return std::format("{:.2f}ms", micros / 1000.0);
    } else {
      return std::format("{:.2f}s", micros / 1000000.0);
    }
  }

  template <typename Func>
  void measure_and_print(const std::string &label, Func &&func) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = func();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << label << ": ";
    std::visit([](auto &&arg) { std::cout << arg; }, result);
    std::cout << " (" << format_duration(duration) << ")" << std::endl;
  }
};
