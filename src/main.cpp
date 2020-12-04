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

#include "main.hpp"

#include "files.hpp"
#include "input.hpp"

#include <iostream>

#include "day_1.hpp"
#include "day_2.hpp"
#include "day_3.hpp"
#include "day_4.hpp"

int main(int argc, char const *argv[]) {
	input in;

	if (!in.parse(argc, argv)) {
		return -1;
	}

	std::string input_contents;
	if (!files::read_file(input_contents, in.input_filename)) {
		return -1;
	}

	std::string out;
	switch (in.day) {
		case 1: {
			if (!in.part) {
				out = day_1::part_a(input_contents);
			} else {
				out = day_1::part_b(input_contents);
			}
			break;
		}
		case 2: {
			if (!in.part) {
				out = day_2::part_a(input_contents);
			} else {
				out = day_2::part_b(input_contents);
			}
			break;
		}
		case 3: {
			if (!in.part) {
				out = day_3::part_a(input_contents);
			} else {
				out = day_3::part_b(input_contents);
			}
			break;
		}
		case 4: {
			if (!in.part) {
				out = day_4::part_a(input_contents);
			} else {
				out = day_4::part_b(input_contents);
			}
			break;
		}
		default: {
			std::cout << "This day has no solution yet!" << std::endl;
			break;
		}
	}

	std::cout << out << std::endl;

	return 0;
}
