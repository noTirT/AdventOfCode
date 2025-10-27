#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <utils.hpp>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: './main <input file.txt>'" << std::endl;
    return 1;
  }

  auto lines = utils::read_lines(argv[1]);
  auto original = lines;

  boost::multiprecision::cpp_int result_1 = 0;
  boost::multiprecision::cpp_int result_2 = 0;

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

  std::cout << "Result for part 1: " << result_1 << std::endl;
  std::cout << "Result for part 2: " << result_2 << std::endl;

  return 0;
}
