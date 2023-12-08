import importlib
from typing import NewType, Tuple

Answer = NewType("Answer", any)


def get_problem_number() -> int:
    error_msg = "Invalid. Please enter a number in range of 1 through 25"

    problem: int
    while True:
        choice = input("Enter Problem number [1-25] to run: ")
        if choice.isnumeric():
            problem = int(choice)
            if 1 <= problem <= 25:
                break
            else:
                print(error_msg)
        else:
            print(error_msg)
    return problem


def run_problem(problem: int) -> Tuple[Answer, Answer]:
    module_name = f"day{problem}"
    part_1 = module_name + ".part1"
    part_2 = module_name + ".part2"

    module1 = importlib.import_module(part_1)
    module2 = importlib.import_module(part_2)

    part_one: Answer
    part_two: Answer

    try:
        part_one = module1.solution()
        part_two = module2.solution()
    except AttributeError:
        raise AttributeError(
            "Error. Loaded problem module must have a solution function"
        )
    return part_one, part_two


def __display_answer(answers: Tuple[Answer, Answer]):
    for i, v in enumerate(["one", "two"]):
        print(f"Part {v} answer:\n", answers[i], sep="")


def main():
    problem: int = get_problem_number()
    answers: Tuple[Answer, Answer] = run_problem(problem)
    __display_answer(answers)


if __name__ == "__main__":
    main()
