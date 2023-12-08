from collections import defaultdict
from typing import List, Literal

from util import read_file_lines

labels = ["A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"]


def get_type(hand: str) -> int:
    counts = defaultdict(int)
    for x in hand:
        counts[x] += 1

    amounts = sorted(counts.values())

    if amounts == [5]:
        return 5
    if amounts == [1, 4]:
        return 4
    if amounts == [2, 3]:
        return 3.5
    if amounts == [1, 1, 3]:
        return 3
    if amounts == [1, 2, 2]:
        return 2.5
    if amounts == [1, 1, 1, 2]:
        return 2
    return 1


class Bet:
    def __init__(self, hand: str, bet: int) -> None:
        self.hand = hand
        self.bet = bet
        self.type = get_type(hand)

    def __str__(self) -> str:
        return f"Bet {{hand: {self.hand}, bet: {self.bet}, type: {self.type}}}"

    def get_hand_value(self) -> List[int]:
        result = []
        for c in self.hand:
            result.append(-labels.index(c))
        return result


def parse_input(test_or_real: Literal["test", "input"]) -> List[Bet]:
    result = []

    input_lines = read_file_lines(f"day7/{test_or_real}.txt")

    for line in input_lines:
        hand, bet = line.split(" ")
        result.append(Bet(hand, int(bet)))

    return result


def solution():
    bets = parse_input("input")
    bets = sorted(bets, key=lambda bet: [bet.type] + bet.get_hand_value())

    result = 0
    for index, bet in enumerate(bets):
        result += (index + 1) * bet.bet
    return result
