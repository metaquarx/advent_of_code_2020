# Advent of Code 2020

This repository contains solutions to the 2020 edition of Advent of Code

# Building

CMake is the standard build tool for C++
```
cmake -S . -B build
cmake --build build
```
You will find the resultant executable in `./build/aoc2020`

# Running

Running the binary without any parameters will tell you the correct parameters to use. That is, `./aoc2020 day part filename`. For example, to run the the solution to part B of day 3, you would do `./aoc2020 3 b input.txt`
