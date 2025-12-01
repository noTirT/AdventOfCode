
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <functional>
#include <AoC.hpp>
#include <DayRegistry.hpp>

class Day02 : public AoCDay {
private:
    std::vector<std::vector<int>> reports;

public:
    Answer part1() override {
        for(const auto& line: lines) {
            std::istringstream iss(line);

            std::vector<int> report;
            int level;

            while(iss >> level ) {
                report.push_back(level);
            }

            reports.push_back(report);
        }
        int save_reports_1 = 0;

        for(const auto& report : reports) {
            if(check_save(report)) {
                save_reports_1 += 1;
            }
        }

        return save_reports_1;
    }

    Answer part2() override {
        int result = 0;
        for(const auto& report : reports) {
            if(check_save(report)) {
                result += 1;
            }
            else if(check_save_with_one_removed(report)) {
                result += 1;
            }
        }

        return result;
    }

private:
    bool check_save_with_one_removed(const std::vector<int>& report) {
        for(size_t i = 0; i<report.size(); ++i) {
            std::vector<int> temp;
            temp.reserve(report.size() - 1);
            for(size_t j = 0; j<report.size(); ++j) {
                if(j!= i) temp.push_back(report[j]);
            }
            if(check_save(temp)) return true;
        }
        return false;
    }
    bool check_save(const std::vector<int>& report) {
        bool descending = true, ascending = true;

        for(size_t i = 1; i<report.size(); ++i) {
            if(report[i] > report[i-1])
                descending = false;
            if(report[i]<report[i-1])
                ascending = false;

            int diff = std::abs(report[i] - report[i-1]);
            if(diff<1 || diff >3) return false;
        }
        return descending || ascending;
    }
};

static DayRegistrar<Day02> registrar(2);
