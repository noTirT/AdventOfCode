# AdventOfCode2023
Advent of Code event 2023

## Usage

Run in terminal
```
python3 main.py
```

Choose the problem you want to run by entering number from 1-25. Both parts of the Problem will then be calculated and printed to the console

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

## Testing

### Setting up tests

To enable testing your solution with unit tests, create a ```solution.txt``` file in your day directory containing the solution for the first part on line 1 and the solution for the second part on line 2

#### Adding Tests to Testing-Class

##### VScode Workspace Snippet

Add the unittest to the class in the ```test.py``` file with the ```test_day``` snippet configured in ```.vscode/python.code-snippets``` and enter the number of the day you want to test for the placeholder

##### Vanilla

Copy the unittest code from one of the other tests and replace the numbers with the number of the day you want to test

### Running Tests

#### VScode Testing Environment

The tests should be discovered by VScode by default and you can just run them in the ```Testing``` Tab

#### Console Testing

##### Define Test Module

Use the following command to run the tests in a specific file

```bash
python3 -m unittest <testing_module>
```

Add the ```-v``` flag to see more output

```bash
python3 -m unittest -v <testing_module>
```

##### Use Test Discovery

Use the following command to run your test files with Test Discovery

```bash
python3 -m unittest
```

Add the ```-v``` flag to see more output

```bash
python3 -m unittest -v
```

## Workflows

### Build

Every push or pull request to the ```main``` branch triggers the ```build``` workflow which runs a linter and all unittests in the ```test.py``` file