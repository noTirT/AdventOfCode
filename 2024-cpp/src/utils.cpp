#include "utils.hpp"
#include <cstdint>
#include <fstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace utils {
std::vector<std::string> read_lines(const std::string &filename) {
  std::ifstream file(filename);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}
int variant_to_int(const std::variant<int64_t, std::string> &v) {
  return std::visit(
      [](const auto &value) -> int {
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>, int64_t>) {
          return static_cast<int>(value);
        } else { // std::string
          return std::stoi(value);
        }
      },
      v);
}
std::string variant_to_string(const std::variant<int64_t, std::string> &v) {
  return std::visit(
      [](const auto &value) -> std::string {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int64_t>) {
          return std::to_string(value);
        } else {
          return value;
        }
      },
      v);
}
} // namespace utils
