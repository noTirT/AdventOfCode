#include <algorithm>
#include <map>
#include <memory>
#include <AoC.hpp>

inline std::map<int, std::unique_ptr<AoCDay>> & getDayRegistry() {
    static std::map<int, std::unique_ptr<AoCDay>> registry;
    return registry;
}

template <typename T>
struct DayRegistrar {
    DayRegistrar(int day_num) {
        getDayRegistry()[day_num] = std::make_unique<T>();
    }
};
