// Copyright 2020 metaquarx, metaquarx@pm.me

//  This file is part of advent_of_code_2020.
//
//  advent_of_code_2020 is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  advent_of_code_2020 is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with advent_of_code_2020.  If not, see
//  <https://www.gnu.org/licenses/>.

#include "day_8.hpp"

#include <algorithm>
#include <sstream>
#include <vector>

static std::vector<std::pair<std::string, short>>
  get_instructions(std::string &input) {
	std::vector<std::pair<std::string, short>> output;

	std::stringstream program;
	program << input;
	std::string temp;
	while (std::getline(program, temp, '\n')) {
		output.push_back(
		  {temp.substr(0, 3), static_cast<short>(std::stoi(temp.substr(4)))});
	}

	return output;
}

static bool infinitely_loops(std::vector<std::pair<std::string, short>> &ins,
							 long &acc) {
	std::vector<long> executed;

	long pc = 0;
	for (; pc < static_cast<long>(ins.size());) {
		if (std::find(executed.begin(), executed.end(), pc) != executed.end()) {
			return true;
		} else if (ins[static_cast<unsigned long>(pc)].first == "nop") {
			executed.push_back(pc);
			pc++;

		} else if (ins[static_cast<unsigned long>(pc)].first == "acc") {
			executed.push_back(pc);
			acc += ins[static_cast<unsigned long>(pc)].second;
			pc++;

		} else if (ins[static_cast<unsigned long>(pc)].first == "jmp") {
			executed.push_back(pc);
			pc += ins[static_cast<unsigned long>(pc)].second;
		}
	}

	return false;
}

std::string day_8::part_a(std::string input) {
	auto instructions = get_instructions(input);
	long accumulator = 0;

	infinitely_loops(instructions, accumulator);

	return std::to_string(accumulator);
}


std::string day_8::part_b(std::string input) {
	auto instructions = get_instructions(input);

	long accumulator;

	for (auto &ins : instructions) {
		accumulator = 0;
		if (ins.first == "nop") {
			ins.first = "jmp";
			if (!infinitely_loops(instructions, accumulator)) {
				return std::to_string(accumulator);
			}
			ins.first = "nop";
		} else if (ins.first == "jmp") {
			ins.first = "nop";
			if (!infinitely_loops(instructions, accumulator)) {
				return std::to_string(accumulator);
			}
			ins.first = "jmp";
		}
	}

	return "";
}
