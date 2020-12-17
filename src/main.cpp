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

#include "day_01.hpp"
#include "day_02.hpp"
#include "day_03.hpp"
#include "day_04.hpp"
#include "day_05.hpp"
#include "day_06.hpp"
#include "day_07.hpp"
#include "day_08.hpp"
#include "day_09.hpp"
#include "day_10.hpp"
#include "day_11.hpp"
#include "day_12.hpp"
#include "day_16.hpp"
#include "day_17.hpp"

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
	solutions["1a"] = day_01::part_a;
	solutions["1b"] = day_01::part_b;
	solutions["2a"] = day_02::part_a;
	solutions["2b"] = day_02::part_b;
	solutions["3a"] = day_03::part_a;
	solutions["3b"] = day_03::part_b;
	solutions["4a"] = day_04::part_a;
	solutions["4b"] = day_04::part_b;
	solutions["5a"] = day_05::part_a;
	solutions["5b"] = day_05::part_b;
	solutions["6a"] = day_06::part_a;
	solutions["6b"] = day_06::part_b;
	solutions["7a"] = day_07::part_a;
	solutions["7b"] = day_07::part_b;
	solutions["8a"] = day_08::part_a;
	solutions["8b"] = day_08::part_b;
	solutions["9a"] = day_09::part_a;
	solutions["9b"] = day_09::part_b;
	solutions["10a"] = day_10::part_a;
	solutions["10b"] = day_10::part_b;
	solutions["11a"] = day_11::part_a;
	solutions["11b"] = day_11::part_b;
	solutions["12a"] = day_12::part_a;
	solutions["12b"] = day_12::part_b;
	solutions["16a"] = day_16::part_a;
	solutions["16b"] = day_16::part_b;
	solutions["17a"] = day_17::part_a;
	solutions["17b"] = day_17::part_b;

	std::string requested = std::to_string(in.day) + (in.part ? "b" : "a");
	if (solutions.find(requested) != solutions.end()) {
		std::cout << solutions[requested](input_contents) << std::endl;
	} else {
		std::cout << "That solution doesn't exist yet!" << std::endl;
	}
	return 0;
}
