#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <limits.h>
#include <cstdint>

class Day16 : public AoCDay {
private:
    int rows;
    int cols;
    struct State {
        int r, c, dir;
        int cost;

        bool operator>(const State& other) const {
            return cost > other.cost;
        }
    };

    // Dir: 0=North, 1=East, 2=South, 3=West
    static constexpr int dr[4] = {-1, 0, 1, 0};
    static constexpr int dc[4] = {0, 1, 0, -1};

    std::vector<std::vector<std::vector<int>>> dist;
    std::pair<int, int> goal;
    std::pair<int, int> start;
    std::map<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>> reverse_edges;

    int to_int(const std::variant<int64_t, std::string>& v) {
        return std::visit([](const auto& value) -> int {
            if constexpr (std::is_same_v<std::decay_t<decltype(value)>, int64_t>) {
                return static_cast<int>(value);
            } else { // std::string
                return std::stoi(value);
            }
        }, v);
    }
public:
    void setup() override {
        rows = (int)lines.size();
        cols = (int)lines[0].size();

        for(int row = 0; row < rows; ++row) {
            for(int col = 0; col < cols; ++col) {
                auto c = lines[row][col];
                if(c == 'S') {
                    start = {row, col};
                } else if(c == 'E') {
                    goal = {row, col};
                }
            }
        }

        std::priority_queue<State,std::vector<State>, std::greater<State>> pq;
        dist.assign(rows, std::vector<std::vector<int>>(cols, std::vector<int>(4, INT_MAX)));

        dist[start.first][start.second][1] = 0;
        pq.push({start.first, start.second, 1, 0});

        while(!pq.empty()) {
            const auto [row, col, dir, cost] = pq.top();
            pq.pop();

            if(cost > dist[row][col][dir]) {
                continue;
            }

            // Check forward step
            int nr = row + dr[dir];
            int nc = col + dc[dir];
            if(nr >= 0 && nr < rows && nc >= 0 && nc < cols && lines[nr][nc] != '#') {
                int new_cost = cost + 1;
                if(new_cost < dist[nr][nc][dir]) {
                    dist[nr][nc][dir] = new_cost;
                    pq.push({nr, nc, dir, new_cost});
                }
            }

            // Check clockwise turn
            int dir_cw = (dir+1)%4;
            int cost_turn = cost +1000;
            if(cost_turn < dist[row][col][dir_cw]) {
                dist[row][col][dir_cw] = cost_turn;
                pq.push({row, col, dir_cw, cost_turn});
            }

            // Check counter-clockwise turn
            int dir_ccw = (dir+3)%4;
            if(cost_turn < dist[row][col][dir_ccw]) {
                dist[row][col][dir_ccw] = cost_turn;
                pq.push({row, col, dir_ccw, cost_turn});
            }
        }
    }

    Answer part1() override {
        // lines is available as std::vector<std::string>
        auto goal_possible_directions = dist[goal.first][goal.second];
        int minimum_distance = INT_MAX;

        for(const auto &direction_distance: goal_possible_directions) {
            if(direction_distance < minimum_distance) minimum_distance = direction_distance;
        }

        return minimum_distance;
    }

    Answer part2() override {
        int best_cost = to_int(part1());

        std::queue<State> q;
        std::vector<std::vector<std::vector<bool>>> visited (lines.size(), std::vector<std::vector<bool>>(lines[0].size(),std::vector<bool>(4, false)));
        std::set<std::pair<int, int>> visited_tiles;

        for(int i = 0; i<4; ++i) {
            if(dist[goal.first][goal.second][i] == best_cost) {
                q.push({goal.first, goal.second, i, best_cost});
                visited_tiles.insert({goal.first, goal.second});
                visited[goal.first][goal.second][i] = true;
            }
        }

        while(!q.empty()) {
            auto [row, col, dir, cost] = q.front();
            q.pop();

            visited_tiles.insert({row, col});
            int pr = row - dr[dir];
            int pc = col - dc[dir];

            // Check if possible that we came with forward step to this state
            if(pr >= 0 && pr < rows && pc >= 0 && pc < rows && lines[pr][pc] != '#') {
                if(dist[pr][pc][dir] == cost -1) {
                    if(!visited[pr][pc][dir]) {
                        visited[pr][pc][dir] = true;
                        q.push({pr, pc, dir, cost-1});
                    }
                }
            }

            // Check if possible that we came with turn to this state
            int prev_dirs[] = {(dir+1)%4, (dir+3)%4};
            for(int t_d : prev_dirs) {
                if(dist[row][col][t_d] == cost -1000) {
                    if(!visited[row][col][t_d]) {
                        visited[row][col][t_d] = true;
                        q.push({row, col, t_d, cost -1000});
                    }
                }
            }
        }
        return (int)visited_tiles.size();
    }
};

static DayRegistrar<Day16> registrar(16);
