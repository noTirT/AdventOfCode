#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <map>
#include <string>

class Day15 : public AoCDay {
private:
  std::pair<int, int> player_position;
  std::map<char, std::pair<int, int>> walking_directions = {
      {'v', {0, 1}}, {'^', {0, -1}}, {'<', {-1, 0}}, {'>', {1, 0}}};
  std::vector<char> walking_plan;

  long long calculate_result(std::vector<std::string> &lines_array) {
    long long result = 0;

    for (int row = 0; row < (int)lines_array.size(); ++row) {
      auto line = lines_array[row];
      if (line.contains('#')) {
        size_t pos = line.find('O', 0);
        while (pos != std::string::npos) {
          result += 100 * row + pos;
          pos = line.find('O', pos + 1);
        }
      }
    }

    return result;
  }

  void iterate_line(int start_row, int start_col, char direction,
                    std::vector<std::string> &lines_array) {
    int cur_row = start_row;
    int cur_col = start_col;

    std::pair<int, int> direction_vector = walking_directions[direction];

    bool hit_free_space = false;

    while (lines_array[cur_row][cur_col] != '#') {
      if (lines_array[cur_row][cur_col] == '.') {
        hit_free_space = true;
        break;
      }
      cur_row += direction_vector.second;
      cur_col += direction_vector.first;
    }

    if (hit_free_space) {
      lines_array[cur_row][cur_col] = 'O';
      lines_array[start_row][start_col] = '.';
      lines_array[start_row + direction_vector.second]
                 [start_col + direction_vector.first] = '@';
      player_position = {start_row + direction_vector.second,
                         start_col + direction_vector.first};
    }
  }

public:
  void setup() override {
    for (int row = 0; row < (int)lines.size(); ++row) {
      auto line = lines[row];
      if (line.contains('#')) {
        size_t pos = line.find('@', 0);
        if (pos != std::string::npos) {
          player_position = {row, pos};
        }

      } else if (line.contains("v") || line.contains("^") ||
                 line.contains("<") || line.contains(">")) {
        for (const auto &dir : line) {
          walking_plan.push_back(dir);
        }
      }
    }
  }

  Answer part1() override {
    auto lines_copy = lines;
    for (const auto &move : walking_plan) {
      iterate_line(player_position.first, player_position.second, move,
                   lines_copy);
    }

    return calculate_result(lines_copy);
  }

  Answer part2() override {
    std::vector<std::string> lines_copy;

    for (size_t row = 0; row < lines.size(); ++row) {
      std::string col_str = "";
      for (size_t col = 0; col < lines[0].size(); ++col) {
        auto cur = lines[row][col];
        if (cur == 'O') {
          col_str.push_back('[');
          col_str.push_back(']');
        } else {
          col_str.push_back(cur);
          if (cur == '#' || cur == '.') {
            col_str.push_back(cur);
          } else if (cur == '@') {
            col_str.push_back('.');
          }
        }
      }
      lines_copy.push_back(col_str);
    }

    return "TODO";
  }
};

static DayRegistrar<Day15> registrar(15);
