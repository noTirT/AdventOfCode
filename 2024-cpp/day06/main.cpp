#include "utils.hpp"
#include <iostream>
#include <set>
#include <tuple>
#include <utility>

struct pair_hash {
  inline std::size_t operator()(const std::pair<int, int> &v) const {
    return v.first * 31 + v.second;
  }
};

bool check_bounds(const std::pair<int, int> &pos, int rows, int cols) {
  return (pos.first >= 0 && pos.first < rows && pos.second >= 0 &&
          pos.second < cols);
}

std::pair<int, int> project_position(std::pair<int, int> position,
                                     std::pair<int, int> direction) {
  return {position.first + direction.first, position.second + direction.second};
}

bool check_for_loop(std::vector<std::string> map,
                    std::pair<int, int> starting_position) {
  std::set<std::tuple<int, int, int, int>> visited;

  std::pair<int, int> direction = {-1, 0};
  std::pair<int, int> position = starting_position;

  int rows = map.size();
  int cols = map[0].size();

  while (check_bounds(position, rows, cols)) {
    auto future_position = project_position(position, direction);
    if (!check_bounds(future_position, rows, cols))
      break;

    if (map[future_position.first][future_position.second] == '#') {
      std::swap(direction.first, direction.second);
      direction.second *= -1;
      continue;
    }

    auto current_state = std::make_tuple(position.first, position.second,
                                         direction.first, direction.second);
    if (visited.count(current_state))
      return true;

    visited.insert(current_state);

    position = future_position;
  }

  return false;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: './main <input file.txt>'" << std::endl;
    return 1;
  }

  auto lines = utils::read_lines(argv[1]);
  auto original = lines;

  int result_1 = 1;
  int result_2 = 0;

  int row_count = lines.size();
  int col_count = lines[0].size();

  std::pair<int, int> cur_pos;
  std::pair<int, int> cur_direction = {-1, 0};

  for (int row = 0; row < row_count; ++row) {
    for (int col = 0; col < col_count; ++col) {
      if (lines[row][col] == '^')
        cur_pos = {row, col};
    }
  }

  auto original_starting_pos = cur_pos;

  while (check_bounds(cur_pos, row_count, col_count)) {
    auto future_position = project_position(cur_pos, cur_direction);
    if (!check_bounds(future_position, row_count, col_count))
      break;

    if (lines[future_position.first][future_position.second] == '#') {
      std::swap(cur_direction.first, cur_direction.second);
      cur_direction.second *= -1;
      continue;
    }

    lines[cur_pos.first][cur_pos.second] = 'X';
    cur_pos = future_position;
    lines[cur_pos.first][cur_pos.second] = 'X';
  }

  for (const auto &row : lines) {
    for (const auto &col : row) {
      if (col == 'X')
        ++result_1;
    }
  }

  for (int row = 0; row < row_count; ++row) {
    for (int col = 0; col < col_count; ++col) {
      if (original[row][col] == '#' || original[row][col] == '^')
        continue;

      auto temp = original;
      temp[row][col] = '#';

      if (check_for_loop(temp, original_starting_pos)) {
        ++result_2;
      }
    }
  }

  std::cout << "Result for part 1: " << result_1 << std::endl;
  std::cout << "Result for part 2: " << result_2 << std::endl;

  return 0;
}
