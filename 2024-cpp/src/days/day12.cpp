#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <queue>
#include <utility>

class Day12 : public AoCDay {
private:
  std::vector<std::vector<int>> manhattan_directions = {
      {-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  std::vector<std::vector<int>> diagonal_directions = {
      {-1, 1}, {-1, -1}, {1, 1}, {1, -1}};

  struct Result {
    long long area = 0;
    long long perimeter = 0;
    long long corners = 0;
  };

  std::vector<std::vector<bool>> visited;

  bool is_same(int r, int c, char plantType) {
    if (r < 0 || c < 0 || r >= (int)lines.size() || c >= (int)lines[0].size()) {
      return false;
    }
    return lines[r][c] == plantType;
  }

  int count_corners(int row, int col, char plantType) {
    int corners = 0;

    for (int i = 0; i < 4; ++i) {
      int next_i = (i + 1) % 4;

      bool same_dir1 = is_same(row + manhattan_directions[i][0],
                               col + manhattan_directions[i][1], plantType);
      bool same_dir2 =
          is_same(row + manhattan_directions[next_i][0],
                  col + manhattan_directions[next_i][1], plantType);
      bool same_diag = is_same(
          row + manhattan_directions[next_i][0] + manhattan_directions[i][0],
          col + manhattan_directions[next_i][1] + manhattan_directions[i][1],
          plantType);

      if (!same_dir1 && !same_dir2)
        corners++;
      else if (same_dir1 && same_dir2 && !same_diag)
        corners++;
    }

    return corners;
  }

  Result flood_fill(int row, int col, char plantType) {
    std::queue<std::pair<int, int>> q;

    q.push({row, col});
    visited[row][col] = true;

    Result res;

    while (!q.empty()) {
      auto [curr_row, curr_col] = q.front();
      q.pop();

      res.area++;

      res.corners += count_corners(curr_row, curr_col, plantType);

      for (const auto &direction : manhattan_directions) {
        int new_row = curr_row + direction[0];
        int new_col = curr_col + direction[1];

        if (new_row < 0 || new_col < 0 || new_row >= (int)lines.size() ||
            new_col >= (int)lines[0].size()) {
          res.perimeter++;
          continue;
        }
        if (lines[new_row][new_col] != plantType) {
          res.perimeter++;
        } else {
          if (!visited[new_row][new_col]) {
            visited[new_row][new_col] = true;
            q.push({new_row, new_col});
          }
        }
      }
    }

    return res;
  }

public:
  Answer part1() override {
    // lines is available as std::vector<std::string>
    visited.assign(lines.size(), std::vector<bool>(lines[0].size(), false));
    std::vector<Result> results;

    for (size_t row = 0; row < lines.size(); ++row) {
      for (size_t col = 0; col < lines[0].size(); ++col) {
        if (!visited[row][col]) {
          auto temp = flood_fill(row, col, lines[row][col]);
          results.push_back(temp);
        }
      }
    }

    long result = 0;
    for (const auto &res : results) {
      result += res.area * res.perimeter;
    }
    return result;
  }

  Answer part2() override {
    visited.assign(lines.size(), std::vector<bool>(lines[0].size(), false));
    std::vector<Result> results;

    for (size_t row = 0; row < lines.size(); ++row) {
      for (size_t col = 0; col < lines[0].size(); ++col) {
        if (!visited[row][col]) {
          auto temp = flood_fill(row, col, lines[row][col]);
          results.push_back(temp);
        }
      }
    }
    long result = 0;
    for (const auto &res : results) {
      result += res.area * res.corners;
    }
    return result;
  }
};

static DayRegistrar<Day12> registrar(12);
