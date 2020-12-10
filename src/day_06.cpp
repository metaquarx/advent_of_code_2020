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

#include "day_06.hpp"

#include <algorithm>
#include <sstream>
#include <vector>

static std::vector<std::vector<std::string>>
  get_declarations(std::string &input) {
	std::vector<std::vector<std::string>> declarations;

	input += "\n";
	while (input.find("\n\n") != std::string::npos) {
		unsigned pos = static_cast<unsigned>(input.find("\n\n"));
		std::stringstream group;
		group << input.substr(0, pos + 1);
		input = input.substr(pos + 2);

		std::vector<std::string> decgroup;

		std::string temp;
		while (std::getline(group, temp, '\n')) {
			decgroup.push_back(temp);
		}

		declarations.push_back(decgroup);
	}

	return declarations;
}

std::string day_06::part_a(std::string input) {
	auto declarations = get_declarations(input);

	unsigned total = 0;

	for (auto &group : declarations) {
		std::vector<char> handled;

		for (auto &person : group) {
			for (char &declaration : person) {
				if (std::find(handled.begin(), handled.end(), declaration)
					== handled.end()) {
					handled.push_back(declaration);
				}
			}
		}

		total += handled.size();
	}

	return std::to_string(total);
}


std::string day_06::part_b(std::string input) {
	auto declarations = get_declarations(input);

	unsigned total = 0;

	for (auto &group : declarations) {
		std::vector<char> handled;

		for (unsigned i = 0; i < group.size(); i++) {
			if (i == 0) {
				for (char &declaration : group[i]) {
					handled.push_back(declaration);
				}
			} else {
				for (auto j = handled.begin(); j != handled.end();) {
					if (std::find(group[i].begin(), group[i].end(), *j)
						== group[i].end()) {
						j = handled.erase(j);
					} else {
						j++;
					}
				}
			}
		}

		total += handled.size();
	}

	return std::to_string(total);
}
