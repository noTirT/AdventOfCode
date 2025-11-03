#include <cstddef>
#include <iostream>
#include <map>
#include <utility>
#include <utils.hpp>

std::map<long, long> generate_index_map(std::string line) {
    std::map<long, long> result;

    bool is_free_block = false;
    long current_id = 0;
    long current_index = 0;

    for(long i = 0; i<line.length(); ++i) {
        long count = line[i] - '0';

        for(long i = 0; i<count; ++i) {
            result[current_index] = is_free_block ? -1: current_id;
            current_index++;
        }
        if(is_free_block) {
            is_free_block = false;
        } else {
            current_id++;
            is_free_block = true;
        }
    }

    return result;
}

std::string index_map_to_string(std::map<long, long> input) {
    std::string output = "";
    for(auto temp : input) {
        if(temp.second == -1) {
            output += '.';
            continue;
        }
        output += '0' + temp.second;
    }

    return output;
}

void rearrange_line(std::map<long, long> *input) {
    // Find first dot
    long first_dot_index;
    for(auto temp : *input) {
        if(temp.second == -1) {
            first_dot_index = temp.first;
            break;
        }
    }

    // Find last non-dot
    long last_non_dot_index;
    for(auto it = input->rbegin(); it != input->rend(); ++it) {
        if(it->second != -1) {
            last_non_dot_index = it->first;
            break;
        }
    }

    if(first_dot_index > last_non_dot_index) return;

    std::swap((*input)[first_dot_index], (*input)[last_non_dot_index]);

    rearrange_line(input);
}

long long calculate_checksum(std::string input) {
    long long result = 0;

    for(size_t i = 0; i<input.length(); ++i) {
        if(input[i] != '.') {
            result += (input[i] - '0') * i;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: './main <input file.txt>'" << std::endl;
        return 1;
    }

    auto lines = utils::read_lines(argv[1]);

    long long result_1 = 0;
    long long result_2 = 0;

    auto line = lines[0];

    auto index_map = generate_index_map(line);

    std::cout << "Generated index map" << std::endl;

    rearrange_line(&index_map);

    std::cout << "Rearranged lines" << std::endl;

    result_1 = calculate_checksum(index_map_to_string(index_map));

    std::vector<std::vector<long>> files;
    std::vector<std::vector<long>> free_spaces;

    long current_id = 0;

    for(size_t i = 0; i<line.length(); ++i) {
        if(i % 2 == 0) {
            files.push_back({current_id, (long)i, line[i]-'0'});
            current_id++;
        } else {
            free_spaces.push_back({(long)i, line[i]-'0'});
        }
    }

    for(int i = files.size() -1 ; i>= 0; --i) {
        for(int j = 0; j<free_spaces.size(); ++j) {
            auto temp = free_spaces[j];
            if(temp[1] >= files[i][2] && temp[0] < files[i][1]) {
                std::cout << "Swapping from index " << files[i][1] << " to " << temp[0] << " with source length " << files[i][2] << " and destination length " << temp[1] << std::endl;
                std::swap(free_spaces[j][0], files[i][1]);

                break;
            }
        }
    }

    std::vector<char> foo(files.size() + free_spaces.size());

    for(auto temp:files) {
        for(int i = 0; i<temp[2] ; ++i) {
            foo[temp[1] + i] = '0' + temp[0];
        }
    }

    utils::print_vector(foo);

    for(auto temp:free_spaces) {
        for(int i = 0; i<temp[1]; ++i) {
            foo[temp[0] + i] = '.';
        }
    }

    std::string str(foo.begin(), foo.end());

    std::cout << str << std::endl;
    result_2 = calculate_checksum(str);

    std::cout << "Result for part 1: " << result_1 << std::endl;
    std::cout << "Result for part 2: " << result_2 << std::endl;

    return 0;
}
