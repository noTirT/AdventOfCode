#include <AoC.hpp>
#include <DayRegistry.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wstringop-overread"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#include <boost/multiprecision/cpp_int.hpp>
#pragma GCC diagnostic pop

class Day07 : public AoCDay {
private:
  boost::multiprecision::cpp_int result_2;

public:
  Answer part1() override {
    auto original = lines;

    boost::multiprecision::cpp_int result_1 = 0;

    for (auto &equation : lines) {
      std::replace(equation.begin(), equation.end(), ':', ' ');

      std::istringstream iss(equation);
      std::vector<boost::multiprecision::cpp_int> parts;
      boost::multiprecision::cpp_int num;

      while (iss >> num) {
        parts.push_back(num);
      }

      boost::multiprecision::cpp_int result = parts[0];

      if (parts.size() < 3)
        continue;

      std::vector<boost::multiprecision::cpp_int> prev_sums = {parts[1]};

      for (size_t i = 2; i < parts.size(); ++i) {
        std::vector<boost::multiprecision::cpp_int> temp;
        if (prev_sums.size() <= 0)
          break;
        for (const auto &prev_sum : prev_sums) {
          boost::multiprecision::cpp_int mult = prev_sum * parts[i];
          boost::multiprecision::cpp_int add = prev_sum + parts[i];

          if (mult <= result)
            temp.push_back(mult);
          if (add <= result)
            temp.push_back(add);
        }
        prev_sums = temp;
      }

      if (std::find(prev_sums.begin(), prev_sums.end(), result) !=
          prev_sums.end()) {
        result_1 += result;
      }

      std::vector<boost::multiprecision::cpp_int> prev_sums_2 = {parts[1]};

      for (size_t i = 2; i < parts.size(); ++i) {
        std::vector<boost::multiprecision::cpp_int> temp;
        if (prev_sums_2.size() <= 0)
          break;
        for (const auto &prev_sum : prev_sums_2) {
          boost::multiprecision::cpp_int mult = prev_sum * parts[i];
          boost::multiprecision::cpp_int add = prev_sum + parts[i];
          boost::multiprecision::cpp_int concatenated(
              (prev_sum.str() + parts[i].str()));
          if (mult <= result)
            temp.push_back(mult);
          if (add <= result)
            temp.push_back(add);
          if (concatenated <= result)
            temp.push_back(concatenated);
        }
        prev_sums_2 = temp;
      }
      if (std::find(prev_sums_2.begin(), prev_sums_2.end(), result) !=
          prev_sums_2.end()) {
        result_2 += result;
      }
    }
    return result_1.str();
  }

  Answer part2() override { return result_2.str(); }
};

static DayRegistrar<Day07> registrar(7);
