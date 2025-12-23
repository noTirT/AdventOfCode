#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <regex>
#include <sstream>
#include <utils.hpp>

class Day17 : public AoCDay {
private:
  long long A;
  long long B;
  long long C;
  std::vector<int> program;
  int instr_ptr = 0;

  std::regex pattern_register = std::regex(R"(Register.*?(\d+))");

  long long get_operand_value(int operand) {
    switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
      return operand;
    case 4:
      return A;
    case 5:
      return B;
    case 6:
      return C;
    }
    return -1;
  }

  long long execute(int code, int operand) {
    switch (code) {
    case 0:
      A = A >> get_operand_value(operand);
      instr_ptr += 2;
      return -1;
    case 1:
      B ^= operand;
      instr_ptr += 2;
      return -1;
    case 2:
      B = get_operand_value(operand) % 8;
      instr_ptr += 2;
      return -1;
    case 3:
      if (A == 0) {
        instr_ptr += 2;
        return -1;
      }
      instr_ptr = operand;
      return -1;
    case 4:
      B ^= C;
      instr_ptr += 2;
      return -1;
    case 5:
      instr_ptr += 2;
      return get_operand_value(operand) % 8;
    case 6:
      B = A >> get_operand_value(operand);
      ;
      instr_ptr += 2;
      return -1;
    case 7:
      C = A >> get_operand_value(operand);
      instr_ptr += 2;
      return -1;
    }
    return -1;
  }

public:
  void setup() override {
    std::smatch matches;
    if (std::regex_search(lines[0], matches, pattern_register)) {
      A = std::stoi(matches[1].str());
    }

    if (std::regex_search(lines[1], matches, pattern_register)) {
      B = std::stoi(matches[1].str());
    }

    if (std::regex_search(lines[2], matches, pattern_register)) {
      C = std::stoi(matches[1].str());
    }

    std::string &program_line = lines[4];
    std::replace(program_line.begin(), program_line.end(), ',', ' ');

    std::istringstream iss(program_line);
    std::string program_point;
    std::vector<std::string> temp;

    while (iss >> program_point) {
      temp.push_back(program_point);
    }

    for (int i = 1; i < (int)temp.size(); ++i) {
      program.push_back(std::stoi(temp[i]));
    }
  }

  Answer part1() override {
    // lines is available as std::vector<std::string>
    std::vector<char> output;
    while (instr_ptr < (int)program.size()) {
      int opcode = program[instr_ptr];
      int operand = program[instr_ptr + 1];

      long long result = execute(opcode, operand);
      if (result == -1)
        continue;

      for (const auto &c : std::to_string(result)) {
        output.push_back(c);
      }
    }

    std::ostringstream oss;
    oss << output[0];

    for (size_t i = 1; i < output.size(); ++i) {
      oss << "," << output[i];
    }
    return oss.str();
  }

  Answer part2() override {
    for (int i = 0; i < 8; ++i) {
      instr_ptr = 0;
      A = i;
      auto const &result = part1();
      std::cout << utils::variant_to_string(result) << std::endl;
    }
    return "TODO";
  }
};

static DayRegistrar<Day17> registrar(17);
