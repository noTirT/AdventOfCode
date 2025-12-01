#!/bin/bash

# 1. Check if a day number was provided
if [ -z "$1" ]; then
    echo "Usage: ./new_day.sh <day_number>"
    echo "Example: ./new_day.sh 5"
    exit 1
fi

# 2. Format Day Number (e.g., 5 -> 05)
# This removes leading zeros if typed (05 -> 5) then re-adds them (5 -> 05) to be safe
RAW_DAY=$(echo $1 | sed 's/^0*//')
PADDED_DAY=$(printf "%02d" $RAW_DAY)

CPP_PATH="src/days/day${PADDED_DAY}.cpp"
INPUT_PATH="inputs/day${PADDED_DAY}.txt"

# 3. Create Directories if they don't exist
mkdir -p src/days
mkdir -p inputs

# 4. Check if file already exists to prevent overwriting
if [ -f "$CPP_PATH" ]; then
    echo "Error: $CPP_PATH already exists!"
    exit 1
fi

# 5. Generate the C++ File
# Note: Adjust include paths if your headers are named differently (.h vs .hpp)
cat <<EOT > "$CPP_PATH"
#include <AoC.hpp>
#include <DayRegistry.hpp>

class Day${PADDED_DAY} : public AoCDay {
public:
    Answer part1() override {
        // lines is available as std::vector<std::string>
        return "TODO";
    }

    Answer part2() override {
        return "TODO";
    }
};

static DayRegistrar<Day${PADDED_DAY}> registrar(${RAW_DAY});
EOT

echo "Created $CPP_PATH"

# 6. Create (or Download) the Input File
# Optional: If you have a file named 'cookie.txt' containing your AoC session cookie,
# this will download the input automatically.
COOKIE_FILE="cookie.txt"

if [ -f "$COOKIE_FILE" ]; then
    echo "Downloading input from Advent of Code..."
    SESSION=$(cat $COOKIE_FILE)
    curl -s --cookie "session=$SESSION" "https://adventofcode.com/2024/day/$RAW_DAY/input" > "$INPUT_PATH"

    # Check if download succeeded (sometimes session is invalid)
    if grep -q "Puzzle inputs" "$INPUT_PATH"; then
        echo "Error: Download failed (Check your session cookie). Created empty file."
        echo "" > "$INPUT_PATH"
    else
        echo "Downloaded input to $INPUT_PATH"
    fi
else
    touch "$INPUT_PATH"
    echo "Created empty input file at $INPUT_PATH"
    echo "(Tip: Create a 'cookie.txt' file with your session cookie to auto-download inputs)"
fi

echo "--- Day $PADDED_DAY Setup Complete ---"
