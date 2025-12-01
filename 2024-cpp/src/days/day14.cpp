#include "utils.hpp"
#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <cmath>
#include <map>
#include <regex>
#include <utility>

class Day14 : public AoCDay {
private:
  struct Robot {
    std::pair<int, int> position = {0, 0};
    std::pair<int, int> velocity = {0, 0};
  };

  std::vector<Robot> robots;

  std::regex robot_regex =
      std::regex(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");

  int width = 101;
  int height = 103;

  long calculate_safety_factor(std::vector<Robot> robots) {
    int omit_row = std::floor(height / 2);
    int omit_col = std::floor(width / 2);
    std::vector<long> quadrant_scores = {0, 0, 0, 0};

    for (const auto &robot : robots) {
      if (robot.position.first == omit_col || robot.position.second == omit_row)
        continue;
      if (robot.position.first < omit_col) {
        if (robot.position.second < omit_row) {
          quadrant_scores[0]++;
        } else if (robot.position.second > omit_row) {
          quadrant_scores[1]++;
        }
      } else if (robot.position.first > omit_col) {

        if (robot.position.second < omit_row) {
          quadrant_scores[2]++;
        } else if (robot.position.second > omit_row) {
          quadrant_scores[3]++;
        }
      }
    }

    long result = 1;
    for (const auto &score : quadrant_scores) {
      result *= score;
    }

    return result;
  }

  bool check_for_tree(std::vector<Robot> robots) {
    std::map<int, int> row_counts;
    std::map<int, int> col_counts;

    for (const auto &robot : robots) {
      row_counts[robot.position.second] += 1;
      col_counts[robot.position.first] += 1;
    }

    bool enough_rows = false;

    for (auto const &[key, val] : row_counts) {
      if (val >= 21) {
        enough_rows = true;
        break;
      }
    }
    for (auto const &[key, val] : col_counts) {
      if (val >= 21 && enough_rows) {
        return true;
      }
    }
    return false;
  }

public:
  void setup() override {
    for (const auto &line : lines) {
      std::smatch matches;

      if (std::regex_search(line, matches, robot_regex)) {
        Robot robot;
        robot.position = {std::stoi(matches[1]), std::stoi(matches[2])};
        robot.velocity = {std::stoi(matches[3]), std::stoi(matches[4])};

        robots.push_back(robot);
      }
    }
  }

  Answer part1() override {
    // lines is available as std::vector<std::string>
    auto robots_copy = robots;
    for (auto &robot : robots_copy) {
      robot.position.first =
          ((robot.position.first + 100 * robot.velocity.first) % width +
           width) %
          width;
      robot.position.second =
          ((robot.position.second + 100 * robot.velocity.second) % height +
           height) %
          height;
    }

    return calculate_safety_factor(robots_copy);
  }

  Answer part2() override {
    auto robots_copy = robots;
    for (int i = 0; i < 10000; ++i) {

      for (auto &robot : robots_copy) {
        robot.position.first =
            ((robot.position.first + robot.velocity.first) % width + width) %
            width;
        robot.position.second =
            ((robot.position.second + robot.velocity.second) % height +
             height) %
            height;
      }

      if (check_for_tree(robots_copy))
        return i + 1;
    }

    return 0;
  }
};

static DayRegistrar<Day14> registrar(14);
