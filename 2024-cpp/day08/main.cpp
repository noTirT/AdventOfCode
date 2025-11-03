#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <utils.hpp>

bool check_boundaries(std::pair<int, int> point, int rows, int cols) {
    return (point.first >= 0 && point.first < rows && point.second >= 0 && point.second < cols);
}

std::vector<std::pair<int, int>> interpolate_antenna_locations(std::pair<int, int> pos1, std::pair<int, int> pos2) {
    auto diff_row = (pos1.first - pos2.first);
    auto diff_col = (pos1.second - pos2.second);

    return {
        {
            pos1.first + diff_row,
            pos1.second + diff_col
        },
        {
            pos2.first - diff_row,
            pos2.second - diff_col,
        }
    };
}

std::vector<std::pair<int, int>> interpolate_all_antenna_locations(std::pair<int, int> pos1, std::pair<int, int> pos2, int rows, int cols) {
    std::vector<std::pair<int, int>> points;

    auto diff_row = (pos1.first - pos2.first);
    auto diff_col = (pos1.second - pos2.second);

    std::pair<int, int> temp = {pos1.first + diff_row, pos1.second + diff_col};

    while(check_boundaries(temp, rows, cols)) {
        points.push_back(temp);
        temp = {
            temp.first + diff_row,
            temp.second + diff_col
        };
    }

    temp = {pos2.first - diff_row, pos2.second - diff_col};

    while(check_boundaries(temp, rows, cols)) {
        points.push_back(temp);
        temp = {
            temp.first - diff_row,
            temp.second - diff_col
        };
    }

    return points;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: './main <input file.txt>'" << std::endl;
        return 1;
    }

    auto lines = utils::read_lines(argv[1]);
    auto lines_copy = lines;

    int result_1 = 0;
    int result_2 = 0;

    std::unordered_map<char, std::vector<std::pair<int, int>>> antenna_location_map;

    for(size_t row = 0; row < lines.size(); ++row) {
        for(size_t col = 0; col < lines[row].size(); ++col) {
            auto element = lines[row][col];

            if(element == '.') continue;

            if(antenna_location_map.find(element) == antenna_location_map.end()) {
                antenna_location_map[element] = {{row, col}};
            } else {
                antenna_location_map[element].push_back({row, col});
            }
        }
    }

    std::set<std::pair<int, int>> unique_affected_points;

    for(auto it : antenna_location_map) {
        auto locations = it.second;

        for(size_t i = 0; i < locations.size()-1; ++i) {
            for(size_t j = i + 1; j < locations.size(); ++j) {
                auto projected_points = interpolate_antenna_locations(locations[i],locations[j]);

                for(auto point : projected_points) {
                    if(check_boundaries(point, lines.size(), lines[0].size())) {
                        lines[point.first][point.second] = '#';
                    }
                }

                auto all_projected = interpolate_all_antenna_locations(locations[i], locations[j], lines.size(), lines[0].size());
                for(auto point : all_projected) {
                    if(check_boundaries(point, lines.size(), lines[0].size())) {
                        lines_copy[point.first][point.second] = '#';
                    }
                }
            }
        }
    }

    for(const auto& row : lines) {
        for(const auto& letter : row) {
            if(letter == '#') ++result_1;
        }
    }

    for(const auto& row : lines_copy) {
        for(const auto& letter : row) {
            if(letter != '.') ++result_2;
        }
    }

    std::cout << "Result for part 1: " << result_1 << std::endl;
    std::cout << "Result for part 2: " << result_2 << std::endl;

    return 0;
}
