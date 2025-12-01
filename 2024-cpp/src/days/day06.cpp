#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <set>
#include <tuple>

class Day06 : public AoCDay {
private:

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

public:
    Answer part1() override {
        int result_1 = 0;
        auto copy = lines;

        int row_count = copy.size();
        int col_count = copy[0].size();

        std::pair<int, int> cur_pos;
        std::pair<int, int> cur_direction = {-1, 0};

        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < col_count; ++col) {
                if (copy[row][col] == '^')
                    cur_pos = {row, col};
            }
        }

        while (check_bounds(cur_pos, row_count, col_count)) {
            auto future_position = project_position(cur_pos, cur_direction);
            if (!check_bounds(future_position, row_count, col_count))
                break;

            if (copy[future_position.first][future_position.second] == '#') {
                std::swap(cur_direction.first, cur_direction.second);
                cur_direction.second *= -1;
                continue;
            }

            copy[cur_pos.first][cur_pos.second] = 'X';
            cur_pos = future_position;
            copy[cur_pos.first][cur_pos.second] = 'X';
        }

        for (const auto &row : copy) {
            for (const auto &col : row) {
                if (col == 'X')
                    ++result_1;
            }
        }

        return result_1;
    }

    Answer part2() override {
        int result = 0;

        int row_count = lines.size();
        int col_count = lines[0].size();

        std::pair<int, int> cur_pos;

        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < col_count; ++col) {
                if (lines[row][col] == '^')
                    cur_pos = {row, col};
            }
        }

        auto original_starting_pos = cur_pos;

        for (int row = 0; row < row_count; ++row) {
            for (int col = 0; col < col_count; ++col) {
                if (lines[row][col] == '#' || lines[row][col] == '^')
                    continue;

                auto temp = lines;
                temp[row][col] = '#';

                if (check_for_loop(temp, original_starting_pos)) {
                    ++result;
                }
            }
        }
        return result;
    }
};

static DayRegistrar<Day06> registrar(6);
