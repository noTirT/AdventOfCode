import unittest
from typing import Tuple
from main import run_problem


from util import read_file_lines


class TestCalculation(unittest.TestCase):
    def test_day_1(self):
        a1, a2 = run_problem(1)
        s1, s2 = self.read_solution(1)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_2(self):
        a1, a2 = run_problem(2)
        s1, s2 = self.read_solution(2)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_3(self):
        a1, a2 = run_problem(3)
        s1, s2 = self.read_solution(3)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_4(self):
        a1, a2 = run_problem(4)
        s1, s2 = self.read_solution(4)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_5(self):
        a1, a2 = run_problem(5)
        s1, s2 = self.read_solution(5)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_6(self):
        a1, a2 = run_problem(6)

        s1, s2 = self.read_solution(6)

        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_7(self):
        a1, a2 = run_problem(7)

        s1, s2 = self.read_solution(7)

        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_8(self):
        a1, a2 = run_problem(8)

        s1, s2 = self.read_solution(8)

        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_9(self):
        a1, a2 = run_problem(9)
        s1, s2 = self.read_solution(9)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_10(self):
        a1, a2 = run_problem(10)
        s1, s2 = self.read_solution(10)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def test_day_11(self):
        a1, a2 = run_problem(11)
        s1, s2 = self.read_solution(11)
        self.assertEqual(a1, s1)
        self.assertEqual(a2, s2)

    def read_solution(self, day: int) -> Tuple[int, int]:
        solutions = read_file_lines(f"./day{day}/solutions.txt")
        return int(solutions[0]), int(solutions[1])


if __name__ == "__main__":
    unittest.main()
