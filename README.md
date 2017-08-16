# Sudoku solver
Solve sudoku puzzles faster than ever.

## Build
```
make
```

## Usage
Use pipes to redirect puzzles to the standard input.
```
cat puzzle | ./solve
```

## Puzzle file format
9 rows and 9 numbers each row. Empty boxes must be 0. (See puzzle.)

## Example
```
$ cat puzzle | ./solve
ORIGINAL
---------------------
|      |  3 7 |6    |
|      |6     |  9  |
|    8 |      |    4|
---------------------
|  9   |      |    1|
|6     |      |    9|
|3     |      |  4  |
---------------------
|7     |      |8    |
|  1   |    9 |     |
|    2 |5 4   |     |
---------------------

SOLVED
---------------------
|9 5 4 |1 3 7 |6 8 2|
|2 7 3 |6 8 4 |1 9 5|
|1 6 8 |2 9 5 |7 3 4|
---------------------
|4 9 5 |7 2 8 |3 6 1|
|6 8 1 |4 5 3 |2 7 9|
|3 2 7 |9 6 1 |5 4 8|
---------------------
|7 4 9 |3 1 2 |8 5 6|
|5 1 6 |8 7 9 |4 2 3|
|8 3 2 |5 4 6 |9 1 7|
---------------------
```
