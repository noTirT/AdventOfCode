#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <regex>
#include <vector>

class Day13 : public AoCDay {
private:
  struct GameRound {
    std::pair<long, long> directionA = {0, 0};
    std::pair<long, long> directionB = {0, 0};
    std::pair<long, long> prizeLocation = {0, 0};
  };

  std::vector<GameRound> rounds;

  std::regex pattern_button = std::regex(R"(X\+(\d+).*?Y\+(\d+))");
  std::regex pattern_prize = std::regex(R"(X\=(\d+).*?Y\=(\d+))");

public:
  void setup() override {
    for (size_t i = 0; i + 2 < lines.size(); i += 4) {
      GameRound round;
      std::smatch matches;

      if (std::regex_search(lines[i], matches, pattern_button)) {
        round.directionA = {std::stoi(matches[1].str()),
                            std::stoi(matches[2].str())};
      }

      if (std::regex_search(lines[i + 1], matches, pattern_button)) {
        round.directionB = {std::stoi(matches[1].str()),
                            std::stoi(matches[2].str())};
      }

      if (std::regex_search(lines[i + 2], matches, pattern_prize)) {
        round.prizeLocation = {std::stoi(matches[1].str()),
                               std::stoi(matches[2].str())};
      }
      rounds.push_back(round);
    }
  }

  Answer part1() override {
    // lines is available as std::vector<std::string>
    // A_times * a_x + B_times * b_x = goal_x
    // A_times * a_y + B_times * b_y = goal_y
    long long result = 0;

    for (const auto &round : rounds) {
      auto goal_x = round.prizeLocation.first;
      auto goal_y = round.prizeLocation.second;
      auto a_x = round.directionA.first;
      auto b_x = round.directionB.first;
      auto a_y = round.directionA.second;
      auto b_y = round.directionB.second;

      auto det = a_x * b_y - a_y * b_x;

      if (det == 0)
        continue;

      auto zaehler_a = goal_x * b_y - goal_y * b_x;
      auto zaehler_b = a_x * goal_y - a_y * goal_x;

      if (zaehler_a % det != 0 || zaehler_b % det != 0)
        continue;

      long long a_presses = zaehler_a / det;
      long long b_presses = zaehler_b / det;

      if (a_presses <= 100 && b_presses <= 100) {
        result += (a_presses * 3) + b_presses;
      }
    }

    return std::to_string(result);
  }

  Answer part2() override {
    long long result = 0;

    for (const auto &round : rounds) {
      auto goal_x = round.prizeLocation.first + 10000000000000;
      auto goal_y = round.prizeLocation.second + 10000000000000;
      auto a_x = round.directionA.first;
      auto b_x = round.directionB.first;
      auto a_y = round.directionA.second;
      auto b_y = round.directionB.second;

      auto det = a_x * b_y - a_y * b_x;

      if (det == 0)
        continue;

      auto zaehler_a = goal_x * b_y - goal_y * b_x;
      auto zaehler_b = a_x * goal_y - a_y * goal_x;

      if (zaehler_a % det != 0 || zaehler_b % det != 0)
        continue;

      long long a_presses = zaehler_a / det;
      long long b_presses = zaehler_b / det;

      result += (a_presses * 3) + b_presses;
    }

    return std::to_string(result);
  }
};

static DayRegistrar<Day13> registrar(13);
