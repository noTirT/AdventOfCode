#include <AoC.hpp>
#include <DayRegistry.hpp>

class Day04 : public AoCDay {
private:

public:
    Answer part1() override {
        int row_count = lines.size();
        int col_count = lines[0].length();

        std::vector<std::pair<int, int>> directions_1 = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        std::string target_1 = "XMAS";

        int result = 0;

        for(int row = 0; row < row_count; ++row) {
            for(int col = 0; col < col_count; ++col) {
                // Solve part 1
                if(lines[row][col] == 'X') {
                    for(auto dir : directions_1) {
                        int x = row;
                        int y = col;

                        for(int i = 1; i<= 3; ++i) {
                            x += dir.first;
                            y += dir.second;
                            if(x >= 0 && x < row_count && y >= 0 && y < col_count && lines[x][y] == target_1[i]) {
                                if(i == 3)
                                    result++;
                            } else break;
                        }
                    }
                }
            }
        }
        return result;
    }

    Answer part2() override {
        int result = 0;

        int row_count = lines.size();
        int col_count = lines[0].length();

        std::vector<std::pair<int, int>> directions_2 = {{1, 1}};
        std::vector<std::string> targets_2 = {"MAS", "SAM"};

        for(int row = 0; row < row_count; ++row) {
            for(int col = 0; col < col_count; ++col) {
                for(auto target : targets_2) {
                    bool passed_first = false;
                    if(lines[row][col] == target[0]) {
                        int x = row;
                        int y = col;
                        for(int i = 1; i<= 2; ++i) {
                            x += 1;
                            y += 1;

                            if(x >= 0 && x < row_count && y >= 0 && y < col_count && lines[x][y] == target[i]) {
                                if(i == 2)
                                    passed_first = true;
                            } else break;
                        }
                    }
                    if(passed_first) {
                        for(auto target : targets_2) {
                            if(col+2 < col_count && lines[row][col+2] == target[0]) {
                                int x = row;
                                int y = col+2;
                                for(int i = 1; i<= 2; ++i) {
                                    x += 1;
                                    y -= 1;

                                    if(x >= 0 && x < row_count && y >= 0 && y < col_count && lines[x][y] == target[i]) {
                                        if(i == 2)
                                            result++;
                                    } else break;
                                }
                            }

                        }
                    }
                }
            }
        }
        return result;
    }
};

static DayRegistrar<Day04> registrar(4);
