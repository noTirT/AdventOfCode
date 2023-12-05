
def read_file_lines(file_path):
    try:
        with open(file_path, "r") as file:
            lines = file.readlines()

            lines = [line.strip() for line in lines]

            return lines
    except FileNotFoundError:
        print(f"Die Datei {file_path} wurde nicht gefunden")
        return []
    

file_path = "day1/input.txt"

input_arr = read_file_lines(file_path)

test_arr = ["1abc2", "pqr3stu8vwx", "a1b2c3d4e5f", "treb7uchet"]


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


print(calc_config_sum(input_arr))
