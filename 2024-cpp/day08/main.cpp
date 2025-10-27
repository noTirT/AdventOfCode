#include <iostream>
#include <utils.hpp>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: './main <input file.txt>'" << std::endl;
    return 1;
  }

  auto lines = utils::read_lines(argv[1]);

  int result_1 = 0;
  int result_2 = 0;

  std::cout << "Result for part 1: " << result_1 << std::endl;
  std::cout << "Result for part 2: " << result_2 << std::endl;

  return 0;
}
