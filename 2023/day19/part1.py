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

def parse_input(mode: Literal["test", "input"]):
    lines = read_file_lines(f"day19/{mode}.txt")
    rules = {}
    parts_list = list() 

    parts = False
    for line in lines:
        if line == "":
            parts = True
            continue

        if not parts:
            line_split = line.replace("{", " ").replace("}", " ").split(" ")
            rules[line_split[0]] = Workflow(line_split[1])
        else:
            line = line.replace("{", "").replace("}", "")
            parts_list.append(tuple(map(lambda prop: int(prop.split("=")[1]), line.split(","))))
            
    return rules, parts_list

def solution():
    rules, parts = parse_input("input")

    accepted = []

    for part in parts:
        curr_rule = "in"
        while True:
            curr_flow = rules[curr_rule]
            curr_val = curr_flow.get_result(part)
            if curr_val == "A":
                accepted.append(part)
                break
            if curr_val == "R":
                break

            curr_rule = curr_val


    return sum(sum(accepted, ()))

