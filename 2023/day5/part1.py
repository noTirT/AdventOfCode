from util import read_file_lines


def solution():
    def apply_map(
        initial_value, destination_range_start, source_range_start, range_length
    ):
        initial_value, destination_range_start, source_range_start, range_length = (
            int(initial_value),
            int(destination_range_start),
            int(source_range_start),
            int(range_length),
        )
        if (
            initial_value < source_range_start
            or initial_value > source_range_start + range_length
        ):
            return initial_value

        offset = initial_value - source_range_start
        return destination_range_start + offset

    input_lines = read_file_lines("day5/input.txt")

    seeds = input_lines[0].split(": ")[1].split(" ")

    curr_line_index = 1

    map_locations = {}

    keys = ["se2so", "so2fe", "fe2wa", "wa2li", "li2te", "te2hu", "hu2lo"]

    key_index = -1

    while curr_line_index < len(input_lines):
        curr_line = input_lines[curr_line_index]
        if len(curr_line) == 0:
            curr_line_index += 1
            continue

        if not curr_line[0].isdigit():
            key_index += 1
            map_locations.setdefault(keys[key_index], [])
        else:
            map_locations[keys[key_index]].append(curr_line.split(" "))

        curr_line_index += 1

    locations = []

    for seed in seeds:
        temp_seed = seed
        for curr_map in map_locations.values():
            for line in curr_map:
                converted_value = apply_map(temp_seed, line[0], line[1], line[2])
                if converted_value != int(temp_seed):
                    temp_seed = converted_value
                    break
        locations.append(temp_seed)

    return min(locations)
