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

#include "day_03.hpp"

#include <cstdint>
#include <vector>

static unsigned loop(unsigned index, unsigned max) {
	return index % max;
}

static std::vector<std::vector<bool>> get_trees(std::string &input) {
	std::vector<std::vector<bool>> trees;

	while (input.find("\n") != std::string::npos) {
		unsigned pos = static_cast<unsigned>(input.find("\n"));
		std::string line = input.substr(0, pos);
		input = input.substr(pos + 1);

		std::vector<bool> temp;
		for (char &c : line) {
			if (c == '.') {
				temp.push_back(false);
			} else {
				temp.push_back(true);
			}
		}

		trees.push_back(temp);
	}

	return trees;
}

std::string day_03::part_a(std::string input) {
	auto trees = get_trees(input);

	unsigned max = static_cast<unsigned>(trees[0].size());
	unsigned total = 0;
	unsigned right = 0;

	for (auto &treeline : trees) {
		if (treeline[loop(right, max)] == true) {
			total++;
		}
		right += 3;
	}

	return std::to_string(total);
}


std::string day_03::part_b(std::string input) {
	auto trees = get_trees(input);

	unsigned max = static_cast<unsigned>(trees[0].size());
	unsigned long total = 1;

	std::vector<std::pair<uint8_t, uint8_t>> courses = {
	  {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

	for (auto &course : courses) {
		unsigned trees_hit = 0;
		unsigned right = 0;
		for (unsigned down = 0; down < trees.size(); down += course.second) {
			if (trees[down][loop(right, max)]) {
				trees_hit++;
			}

			right += course.first;
		}
		total *= trees_hit;
	}

	return std::to_string(total);
}
