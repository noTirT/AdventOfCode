def read_file_lines(file_path):
    try:
        with open(file_path, "r") as file:
            lines = file.readlines()

            lines = [line.strip() for line in lines]

            return lines
    except FileNotFoundError:
        print(f"Die Datei {file_path} wurde nicht gefunden")
        return []


def solution():
    input_lines = read_file_lines("day4/input.txt")

    card_match_map = {}

    for index, line in enumerate(input_lines):
        card_num = line.split(": ")[0].split(" ")[-1]
        own_nums, winning_nums = line.split(": ")[1].split(" | ")

        own_nums, winning_nums = own_nums.split(" "), winning_nums.split(" ")

        own_nums = list(filter(lambda num: num != "", own_nums))
        winning_nums = list(filter(lambda num: num != "", winning_nums))

        matches_amount = len(list(set(own_nums) & set(winning_nums)))

        card_match_map[int(card_num)] = [
            additional for additional in range(index + 2, index + 2 + matches_amount)
        ]

    def dfs(card):
        card_match_map.setdefault(card, [])

        result = 1

        for el in card_match_map[card]:
            result += dfs(el)

        return result

    result = 0

    for key in card_match_map.keys():
        result += dfs(key)
    return result
