#include <AoC.hpp>
#include <DayRegistry.hpp>
#include <regex>
#include <sstream>

class Day17 : public AoCDay {
private:
    long A;
    long B;
    long C;
    std::vector<int> program;

    std::regex pattern_register = std::regex(R"(Register.*?(\d+))");

    void execute(int code, int operand) {
        switch (code) {
        case 2:
            B = operand % 8;
            break;

        }
    }
public:
    void setup() override {
        std::smatch matches;
        if(std::regex_search(lines[0], matches, pattern_register)) {
            A = std::stoi(matches[1].str());
        }

        if(std::regex_search(lines[1], matches, pattern_register)) {
            B = std::stoi(matches[1].str());
        }

        if(std::regex_search(lines[2], matches, pattern_register)) {
            C = std::stoi(matches[1].str());
        }

        std::string &program_line = lines[4];
        std::replace(program_line.begin(), program_line.end(), ',', ' ');

        std::istringstream iss(program_line);
        std::string program_point;
        std::vector<std::string> temp;

        while(iss >> program_point) {
            std::cout << program_point << std::endl;
            temp.push_back(program_point);
        }
        for(int i = 1; i<(int)temp.size(); ++i ) {
            program.push_back(std::stoi(temp[i]));
        }
    }

    Answer part1() override {
        // lines is available as std::vector<std::string>
        for(int instr_ptr = 0; instr_ptr < (int)program.size()-1; instr_ptr+=2) {
            int opcode = program[instr_ptr];
            int operand = program[instr_ptr+1];
        }
        return "TODO";
    }

    Answer part2() override {
        return "TODO";
    }
};

static DayRegistrar<Day17> registrar(17);
