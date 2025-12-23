#include "utils.hpp"
#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <algorithm>
#include <sstream>
#include <vector>

class Day18 : public AoCDay {
private:
  std::vector<std::vector<bool>> byte_corrupted;
  std::pair<int, int> start = {0, 0};
  std::pair<int, int> goal;

public:
  void setup() override {
    int size = is_test_run ? 7 : 71;
    int bytes_simulated = is_test_run ? 12 : 1024;

    if (is_test_run) {
      goal = {6, 6};
    } else {
      goal = {70, 70};
    }

    byte_corrupted.assign(size, std::vector<bool>(size, false));

    for (int i = 0; i < bytes_simulated; ++i) {
      std::string line = lines[i];
      std::replace(line.begin(), line.end(), ',', ' ');
      std::istringstream iss(line);
      int a, b;

      if (iss >> a >> b) {
        byte_corrupted[b][a] = true;
      }
    }
  }

  Answer part1() override {
    // lines is available as std::vector<std::string>

    return "TODO";
  }

  Answer part2() override { return "TODO"; }
};

static DayRegistrar<Day18> registrar(18);
