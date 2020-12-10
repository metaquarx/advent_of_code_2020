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

#include "day_04.hpp"

#include <regex>
#include <vector>

static std::vector<std::string> get_entries(std::string &input) {
	std::vector<std::string> entries;

	while (input.find("\n\n") != std::string::npos) {
		unsigned pos = static_cast<unsigned>(input.find("\n\n"));
		std::string entry = input.substr(0, pos + 1);
		input = input.substr(pos + 2);

		std::replace(entry.begin(), entry.end(), '\n', ' ');

		entries.push_back(entry);
	}

	std::replace(input.begin(), input.end(), '\n', ' ');
	entries.push_back(input);

	return entries;
}

std::string day_04::part_a(std::string input) {
	std::regex r_byr("(byr:)");
	std::regex r_iyr("(iyr:)");
	std::regex r_eyr("(eyr:)");
	std::regex r_hgt("(hgt:)");
	std::regex r_hcl("(hcl:)");
	std::regex r_ecl("(ecl:)");
	std::regex r_pid("(pid:)");

	auto entries = get_entries(input);

	unsigned valid = 0;

	for (auto &entry : entries) {
		if (std::regex_search(entry, r_byr) && std::regex_search(entry, r_iyr)
			&& std::regex_search(entry, r_eyr)
			&& std::regex_search(entry, r_hgt)
			&& std::regex_search(entry, r_hcl)
			&& std::regex_search(entry, r_ecl)
			&& std::regex_search(entry, r_pid)) {
			valid++;
		}
	}


	return std::to_string(valid);
}


std::string day_04::part_b(std::string input) {
	std::regex r_byr("byr:(\\d{4})");
	std::regex r_iyr("iyr:(\\d{4})");
	std::regex r_eyr("eyr:(\\d{4})");
	std::regex r_hgt("hgt:(\\d+)(in|cm)");
	std::regex r_hcl("hcl:#[0-9a-fA-F]{6}");
	std::regex r_ecl("ecl:(amb|blu|brn|gry|grn|hzl|oth)");
	std::regex r_pid("pid:(\\d){9}\\b");

	auto entries = get_entries(input);

	unsigned valid = 0;

	for (auto &entry : entries) {
		std::smatch matc;
		if (std::regex_search(entry, matc, r_byr) && std::stoi(matc[1]) >= 1920
			&& std::stoi(matc[1]) <= 2002
			&& std::regex_search(entry, matc, r_iyr)
			&& std::stoi(matc[1]) >= 2010 && std::stoi(matc[1]) <= 2020
			&& std::regex_search(entry, matc, r_eyr)
			&& std::stoi(matc[1]) >= 2020 && std::stoi(matc[1]) <= 2030
			&& regex_search(entry, matc, r_hgt)
			&& ((matc[2] == "in" && std::stoi(matc[1]) >= 59
				 && std::stoi(matc[1]) <= 76)
				|| (matc[2] == "cm" && std::stoi(matc[1]) >= 150
					&& std::stoi(matc[1]) <= 193))
			&& std::regex_search(entry, r_hcl)
			&& std::regex_search(entry, r_ecl)
			&& std::regex_search(entry, r_pid)) {
			valid++;
		}
	}


	return std::to_string(valid);
}
