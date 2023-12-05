def read_file_lines(file_path):
    try:
        with open(file_path, "r") as file:
            lines = file.readlines()

            lines = [line.strip() for line in lines]

            return lines
    except FileNotFoundError:
        print(f"Die Datei {file_path} wurde nicht gefunden")
        return []
    
file_path = "input.txt"

input_arr = read_file_lines(file_path)

test_arr = ["1abc2", "pqr3stu8vwx", "a1b2c3d4e5f", "treb7uchet"]

test_2 = [
    "two1nine",
    "eightwothree",
    "abcone2threexyz",
    "xtwone3four",
    "4nineeightseven2",
    "zoneight234",
    "7pqrstsixteen",
]

str_nums = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5",
    "six": "6",
    "seven": "7",
    "eight": "8",
    "nine": "9",
}


def calc_config_sum(input_arr):
    sum = 0

    for line in input_arr:
        digits_locations = get_digits_locations(line)
        written_digits_locations = get_written_digits_locations(line)

        curr_first, curr_first_ind = -1, 2**20

        # Find first written digit
        for digit, locations in written_digits_locations.items():
            temp_min = min(locations)
            if temp_min < curr_first_ind:
                curr_first = digit
                curr_first_ind = temp_min

        # Find first digit
        for digit, locations in digits_locations.items():
            temp_min = min(locations)
            if temp_min < curr_first_ind:
                curr_first = digit
                curr_first_ind = temp_min

        curr_last, curr_last_ind = -1, -1

        # Find last written digit
        for digit, locations in written_digits_locations.items():
            temp_max = max(locations)
            if temp_max > curr_last_ind:
                curr_last = digit
                curr_last_ind = temp_max

        # Find last digit
        for digit, locations in digits_locations.items():
            temp_max = max(locations)
            if temp_max > curr_last_ind:
                curr_last = digit
                curr_last_ind = temp_max

        temp = int(f"{curr_first}{curr_last}")
        sum += temp

    return sum


def get_digits_locations(line):
    digits_locations = {}

    for index, character in enumerate(line):
        if character.isdigit():
            digits_locations.setdefault(character, [])
            digits_locations[character].append(index)

    return digits_locations


# TODO: check the whole string for each element. If i just use find then always the first is entered but we want to find all occurences so we must start the search from a certain index and increment that index
def get_written_digits_locations(line):
    digits_locations = {}

    for written_val, converted_val in str_nums.items():
        index = 0
        while index < len(line):
            temp_index = line.find(written_val, index)
            if temp_index == -1:
                break
            digits_locations.setdefault(converted_val, [])
            digits_locations[converted_val].append(temp_index)
            index += len(written_val)

    return digits_locations


print(calc_config_sum(input_arr))
