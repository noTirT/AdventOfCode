#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace utils {
std::vector<std::string> read_lines(const std::string &filename);

template <typename T> void print_vector(const std::vector<T> &vec) {
    for (const auto &v : vec)
        std::cout << v << " ";
    std::cout << "\n";
}

template <typename T>
void print_vector(const std::vector<T> &vec, char delimiter) {
    for (const auto &v : vec)
        std::cout << v << delimiter;
    std::cout << "\n";
}

template <typename T>
void print_matrix(const std::vector<std::vector<T>> &mat) {
    for (const auto &row : mat)
        print_vector(row);
}

} // namespace utils
