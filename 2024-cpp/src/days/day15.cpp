#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <map>
#include <string>

class Day15 : public AoCDay {
private:
    std::vector<std::pair<int, int>> boxes;
    std::pair<int, int> player_position;
    std::map<char, std::pair<int, int>> walking_directions = {
        {'v', {0, 1}}, {'^', {0, -1}}, {'<', {-1, 0}}, {'>', {1, 0}}
    };

    std::vector<std::pair<int, int>> walking_plan;

public:
    void setup() override {
        for (int row = 0; row < (int)lines.size(); ++row) {
            auto line = lines[row];
            if (line.contains('#')) {
                size_t pos = line.find('O', 0);
                while (pos != std::string::npos) {
                    boxes.push_back({row, pos});
                    pos = line.find('O', pos + 1);
                }

                pos = line.find('@', 0);
                if (pos != std::string::npos) {
                    player_position = {row, pos};
                }
            } else if (line.contains("v") || line.contains("^") ||
                       line.contains("<") || line.contains(">")) {
                for (const auto &dir : line) {
                    walking_plan.push_back(walking_directions[dir]);
                }
            }
        }
    }

    Answer part1() override {
        // lines is available as std::vector<std::string>
        return "TODO";
    }

    Answer part2() override {
        return "TODO";
    }
};

static DayRegistrar<Day15> registrar(15);
