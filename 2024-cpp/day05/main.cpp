#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utils.hpp>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: './main <input file.txt>'" << std::endl;
    return 1;
  }

  auto lines = utils::read_lines(argv[1]);

  int result_1 = 0;
  int result_2 = 0;

  int row_count = lines.size();

  std::unordered_map<int, std::unordered_set<int>> dependencies;
  std::vector<std::vector<int>> updates;

  for (int row = 0; row < row_count; ++row) {
    std::string current = lines[row];
    if (current.find('|') != std::string::npos) {
      std::replace(current.begin(), current.end(), '|', ' ');

      int a, b;
      std::istringstream iss(current);

      if (iss >> a >> b) {
        if (dependencies.find(b) == dependencies.end()) {
          dependencies[b] = {a};
        } else {
          dependencies[b].insert(a);
        }
      }
    } else if (current.find(',') != std::string::npos) {
      std::replace(current.begin(), current.end(), ',', ' ');

      std::istringstream iss(current);
      std::vector<int> update;
      int update_point;

      while (iss >> update_point) {
        update.push_back(update_point);
      }

      updates.push_back(update);
    }
  }

  // Start checking the updates

  for (auto &update : updates) {
    bool failed = false;
    for (size_t update_point_index = 0; update_point_index < update.size();
         ++update_point_index) {
      auto elem = update[update_point_index];
      auto dep = dependencies[elem];

      for (const auto &dependency_item : dep) {
        auto it = std::find(update.begin(), update.end(), dependency_item);
        auto found_index = (size_t)std::distance(update.begin(), it);

        if (it != update.end() && found_index > update_point_index) {
          failed = true;
        }
      }
    }

    if (!failed)
      result_1 += update[std::floor(update.size() / 2)];
    else {
      std::vector<int> tmp_vector = {};
      for (auto num : update) {
        if (tmp_vector.size() == 0) {
          tmp_vector.push_back(num);
          continue;
        }
        int insert_in_index = -1;
        for (size_t i = 0; i < tmp_vector.size(); ++i) {
          if (dependencies.find(tmp_vector[i]) == dependencies.end())
            insert_in_index = i;
          else if (dependencies.at(tmp_vector[i]).find(num) !=
                   dependencies.at(tmp_vector[i]).end())
            continue;
          else
            insert_in_index = i;
          break;
        }
        if (insert_in_index == -1)
          tmp_vector.push_back(num);
        else
          tmp_vector.insert(tmp_vector.begin() + insert_in_index, num);
      }
      result_2 += tmp_vector[std::floor(tmp_vector.size() / 2)];
    }
  }

  std::cout << "Result for part 1: " << result_1 << std::endl;
  std::cout << "Result for part 2: " << result_2 << std::endl;

  return 0;
}
