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

#include <functional>
#include <iostream>
#include <unordered_map>

#include "day_1.hpp"
#include "day_2.hpp"
#include "day_3.hpp"
#include "day_4.hpp"
#include "day_5.hpp"
#include "day_6.hpp"

int main(int argc, char const *argv[]) {
	input in;

	if (!in.parse(argc, argv)) {
		return -1;
	}

	std::string input_contents;
	if (!files::read_file(input_contents, in.input_filename)) {
		return -1;
	}

	std::unordered_map<std::string, std::function<std::string(std::string)>>
	  solutions;
	solutions["1a"] = day_1::part_a;
	solutions["1b"] = day_1::part_b;
	solutions["2a"] = day_2::part_a;
	solutions["2b"] = day_2::part_b;
	solutions["3a"] = day_3::part_a;
	solutions["3b"] = day_3::part_b;
	solutions["4a"] = day_4::part_a;
	solutions["4b"] = day_4::part_b;
	solutions["5a"] = day_5::part_a;
	solutions["5b"] = day_5::part_b;
	solutions["6a"] = day_6::part_a;
	solutions["6b"] = day_6::part_b;

	std::string requested = std::to_string(in.day) + (in.part ? "b" : "a");
	if (solutions.find(requested) != solutions.end()) {
		std::cout << solutions[requested](input_contents) << std::endl;
	} else {
		std::cout << "That solution doesn't exist yet!" << std::endl;
	}
	return 0;
}
