from util import read_file_lines

input_lines = read_file_lines("day3/input.txt")

symbols = "*-$=#/%@&+"


def get_symbol_locations(input_lines):
    locations = []
    for row, line in enumerate(input_lines):
        for symbol in symbols:
            index = 0
            while index < len(line):
                temp_ind = line.find(symbol, index)
                if temp_ind == -1:
                    break
                locations.append((row, temp_ind))
                index = temp_ind + 1
    return locations


def search_around_location(location, input_lines):
    row, col = location

    max_row = len(input_lines) - 1
    max_col = len(input_lines[0]) - 1

    digit_locations = []

    locations_around = [
        (row + 1, col),  # below
        (row - 1, col),  # above
        (row, col + 1),  # right
        (row, col - 1),  # left
        (row + 1, col + 1),  # bottom right
        (row + 1, col - 1),  # bottom left
        (row - 1, col - 1),  # top left
        (row - 1, col + 1),  # top right
    ]

    for loc in locations_around:
        if loc[0] < 0 or loc[0] > max_row or loc[1] < 0 or loc[1] > max_col:
            break
        if input_lines[loc[0]][loc[1]].isdigit():
            digit_locations.append(loc)

    return eliminate_neighbor_locations(digit_locations)


def eliminate_neighbor_locations(locations):
    locations = sorted(locations)
    result = [locations[0]]
    index = 1
    while index < len(locations):
        if locations[index - 1][0] != locations[index][0]:
            result.append(locations[index])
        else:
            if abs(locations[index - 1][1] - locations[index][1]) != 1:
                result.append(locations[index])
        index += 1
    return result


def search_location(location, input_lines):
    num = []
    left, right = location[1] - 1, location[1]

    while left >= 0:
        curr_char = input_lines[location[0]][left]
        if curr_char.isdigit():
            num.insert(0, curr_char)
            left -= 1
        else:
            break

    while right < len(input_lines[location[0]]):
        curr_char = input_lines[location[0]][right]
        if curr_char.isdigit():
            num.append(curr_char)
            right += 1
        else:
            break

    return int("".join(num))


def solution():
    input_lines = read_file_lines("day3/input.txt")
    result = 0
    for symbol_location in get_symbol_locations(input_lines):
        digit_locations = search_around_location(symbol_location, input_lines)
        digits = [
            search_location(digit_location, input_lines)
            for digit_location in digit_locations
        ]
        result += sum(digits)
    return result
