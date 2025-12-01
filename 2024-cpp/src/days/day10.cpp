#include "utils.hpp"
#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <queue>
#include <vector>

class Day10 : public AoCDay {
private:
  std::vector<std::vector<int>> possible_directions = {
      {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  std::vector<std::vector<size_t>> trailheads;

  std::vector<std::vector<size_t>> find_next_steps(size_t row, size_t col) {
    std::vector<std::vector<size_t>> result;
    int cur_val = lines[row][col] - '0';

    for (const auto &direction : possible_directions) {
      int new_row = row + direction[0];
      int new_col = col + direction[1];

      int new_val = lines[new_row][new_col] - '0';

      if (new_row < 0 || new_row >= (int)lines.size() || new_col < 0 ||
          new_col >= (int)lines[0].size())
        continue;

      if (new_val == cur_val + 1) {
        result.push_back({row + direction[0], col + direction[1]});
      }
    }

    return result;
  }

public:
  Answer part1() override {
    trailheads.clear();
    for (size_t row = 0; row < lines.size(); ++row) {
      for (size_t col = 0; col < lines[0].size(); ++col) {
        if (lines[row][col] == '0')
          trailheads.push_back({row, col});
      }
    }

    int result = 0;

    for (auto temp : trailheads) {
      int temp_result = 0;
      std::vector<std::vector<size_t>> visited;
      std::queue<std::vector<size_t>> coord_queue;

      for (auto temp2 : find_next_steps(temp[0], temp[1]))
        coord_queue.push(temp2);

      while (!coord_queue.empty()) {
        auto curr_coords = coord_queue.front();
        coord_queue.pop();

        if (lines[curr_coords[0]][curr_coords[1]] == '9') {
          if (std::find(visited.begin(), visited.end(), curr_coords) ==
              visited.end()) {
            visited.push_back(curr_coords);
            ++temp_result;
          }
        } else {
          auto next_steps = find_next_steps(curr_coords[0], curr_coords[1]);
          for (auto step : next_steps) {
            coord_queue.push(step);
          }
        }
      }

      result += temp_result;
    }

    return result;
  }

  Answer part2() override {
    trailheads.clear();
    for (size_t row = 0; row < lines.size(); ++row) {
      for (size_t col = 0; col < lines[0].size(); ++col) {
        if (lines[row][col] == '0')
          trailheads.push_back({row, col});
      }
    }

    int result = 0;

    std::queue<std::vector<size_t>> coord_queue;
    for (auto temp : trailheads) {
      coord_queue.push(temp);
    }

    while (!coord_queue.empty()) {
      auto curr_coords = coord_queue.front();
      coord_queue.pop();

      if (lines[curr_coords[0]][curr_coords[1]] == '9') {
        ++result;
      } else {
        auto next_steps = find_next_steps(curr_coords[0], curr_coords[1]);
        for (auto step : next_steps) {
          coord_queue.push(step);
        }
      }
    }
    return result;
  }
};

static DayRegistrar<Day10> registrar(10);
