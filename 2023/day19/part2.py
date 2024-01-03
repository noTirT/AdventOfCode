from typing import List, Literal, Tuple
from util import read_file_lines

class Rule:
    def __init__(self, rule_string: str) -> None:
        s1 = rule_string.split(":")
        self.response = s1[1]
        formula = s1[0]
        if ">" in formula:
            self.operator = ">"
        elif "<" in formula:
            self.operator = "<"

        s2 = formula.split(self.operator)
        self.prop = s2[0]
        self.value = int(s2[1])

    def apply(self, test_value: int) -> bool:
        if self.operator == ">":
            return test_value > self.value
        else:
            return test_value < self.value

class Workflow:
    def __init__(self, workflow: str) -> None:
        self.rules: List[Rule] = []
        temp_rules = workflow.split(",")
        for rule in temp_rules[:-1]:
            self.rules.append(Rule(rule))
        self.default_response = temp_rules[-1]

    def get_result(self, part: Tuple[int, int, int, int]):
        for rule in self.rules:
            if rule.prop == "x":
                if rule.apply(part[0]):
                    return rule.response
            if rule.prop == "m":
                if rule.apply(part[1]):
                    return rule.response
            if rule.prop == "a":
                if rule.apply(part[2]):
                    return rule.response
            if rule.prop == "s":
                if rule.apply(part[3]):
                    return rule.response
        return self.default_response

def parse_input(mode: Literal["test", "input"]) -> List[Workflow]:
    lines = read_file_lines(f"day19/{mode}.txt")
    rules = {}

    for line in lines:
        if line == "": break

        line_split = line.replace("{", " ").replace("}", " ").split(" ")
        rules[line_split[0]] = Workflow(line_split[1])
            
    return rules 

def solution():
    workflows = parse_input("input")

    def count(ranges, name="in"):
        if name == "R":
            return 0

        if name == "A":
            product = 1
            for lo, hi in ranges.values():
                product *= hi - lo + 1
            return product

        workflow = workflows[name]

        total = 0

        for rule in workflow.rules:
            lo, hi = ranges[rule.prop]

            if rule.operator == "<":
                T = (lo, min(rule.value - 1, hi))
                F = (max(rule.value, lo), hi)
            else:
                T = (max(rule.value + 1, lo), hi)
                F = (lo, min(rule.value, hi))

            if T[0] <= T[1]:
                copy = dict(ranges)
                copy[rule.prop] = T
                total += count(copy, rule.response)
            if F[0] <= F[1]:
                ranges = dict(ranges)
                ranges[rule.prop] = F
            else: 
                break
        else: 
            total += count(ranges, workflow.default_response)
        return total 
    return count({key: (1,4000) for key in "xmas"})
