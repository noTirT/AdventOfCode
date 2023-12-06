# AdventOfCode2023
Advent of Code event 2023

## Usage

Run in terminal
```
python3 main.py
```

Choose Problem you want to run by entering number from 1-25. Both parts of the Problem will then be calculated and printed to the console

## Write solution

For each new day create a new Folder like this 
```
day<day_number>
```

The following is the file structure inside that folder
```bash
├── input.txt
├── part1.py
├── part2.py
├── test.txt (optional)
└── task.txt
```
### .txt Files

* ```input.txt```: contains the puzzle input
* ```task.txt```: contains the problem definition for that day
* ```test.txt```: contains the example puzzle input (optional)

### .py Files

Both Pyhton files have to have a ```solution``` function which returns the result for the corresponding part 1 or 2 of the selected problem.

The modules should not print the solution as that is handled by ```main.py```
