from typing import Literal
from collections import deque
from util import read_file_lines

class Module:
    def __init__(self, name, type, outputs) -> None:
        self.name = name
        self.type = type
        self.outputs = outputs

        if type == "%":
            self.memory = "off"
        else: 
            self.memory = {}

    def __repr__(self) -> str:
        return self.name + "{type=" + self.type + ",outputs=" + ",".join(self.outputs) + ",memory=" + str(self.memory) + "}"

def solution():
    mode: Literal["test", "input"] = "input"
    lines = read_file_lines(f"day20/{mode}.txt")

    modules = {}
    broadcaster_targets = []

    for line in lines:
        module_definition, module_target = line.split(" -> ")
        outputs = module_target.split(", ")

        if module_definition == "broadcaster":
            broadcaster_targets = outputs

        else:
            type = module_definition[0]
            name = module_definition[1:]
            modules[name] = Module(name, type, outputs)
    
    for name, module in modules.items():
        for output in module.outputs:
            if output in modules and modules[output].type == "&":
                modules[output].memory[name] = "lo"

    lo = hi = 0

    for _ in range(1000):
        lo += 1
        q = deque([("broadcaster", x, "lo") for x in broadcaster_targets])

        while q:
            origin, target, pulse = q.popleft()

            if pulse == "lo":
                lo += 1
            else:
                hi += 1

            if target not in modules:
                continue
            
            module = modules[target]

            if module.type == "%":
                if pulse == "lo":
                    module.memory = "on" if module.memory == "off" else "off"
                    outgoing = "hi" if module.memory == "on" else "lo"
                    for x in module.outputs:
                        q.append((module.name, x, outgoing))
            else:
                module.memory[origin] = pulse
                outgoing = "lo" if all(x == "hi" for x in module.memory.values()) else "hi"
                for x in module.outputs:
                    q.append((module.name, x, outgoing))

    return hi * lo


