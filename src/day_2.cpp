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

#include "day_2.hpp"

#include <cstdio>

struct password_entry {
	unsigned pos_a;
	unsigned pos_b;
	char specifier;
	std::string password;
};

std::string day_2::part_a(std::string input) {
	password_entry temp;
	unsigned total = 0;

	char buffer[50];
	while (input.size() > 8
		   && std::sscanf(input.c_str(), "%u-%u %1c: %50s", &temp.pos_a,
						  &temp.pos_b, &temp.specifier, buffer)) {
		temp.password = std::string(buffer);
		input = input.substr(input.find('\n') + 1);

		unsigned count = 0;
		for (unsigned i = 0; i < temp.password.size(); i++) {
			if (temp.password[i] == temp.specifier) {
				count++;
			}
		}

		if (count >= temp.pos_a && count <= temp.pos_b) {
			total++;
		}
	}

	return std::to_string(total);
}


std::string day_2::part_b(std::string input) {
	password_entry temp;
	unsigned total = 0;

	char buffer[50];
	while (input.size() > 8
		   && std::sscanf(input.c_str(), "%u-%u %1c: %50s", &temp.pos_a,
						  &temp.pos_b, &temp.specifier, buffer)) {
		temp.password = std::string(buffer);
		input = input.substr(input.find('\n') + 1);

		unsigned idx_a = temp.pos_a - 1;
		unsigned idx_b = temp.pos_b - 1;

		if ((temp.password.size() > idx_a
			 && temp.password[idx_a] == temp.specifier)
			!= (temp.password.size() > idx_b
				&& temp.password[idx_b] == temp.specifier)) {
			total++;
		}
	}

	return std::to_string(total);
}
