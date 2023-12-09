from util import read_file_lines


def calc_config_sum(input_arr):
    sum = 0
    for line in input_arr:
        left, right = 0, len(line) - 1
        first, last = "", ""
        while left <= right and (first == "" or last == ""):
            if line[left].isdigit():
                first = line[left]
            if line[right].isdigit():
                last = line[right]
            if first == "":
                left += 1
            if last == "":
                right -= 1

        temp = int(f"{first}{last}")
        sum += temp
    return sum


def solution():
    input_arr = read_file_lines("day1/input.txt")
    return calc_config_sum(input_arr)
