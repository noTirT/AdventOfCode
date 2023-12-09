from util import read_file_lines


def solution():
    input_lines = read_file_lines("day4/input.txt")

    result = 0

    for line in input_lines:
        own_nums, winning_nums = line.split(": ")[1].split(" | ")

        own_nums, winning_nums = own_nums.split(" "), winning_nums.split(" ")

        own_nums = list(filter(lambda num: num != "", own_nums))
        winning_nums = list(filter(lambda num: num != "", winning_nums))

        matches_amount = len(list(set(own_nums) & set(winning_nums)))

        value = int(2 ** (matches_amount - 1))
        result += value
    return result
