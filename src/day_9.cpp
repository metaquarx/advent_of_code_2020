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

#include "day_9.hpp"

#include <algorithm>
#include <limits>
#include <sstream>
#include <vector>

static std::vector<unsigned> get_numbers(std::string &input) {
	std::vector<unsigned> output;

	std::stringstream parser;
	parser << input;
	unsigned temp;
	while (parser >> temp) {
		output.push_back(temp);
	}

	return output;
}

std::string day_9::part_a(std::string input) {
	auto numbers = get_numbers(input);

	unsigned preamble = 25;

	std::vector<unsigned> handled;
	for (unsigned i = preamble; i < numbers.size(); i++) {
		bool found = false;

		for (unsigned x = 0; x < numbers.size(); x++) {
			if (x + 1 > i - preamble && x < i) {
				for (unsigned y = 0; y < numbers.size(); y++) {
					if (y + 1 > i - preamble && y < i) {
						if (numbers[x] != numbers[y]) {
							if (numbers[x] + numbers[y] == numbers[i]) {
								found = true;
							}
						}
					}
				}
			}
		}

		if (found == false) {
			return std::to_string(numbers[i]);
		} else {
			found = true;
		}
	}

	return "";
}


std::string day_9::part_b(std::string input) {
	auto numbers = get_numbers(input);

	unsigned target = static_cast<unsigned>(std::stoi(part_a(input)));

	for (unsigned x = 0; x < numbers.size(); x++) {
		for (unsigned y = x + 1; y < numbers.size(); y++) {
			unsigned total_in_range = 0;

			for (unsigned i = x; i <= y; i++) {
				total_in_range += numbers[i];
			}

			if (total_in_range == target) {
				unsigned min = std::numeric_limits<unsigned>::max();
				unsigned max = 0;

				for (unsigned i = x; i <= y; i++) {
					if (numbers[i] < min) {
						min = numbers[i];
					}

					if (numbers[i] > max) {
						max = numbers[i];
					}
				}

				return std::to_string(max + min);
			}
		}
	}


	return "";
}
