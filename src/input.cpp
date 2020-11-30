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

#include "input.hpp"

#include <algorithm>
#include <iostream>
#include <limits>

bool input::parse(int argc, char const *argv[]) {
	if (argc < 4) {
		show_help(argv[0]);
		return false;
	}

	input_filename = argv[3];

	if (argv[2] == std::string("a")) {
		part = false;
	} else if (argv[2] == std::string("b")) {
		part = true;
	} else {
		show_help(argv[0]);
		return false;
	}

	std::string day_str = argv[1];
	if (!day_str.empty()
		&& std::all_of(day_str.begin(), day_str.end(), ::isdigit)) {
		int input = std::stoi(day_str);

		if (input <= std::numeric_limits<uint8_t>::max()
			&& input >= std::numeric_limits<uint8_t>::min()) {
			day = static_cast<uint8_t>(input);
			return true;
		}
	}

	show_help(argv[0]);
	return false;
}

void input::show_help(const std::string &name) {
	std::cout << "Usage: " << name << " <day> <part> <file>" << std::endl;
	std::cout << "         day - integer - 1 to 25" << std::endl;
	std::cout << "        part - string  - \"a\" or \"b\"" << std::endl;
	std::cout << "  input file - string  - Input filename" << std::endl;
}
