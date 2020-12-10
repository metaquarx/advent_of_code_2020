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

#include "day_10.hpp"

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <vector>

#include <iostream>

static std::vector<unsigned> get_adapters(std::string &input) {
	std::vector<unsigned> output;

	unsigned temp;
	std::stringstream ss;
	ss << input;
	while (ss >> temp) {
		output.push_back(temp);
	}

	return output;
}

std::string day_10::part_a(std::string input) {
	auto adapters = get_adapters(input);
	std::sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters.back() + 3);

	unsigned gap_1 = 0;
	unsigned gap_3 = 0;

	unsigned last = 0;
	for (auto &ad : adapters) {
		if (ad - last == 1) {
			gap_1++;
		} else if (ad - last == 3) {
			gap_3++;
		}

		last = ad;
	}

	return std::to_string(gap_1 * gap_3);
}

std::string day_10::part_b(std::string input) {
	auto adapters = get_adapters(input);

	adapters.push_back(0);
	std::sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters.back() + 3);

	std::vector<long> ways;
	ways.push_back(1);

	for (long i = 1; i < static_cast<long>(adapters.size()); i++) {
		long j = i - 1;
		long arrange = ways[static_cast<size_t>(j)];

		while (--j >= 0
			   && adapters[static_cast<size_t>(i)]
					  - adapters[static_cast<size_t>(j)]
					<= 3) {
			arrange += ways[static_cast<size_t>(j)];
		}

		ways.push_back(arrange);
	}


	return std::to_string(ways.back());
}
