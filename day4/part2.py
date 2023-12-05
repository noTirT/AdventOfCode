def read_file_lines(file_path):
    try:
        with open(file_path, "r") as file:
            lines = file.readlines()

            lines = [line.strip() for line in lines]

            return lines
    except FileNotFoundError:
        print(f"Die Datei {file_path} wurde nicht gefunden")
        return []
    
input_lines = read_file_lines("day4/input.txt")

result = 0

# TODO: not finished
for line in input_lines:
    own_nums, winning_nums = line.split(": ")[1].split(" | ")

    own_nums, winning_nums = own_nums.split(" "), winning_nums.split(" ")

    own_nums = list(filter(lambda num: num != "", own_nums))
    winning_nums = list(filter(lambda num: num != "", winning_nums))

    matches_amount = len(list(set(own_nums) & set(winning_nums)))
    
    value = int(2 ** (matches_amount- 1))
    result += value
print(result)