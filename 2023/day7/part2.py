from collections import defaultdict
from typing import List, Literal

from util import read_file_lines

labels = ["A", "K", "Q", "T", "9", "8", "7", "6", "5", "4", "3", "2", "J"]


def get_type(hand: str) -> int:
    counts = defaultdict(int)
    jokers = 0
    for x in hand:
        if x == "J":
            jokers += 1
        else:
            counts[x] += 1

    amounts = sorted(counts.values())

    # Check for 5 same
    if jokers >= 5 or amounts[-1] + jokers >= 5:
        return 5

    # Check for 4 same
    if jokers >= 4 or amounts[-1] + jokers >= 4:
        return 4

    # Check for full house
    if amounts[-1] + jokers >= 3:
        remaining_jokers = amounts[-1] + jokers - 3
        if (
            len(amounts) >= 2
            and amounts[-2] + remaining_jokers >= 2
            or remaining_jokers >= 2
        ):
            return 3.5
        # If not full house then it's 3 same
        return 3

    # Check for 2 pairs
    if amounts[-1] + jokers >= 2:
        remaining_jokers = amounts[-1] + jokers - 2
        if (
            len(amounts) >= 2
            and amounts[-2] + remaining_jokers >= 2
            or remaining_jokers >= 2
        ):
            return 2.5
        # If not 2 pairs then it's 1 pair
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
