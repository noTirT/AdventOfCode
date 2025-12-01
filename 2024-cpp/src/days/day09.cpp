#include <AoC.hpp>
#include <DayRegistry.hpp>

class Day09 : public AoCDay {
public:
    Answer part1() override {
        long long result_1 = 0;

        auto line = lines[0];

        std::vector<long long> representation;

        long curr_id = 0;

        for(size_t i = 0; i<line.length(); ++i) {
            int count = line[i] -'0';
            if(i %2 == 0) {
                for(int j = 0; j<count; ++j) {
                    representation.push_back(curr_id);
                }
                curr_id++;
            } else {
                for(int j = 0; j<count; ++j) {
                    representation.push_back(-1);
                }
            }
        }
        rearrange_line(representation);

        result_1 = calculate_checksum(representation);

        return result_1;
    }

    Answer part2() override {
        return "TODO";
    }
private:
    void rearrange_line(std::vector<long long> &input) {
        long left = 0;
        long right = input.size()-1;

        while(left < right) {
            while(left < input.size() && input[left] != -1) left++;
            while(right >= 0 && input[right] == -1) right--;

            if(right <= left) break;

            std::swap(input[left], input[right]);
        }
    }


    long long calculate_checksum(std::vector<long long > input) {
        long long result = 0;

        for(size_t i = 0; i<input.size(); ++i) {
            if(input[i] != -1) {
                result += input[i]*i;
            }
        }

        return result;
    }
};

static DayRegistrar<Day09> registrar(9);
