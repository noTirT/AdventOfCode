#include <iostream>
#include <DayRegistry.hpp>

int main(int argc, char* argv[]) {
    auto& registry = getDayRegistry();

    if(argc > 1) {
        int day = std::stoi(argv[1]);
        if(registry.count(day)) {
            registry[day]->run(day);
        } else {
            std::cout <<"Day " << day << " not found." <<std::endl;
        }
    } else if(!registry.empty()) {
        registry.rbegin()->second->run(registry.rbegin()->first);
    }

    return 0;
}
