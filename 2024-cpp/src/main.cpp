#include <DayRegistry.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  auto &registry = getDayRegistry();

  if (argc > 1) {
    int day = std::stoi(argv[1]);
    bool is_test = false;
    if (argc > 2) {
      std::string arg2 = argv[2];
      if (arg2 == "--test") {
        is_test = true;
      }
    }
    if (registry.count(day)) {
      registry[day]->run(day, is_test);
    } else {
      std::cout << "Day " << day << " not found." << std::endl;
    }
  } else if (!registry.empty()) {
    registry.rbegin()->second->run(registry.rbegin()->first, true);
  }

  return 0;
}
