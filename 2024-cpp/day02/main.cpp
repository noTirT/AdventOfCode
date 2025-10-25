#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

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

int main() {
    std::ifstream myfile("input.txt");
    if(!myfile) {
        std::cerr << "Failed to read file\n";
        return 1;
    }

    std::vector<std::vector<int>> reports;

    for(std::string line; std::getline(myfile, line);) {
        std::istringstream iss(line);

        std::vector<int> report;
        int level;

        while(iss >> level ) {
            report.push_back(level);
        }

        reports.push_back(report);
    }

    int save_reports_1 = 0;
    int save_reports_2 = 0;

    for(const auto& report : reports) {
        if(check_save(report)) {
            save_reports_1 += 1;
            save_reports_2 += 1;
        }
        else if(check_save_with_one_removed(report)) {
            save_reports_2 += 1;
        }
    }

    std::cout << "Save reports for task 1: " << save_reports_1 << std::endl;
    std::cout << "Save reports for task 2: " << save_reports_2 << std::endl;

    return 0;
}
